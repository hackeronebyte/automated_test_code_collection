import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.presell.getProductByStoreId import getProductByStoreId
from order_handle.presell.addCartItem import addCartItem
from order_handle.presell.cashierPayment import cashierPayment

from tools.logconfig.logingconfig import loging


def presell_handle(authorization):
    '''
    预售上商品购买流程
    :param authorization:
    :return:
    '''
    # 购买限制有问题 在调用接口是后台限制的数量二但是接口可以购买三
    loging("购买预售商品".center(100, "*"))
    result = getProductByStoreId(authorization)
    totalCount = result["data"]["totalCount"]
    if totalCount > 0:
        # 判断库存不足的情况
        result = addCartItem(authorization, result)
        if result["message"] == "商品库存不足":
            loging("预售商品" + str(result["message"]) + ",预售流程结束")
        else:
            if cashierPayment(authorization) == None:
                loging("预售商品购买失败！")
            else:
                loging("预售商品支付成功！")
    else:
        loging("系统没有预售商品，预售流程结束！")


if __name__ == '__main__':
    authorization = "574982913b054940816f2edd73e012be298150f4538139d1bc1b87db233bae5e"
    presell_handle(authorization)
