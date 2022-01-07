import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post


def getCouponCenterList(authorization):
    '''
    获取领券中心数据全部信息
    :param authorization:
    :return: requests_post(url, header, data)
    '''
    url = "promotion-aggr/promotion/getCouponCenterList"
    header = get_header(authorization)
    data = data_str_proc({"pageIndex": 1, "pageSize": "20"})
    return requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "49c268fac8bf4f21aaa40904d5b70b71ad7ea6cbbf2c2dc53a99bfe989d55c41"
    getCouponCenterList(authorization)
