# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import logging

logger = logging.getLogger()

class CrawlerPipeline:
    size = 0
    def open_spider(self, spider):
        self.file = open("tags.h", "w")

    def close_spider(self, spider):
        output = '\n\nconst char *TAGS[] = {{tag_{}}};\n'.format(",tag_".join(str(i) for i in range(self.size)))
        output += 'const int TAGS_SIZE = {};\n'.format(self.size)
        self.file.write(output)
        logger.info(output)
        self.file.close()

    def process_item(self, item, spider):
        adapter = ItemAdapter(item)
        hex_tag = adapter["value"].encode('utf-8').hex(sep='x').split('x')
        tag = ',0x'.join(hex_tag)
        logger.info(tag)
        logger.info("\n{}".format(adapter["value"]))
        output = "const char tag_{}[{}] = {{0x{}, 0x0}};\n".format(self.size, len(hex_tag) + 1, tag)
        self.file.write(output)
        self.size += 1
        return item
