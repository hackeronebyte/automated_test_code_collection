import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.groupbuying.joinGroup import joinGroup
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post
from tools.logconfig.logingconfig import loging


def cashierPayment(authorization):
    '''
    支付团拼
    :param authorization:
    :return:
    '''
    # 4923435635492590743
    # {"orgOrderNo":"4923435635492590734","paymentId":6,"tradeType":1001}
    url = "cashier/cashier/cashierPayment"
    header = get_header(authorization)
    joinGroup_result = joinGroup(authorization)
    if joinGroup_result["message"] != "商品售罄":
        orgOrderNo = joinGroup_result["data"]["orgOrderNo"]
        data = data_str_proc({"orgOrderNo": orgOrderNo, "paymentId": 6, "tradeType": 1001})
        requests_post(url, header, data)
        loging("团拼商品支付成功！")

    else:
        loging(str(joinGroup_result["message"]) + ",团拼流程结束！")


if __name__ == '__main__':
    authorization = "bb64bfad1c1b4db7843ece42df7a854a922305d91cf21f3200a255a209f9c7f2"
    cashierPayment(authorization)
