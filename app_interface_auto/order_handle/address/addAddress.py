import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post


def addAddress(authorization):
    url = "user/userAddress/addAddress"
    header = get_header(authorization)
    data = data_str_proc({"roughAddress": "九龙路110号劳动广场110栋110楼", "sex": 1, "lat": 29.62373, "lng": 106.4778, "locationArea": "重庆市九龙路",
                          "isDefaultAddr": "", "receiveName": "小秦同学", "receivePhone": "13212456781", "detailAddress": "12",
                          "tag": 1}).encode("utf-8")
    requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "b9aba8b05d0d4e63a4426a262d2dbcb7e587b05612b8eee8d33ca67516cd8c11"
    addAddress(authorization)
