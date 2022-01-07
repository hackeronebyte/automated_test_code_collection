import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.batchAddCartItem import batchAddCartItem
import random
from tools.logconfig.logingconfig import loging


def cancelorder_add(authorization):
    '''
    对每天请求和响应结果保存到excel
    :param authorization:
    :return:
    '''
    with open(file_system_path() + "/tools/order_tools/cancelOrder_ID.txt", "r", encoding="utf-8") as forderID:
        forderID_lines = int(len(forderID.readlines()))
        if forderID_lines != 0:
            loging("对取消的订单进行再次购买".center(100, "*"))
            loging("再次购买有" + str(forderID_lines) + "笔订单")
            count = random.randint(1, forderID_lines)
            for i in range(count):
                loging("对取消订单进行" + str(count) + "次再购买，正在进行第" + str(i + 1) + "次购买")
                batchAddCartItem(authorization)
        else:
            loging("本次测试无取消订单,无需进行再次购买")


def order_result_statistics(sucess, fail):
    loging("下单接口测试执行完成  Succee(成功): " + str(sucess) + "条用例, Fail(失败): " + str(
        fail) + "条用例")
