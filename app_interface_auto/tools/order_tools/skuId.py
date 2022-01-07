import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
import random


def skuId(result):
    '''
    添加商品skuId
    :param result:
    :return: skuId
    '''
    data_len = int(len(result["data"]["data"]))
    if data_len == 1:
        return result["data"]["data"][0]["skuId"]
    else:
        index = random.randint(0, int(len(result["data"]["data"])) - 1)
        return result["data"]["data"][index]["skuId"]
