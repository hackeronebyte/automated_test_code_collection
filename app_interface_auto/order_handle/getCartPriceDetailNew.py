import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.getLimitAreaAddressList import getLimitAreaAddressList
from order_handle.getCartByList import getCartByList
from tools.order_tools.order_proc import order_proc
from tools.order_tools.data_str_proc import data_str_proc
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_post
from tools.logconfig.logingconfig import loging
import random


def getCartPriceDetailNew(authorization):
    '''
    获取下单价格
    :param authorization:
    :return: result, data_dict
    '''
    url = "shopping-cart/o2o/cart/getCartPriceDetailNew"
    header = get_header(authorization)
    adders = getLimitAreaAddressList(authorization)

    receiveAddr, receiveAddrLatitude, receiveAddrLongitude, receiveName, receivePhone = order_proc(adders)
    data = {}
    #
    data["list"] = getCartByList(authorization)
    data["receiverAddress"] = receiveName
    data["receiverName"] = receiveName
    data["receiverPhone"] = receivePhone
    data["receiveAddr"] = receiveAddr
    data["userLatitude"] = receiveAddrLatitude
    data["userLongitude"] = receiveAddrLongitude
    data["needDelivery"] = "true"
    # 使用优惠券 order_type = random.randint(1, 2)
    random_useCoupon = random.randint(0, 1)
    # print(random_useCoupon)
    if random_useCoupon == 0:
        data["useCoupon"] = "false"
        loging("未使用优惠券购买商品！")
    else:
        loging("使用优惠券购买商品！")
        data["useCoupon"] = "true"

    data_dict = data
    data = data_str_proc(data)
    result = requests_post(url, header, data.encode("utf-8"))
    return result, data_dict


if __name__ == '__main__':
    authorization = "d2f4bd027be34fa58e771e1612fd409f4147b8b71d9a3c889e142391745bc9b8"
    getCartPriceDetailNew(authorization)
