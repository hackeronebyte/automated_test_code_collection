import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.groupbuying.getGroupProductList_handle import getGroupProductList_handle
from order_handle.groupbuying.cashierPayment import cashierPayment
from tools.logconfig.logingconfig import loging


def groupbuying_handle(authorization):
    loging("购买团购商品".center(100, "*"))
    groupProductList = getGroupProductList_handle(authorization)
    if groupProductList != "null":
        cashierPayment(authorization)
    else:
        loging("系统没有团拼商品，团拼流程结束")


if __name__ == '__main__':
    authorization = "bb64bfad1c1b4db7843ece42df7a854a922305d91cf21f3200a255a209f9c7f2"
    groupbuying_handle(authorization)
