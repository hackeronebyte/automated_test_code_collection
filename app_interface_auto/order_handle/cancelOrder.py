import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_post
from tools.order_tools.data_str_proc import data_str_proc


def cancelOrder(authorization, orderId):
    url = "order/order/cancelOrder"
    header = get_header(authorization)
    data = data_str_proc({"cancelReason": "我不想买了", "orderId": orderId}).encode("utf-8")
    result = requests_post(url, header, data)
    return result
