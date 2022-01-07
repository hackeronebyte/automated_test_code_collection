import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.presell.getCart import getCart


def getCart_handle(authorization):
    '''
    为getCartBylist准备data数据
    :param authorization:
    :return: marketNo_list[]
    '''
    result = getCart(authorization)
    cart_count = int(len(result["data"]["cartItemVOList"]))
    marketNo_list = []
    for c_count in range(cart_count):
        marketNo_list.append(result["data"]["cartItemVOList"][c_count]["marketNo"])
    return marketNo_list


if __name__ == '__main__':
    authorization = "bb64bfad1c1b4db7843ece42df7a854a922305d91cf21f3200a255a209f9c7f2"
    getCart_handle(authorization)
