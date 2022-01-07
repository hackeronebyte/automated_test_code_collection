import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_get_header


def getOrderDetailInfoByOrgOrder(authorization, orderNumber):
    '''
    查询订单状态
    :param authorization:
    :param orderNumber:
    :return: result
    '''
    url = "order/order/getOrderDetailInfoByOrgOrderNo/" + orderNumber
    header = get_header(authorization)
    result = requests_get_header(url, header)
    return result


if __name__ == '__main__':
    authorization = "1e6fb5aab1c54e7896bc9baff8029b60334e7eb867cabe64ec1073ae53283cc2"
    orderNumber = "4923435669852329787"
    getOrderDetailInfoByOrgOrder(authorization, orderNumber)
