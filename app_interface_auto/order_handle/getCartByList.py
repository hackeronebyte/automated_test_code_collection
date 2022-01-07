import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post
from order_handle.getCart import getCart
from tools.order_tools.cart_bylist import cart_bylist
from tools.logconfig.logingconfig import loging


def getCartByList(authorization):
    '''
    getCartByList id
    :param authorization:
    :return: id
    这里处理了库存为零的情况，为零商品不能购买
    '''
    url = "shopping-cart/o2o/cart/getCartByList"
    header = get_header(authorization)
    data = getCart(authorization)
    # print(data)
    data = data_str_proc(data)
    cart_Bylist = requests_post(url, header, data)
    cart_bylist(cart_Bylist)
    cart_count = int(len(cart_Bylist["data"]["cartItemVOList"]))
    by_cat_id_list = []
    for car_index in range(cart_count):
        # 库存为零的情况不能购买
        stock_count = cart_Bylist["data"]["cartItemVOList"][car_index]["stock"]
        by_cat_id = str(cart_Bylist["data"]["cartItemVOList"][car_index]["id"])
        if stock_count != 0:
            loging(str(by_cat_id) + ", 商品存储数量: " + str(stock_count))
            by_cat_id_list.append(by_cat_id)
        else:
            loging(str(by_cat_id) + ", 商品库存数量: " + str(stock_count) + " 不能购买")

    loging(by_cat_id_list)
    return by_cat_id_list


if __name__ == '__main__':
    authorization = "d2f4bd027be34fa58e771e1612fd409f4147b8b71d9a3c889e142391745bc9b8"
    getCartByList(authorization)
