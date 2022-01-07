from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_get_header


def getCartJdPromotionList(authorization):
    url = "shopping-cart/o2o/cart/getCartJdPromotionList"
    header = get_header(authorization)
    return requests_get_header(url, header)


if __name__ == '__main__':
    authorization = "cd0d845875a244fd92ce3f0a8df786e00674a20969d4001b060ab01de1dfd505"
    getCartJdPromotionList(authorization)
