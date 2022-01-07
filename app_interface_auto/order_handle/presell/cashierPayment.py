import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from tools.order_tools.presell.makeOrderNew_handle import makeOrderNew_handle
from api.requests_api import requests_post


def cashierPayment(authorization):
    '''
    预售支付
    :param authorization:
    :return:
    '''
    if makeOrderNew_handle(authorization) == None:
        return None
    else:
        url = "cashier/cashier/cashierPayment"
        header = get_header(authorization)
        data = data_str_proc(makeOrderNew_handle(authorization))
        requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "bb64bfad1c1b4db7843ece42df7a854a922305d91cf21f3200a255a209f9c7f2"
    cashierPayment(authorization)
