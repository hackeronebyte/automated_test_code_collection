import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_get_header
from api.requests_api import requests_post
from tools.logconfig.logingconfig import loging


def getLimitAreaAddressList(authorization):
    '''
    获取配送地址，没有则创建
    :param authorization:
    :return:
    '''
    url = "user/userAddress/getLimitAreaAddressList/99999"
    header = get_header(authorization)
    adders = requests_get_header(url, header)
    data_count = int(len(adders["data"]))
    if data_count == 0:
        loging("没有收获地址，系统默认添加".center(100, "*"))
        # 获取门店地址
        url = "wsd-interface/user/userAddress/addAddress"
        data = {"roughAddress": "南岸南",
                "sex": "1",
                "lat": "29.62373",
                "lng": "106.4778",
                "locationArea": "巴南区",
                "isDefaultAddr": "1",
                "receiveName": "自动化",
                "receivePhone": "13212456701",
                "detailAddress": "123",
                "tag": "1"
                }
        data = str(data).replace("'", '\"').encode("utf-8")
        requests_post(url, header, data)
    if data_count == 0:
        adders = getLimitAreaAddressList(authorization)
    return adders


if __name__ == '__main__':
    authorization = "c36de9ebd7ed44cf8687084a5da8b5f1ccbf0de14296eeca6e48c295ce3d6bf7"
    getLimitAreaAddressList(authorization)
