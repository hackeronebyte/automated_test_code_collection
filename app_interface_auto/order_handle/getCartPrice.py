import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from order_handle.getCart import getCart_all
from api.requests_api import requests_post


def getCartPrice(authorization):
    '''
    获取购物车价格
    :param authorization:
    :return:cart_Price
    '''
    url = "shopping-cart/o2o/cart/getCartPrice"
    header = get_header(authorization)
    data = getCart_all(authorization)
    data = str(data).replace("'", '\"')
    cart_Price = requests_post(url, header, data)


    return float(cart_Price["data"]["productDiscountAmount"])


if __name__ == '__main__':
    authorization = "af3f684e731f4c9588e16d2f7823393076bc9d63a8a71e7dbd60d944b04d0916"
    getCartPrice(authorization)
