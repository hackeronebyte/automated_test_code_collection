import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_str_proc import data_str_proc
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_post


def getProductByStoreId(authorization):
    '''
    获取整个预售信息
    :param authorization:
    :return: 请求结果集
    '''
    url = "group-front/presaleProduct/getProductByStoreId"
    header = get_header(authorization)
    data = data_str_proc({"storeId": "99999", "pageIndex": "1", "pageSize": "10"})
    return requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "bb64bfad1c1b4db7843ece42df7a854a922305d91cf21f3200a255a209f9c7f2"
    getProductByStoreId(authorization)
