import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_get_header


def getGroupProductList(authorization):
    '''
    返回团购集合
    :param authorization:
    :return: result
    '''
    url = "group-front/groupProduct/getGroupProductList?storeId=99999&pageIndex=1&pageSize=10"
    header = get_header(authorization)
    return requests_get_header(url, header)


if __name__ == '__main__':
    authorization = "bb64bfad1c1b4db7843ece42df7a854a922305d91cf21f3200a255a209f9c7f2"
    getGroupProductList(authorization)
