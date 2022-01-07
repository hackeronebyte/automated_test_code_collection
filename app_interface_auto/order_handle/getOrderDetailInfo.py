import sys

sys.path.append("D:\pythonworkspace\order_interface_atuo")
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_get_header


def getOrderDetailInfo(authorization, orderID):
    '''
           此接口获取全部订单
           :param authorization:
           :return:
           '''
    url = 'order/order/getOrderDetailInfo/' + str(orderID)
    header = get_header(authorization)
    result = requests_get_header(url, header)
    return result


if __name__ == '__main__':
    authorization = "4cef0c768429444ca5bbbd32a54e9929020e9d8ee576ef548f02e8c9eeb27fb2"
    getOrderDetailInfo(authorization, 18795)
