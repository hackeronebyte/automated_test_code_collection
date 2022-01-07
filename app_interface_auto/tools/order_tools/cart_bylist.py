import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.get_time import get_now_time
from tools.order_tools.read_write_order_dict import write_order_dict


def cart_bylist(result):
    bylist_dict = {}
    bylist_dict["run_time"] = get_now_time()
    cartItem_count = int(len(result["data"]["cartItemVOList"]))
    bylist_list = []
    for cart_count in range(cartItem_count):
        cartItem_dict = {}
        name = result["data"]["cartItemVOList"][cart_count]["name"]
        skuId = result["data"]["cartItemVOList"][cart_count]["skuId"]
        id = result["data"]["cartItemVOList"][cart_count]["id"]
        count = result["data"]["cartItemVOList"][cart_count]["count"]
        salePrice = result["data"]["cartItemVOList"][cart_count]["salePrice"]
        totalPrice = result["data"]["cartItemVOList"][cart_count]["totalPrice"]
        cartItem_dict["name"] = name
        cartItem_dict["skuId"] = skuId
        cartItem_dict["id"] = id
        cartItem_dict["count"] = count
        cartItem_dict["salePrice"] = salePrice
        cartItem_dict["totalPrice"] = totalPrice
        bylist_list.append(cartItem_dict)

    # totalPrice_str = "合计：" + str(totalPrice_str)
    bylist_dict["data"] = bylist_list
    bylist_dict["cart_totalPrice"] = float(0)
    # loging(totalPrice_str)

    file_dict_name = file_system_path() + "/tools/order_tools/order_dict.txt"
    write_order_dict(file_dict_name, bylist_dict)


if __name__ == '__main__':
    cart_bylist()
