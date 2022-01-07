import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.presell.makeOrderNew import makeOrderNew


def makeOrderNew_handle(authorization):
    '''
    为支付准备数据
    :param authorization:
    :return: {"orgOrderNo": result["data"]["orgOrderNo"], "paymentId": 6, "tradeType": 1001}
    '''
    result = makeOrderNew(authorization)
    if result == None:
        return None
    # {"orgOrderNo": result["data"]["orgOrderNo"], "paymentId": 6, "tradeType": 1001}
    else:
        return {"orgOrderNo": result["data"]["orgOrderNo"], "paymentId": 6, "tradeType": 1001}
