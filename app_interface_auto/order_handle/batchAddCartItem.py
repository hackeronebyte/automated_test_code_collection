import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.cancelorder_add import cancelorder_add
from order_handle.getOrderDetailInfo import getOrderDetailInfo
from tools.order_tools.batchAddCartItem_handle import batchAddCartItem_handle
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_post
from tools.order_tools.data_str_proc import data_str_proc
from tools.logconfig.logingconfig import loging
from order_handle.createOnlineOrder import createOnlineOrder


def batchAddCartItem(authorization):
    '''
    取消的商品 再次购买
    :param authorization:
    :return:
    '''
    orderID = cancelorder_add()
    if orderID != "null":
        result = getOrderDetailInfo(authorization, orderID)
        url = "shopping-cart/o2o/cartItem/batchAddCartItem"
        header = get_header(authorization)
        data = data_str_proc(batchAddCartItem_handle(result))
        requests_post(url, header, data)
        createOnlineOrder(authorization)
    else:
        loging("orderID 为 null 再次购买结束！")


if __name__ == '__main__':
    authorization = "4cef0c768429444ca5bbbd32a54e9929020e9d8ee576ef548f02e8c9eeb27fb2"
    batchAddCartItem(authorization)
