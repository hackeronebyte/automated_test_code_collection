import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post


def getUserCouponListUnusedJd(authorization):
    '''
    已有优惠券
    :param authorization:
    :return: requests_post(url, header, data)
    '''
    url = "promotion-aggr/coupon/getUserCouponListUnusedJd"
    header = get_header(authorization)
    data = data_str_proc(
        {"couponType": 1, "pageIndex": 1, "pageSize": 20, "rowTotal": "null", "source": "null", "startRow": "null",
         "storeId": "null"})
    return requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "be7129e40ed5488fadcadc81db39eff7edaa050ed6e05f397e658e04c2f4eba3"
    getUserCouponListUnusedJd(authorization)
