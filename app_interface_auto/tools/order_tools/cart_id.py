import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
import random
from tools.logconfig.logingconfig import loging


def cart_id(result):
    '''
    处理购物车 cart_id 返回一个list(随机选择列表 用于模拟用户操作)
    为下单数据准备 cart_id
    :param result:
    :return: cartItem_List
    '''
    # 这个分为两种情况 1、随机选择性购买 2、全部一次性购买
    random_cart = random.randint(1, 2)
    cartItemVOList_count = int(len(result["data"]["cartItemVOList"]))
    random_cartItem = random.randint(1, cartItemVOList_count)
    cartItem_List = []
    if random_cart == 1:
        loging("随机选择性购买商品".center(100, "*"))
        for c_count in range(random_cartItem):
            cat_id = str(result["data"]["cartItemVOList"][c_count]["id"])
            cartItem_List.append(cat_id)
    if random_cart == 2:
        loging("购物车商品全部购买".center(100, "*"))
        for c_count_all in range(cartItemVOList_count):
            cat_id = str(result["data"]["cartItemVOList"][c_count_all]["id"])
            cartItem_List.append(cat_id)

    # print(cartItem_List)
    return cartItem_List


def cart_id_all(result):
    '''
    处理购物车 cart_id 返回一个list(全部购物车)
    :param result:
    :return: cartItem_List
    '''
    cartItem_List = []
    cartItemVOList_count = int(len(result["data"]["cartItemVOList"]))
    # 过滤库存为零的商品
    for c_count_all in range(cartItemVOList_count):
        stock = result["data"]["cartItemVOList"][c_count_all]["stock"]
        cat_id = str(result["data"]["cartItemVOList"][c_count_all]["id"])
        # print(cat_id, stock)
        if stock != 0:
            cartItem_List.append(cat_id)
    # print(cartItem_List)
    return cartItem_List


if __name__ == '__main__':
    cart_id_all()
