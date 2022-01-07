import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.getOrderPagedInfo import getOrderPagedInfo_all
from tools.order_tools.deleteOrder_handle import deleteOrder_handle
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_get_header
from tools.logconfig.logingconfig import loging


def deleteOrder(authorization):
    '''
    删除订单 随机删除
    :param authorization:
    :return:
    '''

    deleteOrder_file = file_system_path() + "/tools/deleteOrder_ident.txt"
    with open(deleteOrder_file, "r", encoding="utf-8") as f:
        lines = f.readline().split(",")
        # print(lines)
        sum = 0
        if int(lines[1]) < int(lines[0]):
            for i in range(int(lines[0])):
                sum += 1
                with open(deleteOrder_file, "w", encoding="utf-8") as f1:
                    f1.write(str(lines[0]) + "," + str(sum))
                    result = getOrderPagedInfo_all(authorization)
                    orderID = deleteOrder_handle(result)
                    if orderID != 0:
                        url = "order/order/deleteOrder/" + str(orderID)
                        herader = get_header(authorization)
                        requests_get_header(url, herader)
                        loging("订单删除成功" + str(orderID))
                    else:
                        loging("没有可删除的订单")
        else:
            loging("配置文件无删除订单配置，无需删除订单")


if __name__ == '__main__':
    authorization = "c09b7694d479401e867fe6cf85de4bb7b53dbd48fd8306b0177aca7bd9ef99ad"
    deleteOrder(authorization)
