import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.logconfig.logingconfig import loging


def batchAddCartItem_handle(result):
    '''
    处理再次购买数据 返回json 格式数据类型
    为再次购买准备data数据
    :param result:
    :return:
    '''
    orderDetailVOs_count = int(len(result["data"]["orderDetailVOs"]))
    orderDetailVOs_list = []
    for order_count in range(orderDetailVOs_count):
        orderDetailVOs_dict = {}
        orderDetailVOs_dict["skuId"] = result["data"]["orderDetailVOs"][order_count]["skuId"]
        orderDetailVOs_dict["count"] = result["data"]["orderDetailVOs"][order_count]["count"]
        orderDetailVOs_dict["marketType"] = result["data"]["orderDetailVOs"][order_count]["marketType"]
        orderDetailVOs_dict["marketNo"] = ""
        orderDetailVOs_list.append(orderDetailVOs_dict)
        loging("再次购买商品信息:" + str(order_count + 1) + "、" + str(orderDetailVOs_dict))
    loging("再次购买商品信息_COUNT:" + str(orderDetailVOs_list))

    return orderDetailVOs_list


if __name__ == '__main__':
    batchAddCartItem_handle()
