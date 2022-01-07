import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_get_header


def getAddressList(authorization):
    url = "user/userAddress/getAddressList"
    header = get_header(authorization)
    return requests_get_header(url, header)


if __name__ == '__main__':
    authorization = "13908dbff12e42cbac4dabe8f6036f0aaac67b5c703958de201b337f0f14f281"
    getAddressList(authorization)
