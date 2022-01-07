import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from api.requests_api import requests_get_header
import random
from tools.order_tools.skuId import skuId
from tools.logconfig.logingconfig import loging
from tools.order_tools.data_header_format_handle import get_header_not_author


# 商品搜索
def goods_processing_search(identification):
    '''
    搜索商品 1 关键字 模拟手动搜索
            2 分类选择搜索
    :param identification:
    :return:
    '''
    sku_id = 0
    header = get_header_not_author()
    if identification == 1:

        loging("正在手动搜索商品".center(100, "*"))
        # 在配置文件手工搜索
        with open(file_system_path() + "/tools/goods_kw.txt", "r", encoding="utf-8") as f:
            # with open("goods_kw.txt", "r", encoding="utf-8") as f:
            line = f.readline()
            kw = line.split(",")
            loging(kw)
            index = random.randint(0, int(len(kw)) - 1)
            url = "product-query/search/searchProduct?kw=" + str(
                kw[index]) + "&sort=default&order=0&index=1&size=10"

            result_hand = requests_get_header(url, header)
            #  and result_hand["code"] != 200
            if result_hand["data"]["rowTotal"] == 0 or result_hand["code"] == 1006:
                loging("手动搜索，没有搜索到商品将跳转到分类进行搜索......".center(100, "*"))
                sku_id = goods_processing_search(1)
            if result_hand["data"]["rowTotal"] != 0:
                sku_id = skuId(result_hand)
                loging("搜索到商品 sku_id:" + str(sku_id))

        # skuId(result_hand)
    if identification == 2:
        sku_id = 0
        loging("正在分类搜索商品!".center(100, "*"))
        show_type_url = "product-query/classfication/list/firstLevel"
        result = requests_get_header(show_type_url, header)
        # print(int(len(result["data"])))
        index = random.randint(0, int(len(result["data"])) - 1)
        show_id = result["data"][index]["id"]
        show_url = "product-query/search/searchProduct?sort=default&order=0&index=1&size=10&fcid=" + str(
            show_id) + "&searchType=0"
        result_auto = requests_get_header(show_url, header)
        # and result_auto["code"] != 200
        # {"code":1006,"message":"商品已下架"}
        if result_auto["data"]["rowTotal"] == 0 or result_auto["code"] == 1006:
            loging("分类搜索，没有搜索到商品继续搜索".center(100, "*"))
            sku_id = goods_processing_search(2)
        if result_auto["data"]["rowTotal"] != 0:
            sku_id = skuId(result_auto)
            loging("搜索到商品商品 sku_id:" + str(sku_id))
    return sku_id


if __name__ == '__main__':
    print(goods_processing_search(1))
