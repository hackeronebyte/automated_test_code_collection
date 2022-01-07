import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.logconfig.logingconfig import loging


def show_order_log(data_dict):
    loging("下单时间:" + data_dict["run_time"])
    loging("订单号:" + data_dict["order_number"])
    data_count = int(len(data_dict["data"]))
    for d_count in range(data_count):
        show_str = \
            "name:" + str(data_dict["data"][d_count]["name"]) + \
            ", skuId:" + str(data_dict["data"][d_count]["skuId"]) + \
            ", id:" + str(data_dict["data"][d_count]["id"]) + \
            ", count:" + str(data_dict["data"][d_count]["count"]) + \
            ", salePrice:" + str(data_dict["data"][d_count]["salePrice"]) + \
            ", totalPrice:" + str(data_dict["data"][d_count]["totalPrice"])
        loging(show_str)

    loging("商品金额:" + str(data_dict["productDiscountAmount"]))
    loging("包装费:" + str(data_dict["packingAmount"]))
    loging("运费:" + str(data_dict["freightAmount"]))
    loging("优惠金额:" + str(data_dict["discountAmount"]))
    loging("优惠券金额:" + str(data_dict["couponDiscountPrice"]))
    loging("订单金额:" + str(data_dict["cart_totalPrice"]))
    loging("实付金额:" + str(data_dict["productTotalAmount"]))


if __name__ == '__main__':
    show_order_log(data_dict={'run_time': '2021-02-10 09:53:01', 'data': [
        {'name': '草莓罐头（箱-6）', 'skuId': 115029115185, 'id': 23750, 'count': 1, 'salePrice': 16.0, 'totalPrice': 16.0}],
                              'cart_totalPrice': 47.82, 'code': 200, 'order_number': '4923435601132850943',
                              'productTotalAmount': 41.82, 'packingAmount': 1, 'freightAmount': 5, 'discountAmount': 0,
                              'couponDiscountPrice': 0.0, 'message': '操作成功'}
                   )
