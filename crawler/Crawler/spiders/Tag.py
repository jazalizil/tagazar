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
        word = "Tag"
        try:
            word = self.word
        except AttributeError:
            self.logger.warnging("Set default Tag")
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


    async def parse(self, response):
        page = response.meta["playwright_page"]
        async def handle_download(response):
            loading = await page.locator('div#taagTestAllListLoaded').text_content()
            self.logger.info('{}.'.format(loading))
        page.on("response", handle_download)
        page.set_default_timeout(TIMEOUT)
        try:
            await page.wait_for_function(js_code)
        except PlaywrightTimeoutError:
            self.logger.warning('Timeout error')
        tags = await page.locator("pre.fig").all_inner_texts()
        await page.close()
        self.logger.info("Done.")
        for tag in tags:
            yield Tag(value=tag, size=len(tag))
