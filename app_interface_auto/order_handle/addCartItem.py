import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from api.requests_api import requests_post
import random
from tools.goods_search import goods_processing_search
from tools.order_tools.data_header_format_handle import get_header
from order_handle.createOnlineOrder import createOnlineOrder
from order_handle.getCartPrice import getCartPrice
from tools.logconfig.logingconfig import loging
from order_handle.getCart import getCart_all
from order_handle.coupon.getCouponJd import getCouponJd


#  添加商品到购物车
def addCartItem(authorization):
    '''
    添加商品到购物车
    :param authorization:
    :return: null
    '''
    # 在下单查看是否有优惠券，没有优惠券进行领用
    getCouponJd(authorization)
    skuId_list = []
    if getCartPrice(authorization) >= float(20.00):
        createOnlineOrder(authorization)
    else:
        loging("购买商品到购物车".center(100, "*"))
        url = "shopping-cart/o2o/cartItem/addCartItem"
        header = get_header(authorization)
        # 购买3-6个商品条目
        # 购买商品数据量 count 1-3
        count_for = random.randint(3, 6)
        # print("count_for", count_for)
        for cf in range(count_for):
            count = random.randint(1, 3)
            identification = random.randint(1, 2)
            skuId = goods_processing_search(identification)
            skuId_list.append(skuId)
            data = "{\"count\": " + str(count) + ", \"skuId\": " + str(skuId) + ", \"marketNo\": \"\"}"
            requests_post(url, header, data)
        loging("所有商品 skuId" + str(skuId_list))
        getCart_all(authorization)

        createOnlineOrder(authorization)


if __name__ == '__main__':
    authorization = "ed991629826344039043fb72f3828059dd875ebe78bad81c9bf22131fa54f7df"
    addCartItem(authorization)
