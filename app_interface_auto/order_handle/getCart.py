import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from api.requests_api import requests_get_header
from tools.order_tools.cart_id import cart_id
from tools.order_tools.cart_id import cart_id_all
from tools.logconfig.logingconfig import loging
from tools.order_tools.data_header_format_handle import get_header
from order_handle.getCartJdPromotionList import getCartJdPromotionList


# 获取购物车列表
def getCart(authorization):
    '''
    获取购物车列表 cartid
    :param authorization:
    :return: carts
    '''
    url = "shopping-cart/o2o/cart/getCart"
    header = get_header(authorization)
    result = requests_get_header(url, header)
    # print(result)
    carts = cart_id(result)
    if int(len(carts)) == 0:
        loging("购物车无商品".center(100, "*"))
        loging(carts)
    loging("购物车 cart_id:" + str(carts))

    return carts


def getCart_all(authorization):
    '''
    获取购物车列表 全部cartid 处理库存为零的情况
    :param authorization:
    :return:
    '''
    url = "shopping-cart/o2o/cart/getCart"
    header = get_header(authorization)
    result = requests_get_header(url, header)
    # print(result)
    # 处理库存为零的情况
    carts = cart_id_all(result)
    if int(len(carts)) == 0:
        loging("购物车无商品_ALL".center(100, "*"))
        loging(carts)
    loging("购物车_ALL cart_id:" + str(carts))

    # 处理促销接口
    getCartJdPromotionList(authorization)

    return carts


if __name__ == '__main__':
    authorization = "4ccdcbadf81f4299a4f029edd2f9735a9d9bd90a16b0943edd0e28b8af8baa69"
    getCart_all(authorization)
