from typing import Iterable

import scrapy
import urllib.parse

from scrapy import Request
from playwright.sync_api import TimeoutError as PlaywrightTimeoutError

from Crawler.items import Tag

TIMEOUT = 120e3

js_code = """
    () => {
        value = document.querySelector('div#taagTestAllListLoaded');
        const [current, final] = value.textContent.split(': ')[1].split(' of ')
        return current === final
    }
"""

class TagSpider(scrapy.Spider):
    name = "Tag"
    allowed_domains = ["www.patorjk.com"]

    def start_requests(self) -> Iterable[Request]:
        try: self.word
        except AttributeError: word = 'Tag'
        params = {
            'p': 'testall',
            'f': 'Graffiti',
            't': word
        }
        url = "https://www.patorjk.com/software/taag/" + '#' + urllib.parse.urlencode(params)
        yield scrapy.Request(url, self.parse, meta={
            "playwright": True,
            "playwright_include_page": True,
        })

    async def new_font(self, response):
        count = await self.page.locator("div#taagTestAllListLoaded").text_content()
        self.logger.info(count)

    async def parse(self, response):
        self.page = response.meta["playwright_page"]
        self.page.set_default_timeout(TIMEOUT)
        self.page.on("response", self.new_font)
        try:
            await self.page.wait_for_function(js_code)
        except PlaywrightTimeoutError:
            self.logger.warning('Timeout error')
        tags = await self.page.locator("pre.fig").all_inner_texts()
        await self.page.close()
        self.logger.info("Done.")
        for tag in tags:
            yield Tag(value=tag, size=len(tag))
