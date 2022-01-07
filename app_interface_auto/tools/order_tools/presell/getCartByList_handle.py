import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.presell.getCartByList import getCartByList


def getCartByList_handle(authorization):
    '''
    为预售下单准备数据
    :param authorization:
    :return: {"productList":[{"productId":462,"buyCount":1},{"productId":465,"buyCount":1}],"remark":""}
    '''
    result = getCartByList(authorization)

    if result.get("data") == None:
        return None
    else:
        count_cart = int(len(result["data"]["cartItemVOList"]))
        # {"productList": [{"productId": 462, "buyCount": 2}, {"productId": 465, "buyCount": 3}], "remark": ""}
        # {"productList":[{"productId":462,"buyCount":1},{"productId":465,"buyCount":1}],"remark":""}
        product_dict = {}
        productList = []
        for c_car in range(count_cart):
            product = {}
            productId = result["data"]["cartItemVOList"][c_car]["productId"]
            count = result["data"]["cartItemVOList"][c_car]["count"]
            product["productId"] = productId
            product["buyCount"] = count
            productList.append(product)
        product_dict["productList"] = productList
        product_dict["remark"] = ""
        return product_dict
