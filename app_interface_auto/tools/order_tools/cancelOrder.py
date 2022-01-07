import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.getOrderDetailInfoByOrgOrder import getOrderDetailInfoByOrgOrder
from order_handle.cancelOrder import cancelOrder
from tools.logconfig.logingconfig import loging


def cancelOrder_handle(authorization, orderNumber):
    result = getOrderDetailInfoByOrgOrder(authorization, orderNumber)
    orderId = result["data"]["orderInfoVO"]["id"]
    loging("取消订单号：" + str(orderNumber) + ", orderId:" + str(orderId))
    # 取消订单orderId写入文件保存，在此购买使用
    with open(file_system_path() + "/tools/order_tools/cancelOrder_ID.txt", "a+", encoding="utf-8") as f:
        f.write(str(orderId) + "\n")

    result = cancelOrder(authorization, orderId)
    return result


if __name__ == '__main__':
    authorization = "67935a0aec544878b9ac1768ad4fba20f95514939b47a21758af573701cdfb52"
    orderNumber = "4923435601132854833"
    result = cancelOrder_handle(authorization, orderNumber)
    print(result)
