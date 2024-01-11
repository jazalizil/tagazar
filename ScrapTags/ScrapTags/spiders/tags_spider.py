import scrapy
from scrapy_splash import SplashRequest


class TagsSpider(scrapy.Spider):
    name = "tags"

    def start_requests(self):
        urls = "https://patorjk.com/software/taag/#p=testall&t=jazaoazar"

        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        self.log(f"{response.body}")
