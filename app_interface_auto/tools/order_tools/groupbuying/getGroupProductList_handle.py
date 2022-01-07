import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.groupbuying.getGroupProductList import getGroupProductList
from tools.get_time import get_now_time
import random


def getGroupProductList_handle(authorization):
    '''
    处理团购时间未过期的
    :param authorization:
    :return: result["data"]["list"][index]
    '''
    result = getGroupProductList(authorization)
    list_count = int(len(result["data"]["list"]))
    index_list = []
    for l_count in range(list_count):
        spellEndTime = result["data"]["list"][l_count]["spellEndTime"]
        if spellEndTime > get_now_time():
            index_list.append(l_count)
    list_count = int(len(index_list))
    if list_count != 0:
        index = random.randint(0, list_count - 1)
        return result["data"]["list"][index]
    else:
        return "null"
