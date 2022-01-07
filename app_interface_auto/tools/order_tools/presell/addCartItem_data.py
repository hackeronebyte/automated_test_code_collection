import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.presell.getProductByStoreId import getProductByStoreId


def addCartItem_data(result, index):
    '''
    预售添加购物车准备 data数据
    :param result:
    :param index:
    :return: {"count": 1, "marketNo": marketNo, "skuId": skuId}
    '''
    marketNo = result["data"]["list"][index]["marketNo"]
    skuId = result["data"]["list"][index]["skuId"]
    # count = random.randint(1, 3)
    return {"count": 1, "marketNo": marketNo, "skuId": skuId}


if __name__ == '__main__':
    authorization = "bb64bfad1c1b4db7843ece42df7a854a922305d91cf21f3200a255a209f9c7f2"
    getProductByStoreId(authorization)
