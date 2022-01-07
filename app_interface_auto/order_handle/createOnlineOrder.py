import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.get_time import get_now_time
from tools.get_time import get_time_revert
from tools.logconfig.logingconfig import loging
from api.requests_api import requests_post
from tools.order_tools.data_str_proc import data_str_proc
from order_handle.cashierPayment import cashierPayment
from tools.order_tools.read_write_order_dict import *
import random
from order_handle.getCartPriceDetailNew import getCartPriceDetailNew
from order_handle.getOrderDetailInfoByOrgOrder import getOrderDetailInfoByOrgOrder
from tools.order_tools.cancelOrder import cancelOrder_handle


def createOnlineOrder(authorization):
    '''
    下单操作
    :param authorization:
    :return: null
    '''
    loging("下单".center(100, "*"))
    url = "order/order/createOnlineOrder"
    header = get_header(authorization)
    data = {}
    # 获取配送地址
    # 配送和自提
    order_type = random.randint(1, 2)
    # result, data_dict
    result_CartPriceDetailNew, data_CartPriceDetailNew = getCartPriceDetailNew(authorization)
    # 组装配送信息
    if order_type == 1:
        loging("配送订单".center(100, "*"))
        data["cartIds"] = data_CartPriceDetailNew["list"]
        data["expectReceiveStartTime"] = get_now_time()
        data["expectReceiveEndTime"] = get_time_revert(30)
        data["isDelivery"] = "1"
        data["remark"] = ""
        data["receiveAddr"] = data_CartPriceDetailNew["receiveAddr"]
        data["receiveAddrLatitude"] = data_CartPriceDetailNew["userLatitude"]
        data["receiveAddrLongitude"] = data_CartPriceDetailNew["userLongitude"]
        data["receiveName"] = data_CartPriceDetailNew["receiverName"]
        data["receivePhone"] = data_CartPriceDetailNew["receiverPhone"]
    if order_type == 2:
        loging("自提订单".center(100, "*"))
        data["cartIds"] = data_CartPriceDetailNew["list"]
        data["expectReceiveStartTime"] = get_now_time()
        data["expectReceiveEndTime"] = get_time_revert(30)
        data["isDelivery"] = "0"
        data["remark"] = ""
    data = data_str_proc(data)
    result = requests_post(url, header, data.encode("utf-8"))
    # {"code":200,"data":"4923435601132850943","message":"操作成功"}
    # {"code":5001,"message":"商品金额小于20元不支持配送！"}
    # {"code":5001,"message":"系统执行异常(1613612632237)"}
    file_dict_name = file_system_path() + "/tools/order_tools/order_dict.txt"
    if result["code"] == 200:
        orderNumber = result["data"]
        loging(orderNumber)
        orgOrderNo = int(orderNumber)
        ## 下单之后在取消订单 订单号%6==0 取消订单
        if orgOrderNo % 4 == 0 or orgOrderNo % 6 == 0:
            cancelOrder_result = cancelOrder_handle(authorization, orderNumber)
            if cancelOrder_result["code"] == 200:
                cancelOrder_result["message"] = "取消订单," + cancelOrder_result["message"]
                read_write_order_dict_cancelOrder(file_dict_name, result, result_CartPriceDetailNew, cancelOrder_result)
            else:
                cancelOrder_result["message"] = "取消订单," + cancelOrder_result["message"]
                read_write_order_dict_cancelOrder(file_dict_name, result, result_CartPriceDetailNew, cancelOrder_result)
        else:
            # 调用支付接口 支付订单
            cashierPaymentresult = cashierPayment(authorization, orderNumber)
            # 支付成功后，查询订单获取订单信息
            orderDetailInfo = getOrderDetailInfoByOrgOrder(authorization, orderNumber)
            # 下单支付成功后把订单写入excel
            read_write_order_dict_success(file_dict_name, result, result_CartPriceDetailNew, orderDetailInfo,
                                          cashierPaymentresult)

    else:
        # {"code":5001,"message":"商品金额小于20元不支持配送！"}
        read_write_order_dict(file_dict_name, result, result_CartPriceDetailNew)


if __name__ == '__main__':
    authorization = "de25f14d4e7e4e8ab10813f032de2812370ffca1fc7e664d8e085671a9ab54fb"
    createOnlineOrder(authorization)
