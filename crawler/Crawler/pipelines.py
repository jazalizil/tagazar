# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import logging
import os

logger = logging.getLogger()

class CrawlerPipeline:
    first = True
    size = 0
    def open_spider(self, spider):
        self.file = open("tags.h", "w")
        self.file.write("unsigned char TAGS[] = ")

    def close_spider(self, spider):
        self.file.write('};\n')
        self.file.write('unsigned int TAGS_SIZE = {};\n'.format(self.size))
        self.file.close()

    def process_item(self, item, spider):
        adapter = ItemAdapter(item)
#        logger.info("unsigned char x[] = {{{}}}".format(", ".join([hex(i) for i in adapter["value"]])))
        tag = ',0x'.join(adapter["value"].encode('utf-8').hex(sep='x').split('x') + ['0a', '0a'])
        self.file.write('{}0x{}'.format('{' if self.first else ',', tag))
        self.first = False
        logger.info('0x{}'.format(tag))
        self.size += adapter['size']
        return item
