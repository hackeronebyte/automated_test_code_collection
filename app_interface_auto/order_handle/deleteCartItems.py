from order_handle.getCart import getCart_all
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post
from tools.logconfig.logingconfig import loging


def deleteCartItems(authorization):
    """
    删除购物车 生产环境可能需要
    :param authorization:
    :return:
    """
    carts_id = getCart_all(authorization)
    # carts_id =
    if int(len(carts_id)) > 0:
        loging("删除购物车商品" + str(carts_id))
        url = "shopping-cart/o2o/cartItem/deleteCartItems"
        header = get_header(authorization)
        data = data_str_proc(carts_id)
        requests_post(url, header, data)
    else:
        loging("购物车没有商品无需删除")


if __name__ == '__main__':
    authorization = "4ee0b763c4fc4048a6fe3fa51caadb6b206307460e0dc1506aa7d9f2bafd2e61"
    deleteCartItems(authorization)
