import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from tools.order_tools.data_str_proc import data_str_proc
from tools.order_tools.groupbuying.getGroupProductList_handle import getGroupProductList_handle
from api.requests_api import requests_post
from tools.logconfig.logingconfig import loging


def joinGroup(authorization):
    '''
    加入团购
    :param authorization:
    :return: requests_post(url, header, data)
    '''
    # {"groupInfoId":0,"groupProductId":"4923435635492590532",
    # "joinType":0,"storeId":99999,"version":0,"joinChannel":0}
    url = 'group-front/groupInfo/joinGroup'
    header = get_header(authorization)
    result_groupProductId = getGroupProductList_handle(authorization)
    loging("团拼商品:" + str(result_groupProductId))
    groupProductId = result_groupProductId["groupProductId"]
    data = data_str_proc(
        {"groupInfoId": 0, "groupProductId": groupProductId, "joinType": 0, "storeId": 99999, "version": 0,
         "joinChannel": 0})
    return requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "bb64bfad1c1b4db7843ece42df7a854a922305d91cf21f3200a255a209f9c7f2"
    joinGroup(authorization)
