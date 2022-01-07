import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from order_handle.presell.getProductByStoreId import getProductByStoreId
from tools.order_tools.presell.addCartItem_data import addCartItem_data
import random
from api.requests_api import requests_post


def addCartItem(authorization, presell_result):
    '''
    添加预售商品到购物车
    :param authorization:
    :param presell_result:
    :return:
    '''
    # presell_result = getProductByStoreId(authorization)
    count_result = int(len(presell_result["data"]["list"]))
    for_count = random.randint(1, count_result)
    for f_c in range(for_count):
        url = "group-front/presale/cartItem/addCartItem"
        header = get_header(authorization)
        data = data_str_proc(addCartItem_data(presell_result, f_c))
        return requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "7fd07054d45f4f03b37f2c7a350b22bf6b3def99c12186b12b6211dfa1ee1bfc"
    addCartItem(authorization)
