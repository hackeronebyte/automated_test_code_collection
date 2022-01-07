import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post


def getAllStoresByLocation(authorization):
    url = "business-store/store/getAllStoresByLocation"
    header = get_header(authorization)
    data = data_str_proc({"functionId": 1, "latitude": 29.616881, "longitude": 106.501275})
    requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "8cbdc8e453554a0e883f911e46189e4a794c6e2ae9fba0166d7ec7177de79db6"
    getAllStoresByLocation(authorization)
