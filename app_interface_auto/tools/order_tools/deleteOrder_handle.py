import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.logconfig.logingconfig import loging


def deleteOrder_handle(result):
    '''
    对删除订单进行处理 随机返回ID
    :param result:
    :return: orderID
    '''
    res = result["data"]["result"]
    orderID = 0
    for r in res:
        if r["statusCode"] == 10040:
            orderID = r["id"]
    loging("删除的订单ID:" + str(orderID))
    return orderID


if __name__ == '__main__':
    print("===========", deleteOrder_handle())
