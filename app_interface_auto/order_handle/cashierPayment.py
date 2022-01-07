import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.logconfig.logingconfig import loging
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post


def cashierPayment(authorization, orderNumber):
    '''
    订单支付
    :param authorization:
    :param orderNumber:
    :return: null
    '''
    loging("支付订单".center(100, "*"))
    url = "cashier/cashier/cashierPayment"
    header = get_header(authorization)
    data = {"orgOrderNo": orderNumber, "paymentId": "6", "tradeType": "1004"}
    data = data_str_proc(data)
    result = requests_post(url, header, data)
    if result["code"] == 200:
        loging(
            "订单支付成功! orderId:" + str(result["data"]["orderId"]) + ", orgOrderNo:" + str(result["data"]["orgOrderNo"]))
    else:
        loging("订单支付失败")
    return result


if __name__ == '__main__':
    authorization = "9ea6f76c49be44d5841369be27fb16c533c3a1d6ad9ad8927b438617a7025e04"
    orderNumber = "4923435601132851283"
    cashierPayment(authorization, orderNumber)
