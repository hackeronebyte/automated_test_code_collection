import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post


def getOrderPagedInfo(authorization):
    '''
    此接口 获取待支付全部订单
    :param authorization:
    :return:
    '''
    url = 'order/order/getOrderPagedInfo'
    header = get_header(authorization)
    data = {"pageIndex": 1, "pageSize": 10, "systemSrc": "0", "statusCode": "10000"}
    data = data_str_proc(data)
    requests_post(url, header, data)


def getOrderPagedInfo_all(authorization):
    '''
       此接口获取全部订单
       :param authorization:
       :return:
       '''
    url = 'order/order/getOrderPagedInfo'
    header = get_header(authorization)
    data = {"pageIndex": 1, "pageSize": 20, "systemSrc": "0"}
    data = data_str_proc(data)
    result = requests_post(url, header, data)
    return result


if __name__ == '__main__':
    authorization = "c09b7694d479401e867fe6cf85de4bb7b53dbd48fd8306b0177aca7bd9ef99ad"
    # getOrderPagedInfo(authorization)
    getOrderPagedInfo_all(authorization)
