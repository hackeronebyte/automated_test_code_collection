import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from order_handle.coupon.getUserCouponListUnusedJd import getUserCouponListUnusedJd
from order_handle.coupon.getCouponCenterList import getCouponCenterList
from tools.logconfig.logingconfig import loging
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post
import random


def getCouponJd(authorization):
    '''
    领用优惠券
    :param authorization:
    :return:
    '''
    # 查询是否有优惠券 如果有就打印日志 显示优惠券信息
    result_usedJd = getUserCouponListUnusedJd(authorization)
    # print(result_usedJd)
    if result_usedJd["data"]["rowTotal"] != 0:
        loging("优惠券".center(100, "*"))
        data_count = int(len(result_usedJd["data"]["data"]))
        for d_count in range(data_count):
            qname = result_usedJd["data"]["data"][d_count]["qname"]
            leastCost = result_usedJd["data"]["data"][d_count]["leastCost"]
            qmz = result_usedJd["data"]["data"][d_count]["qmz"]
            qtype = int(result_usedJd["data"]["data"][d_count]["qtype"])
            if qtype == 0:
                loging("优惠券：" + qname + ",满" + str(leastCost) + "," + str(qmz) + "折")
            else:
                loging("优惠券：" + qname + ",满" + str(leastCost) + ",减" + str(qmz) + "")
    else:
        # 如果没有优惠券 就领导优惠券
        loging("无优惠券".center(100, "*"))
        result_CouponCenterList = getCouponCenterList(authorization)
        series_random = random.randint(1, int(len(result_CouponCenterList["data"]["data"])))
        series = result_CouponCenterList["data"]["data"][series_random]["series"]
        title = result_CouponCenterList["data"]["data"][series_random]["title"]
        url = "promotion-aggr/coupon/getCouponJd"
        header = get_header(authorization)
        data = data_str_proc({"couponId": series})
        requests_post(url, header, data)
        loging("领用优惠券：" + title + ", " + str(series))


if __name__ == '__main__':
    authorization = "49c268fac8bf4f21aaa40904d5b70b71ad7ea6cbbf2c2dc53a99bfe989d55c41"
    getCouponJd(authorization)
