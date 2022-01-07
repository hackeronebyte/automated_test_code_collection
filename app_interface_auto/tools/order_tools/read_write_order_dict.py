import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
import json
from tools.operaExcel import OperaExcel
from tools.order_tools.show_order_log import show_order_log
from tools.file_system_path import file_system_path


def read_write_order_dict(file_name, data_dict, result_CartPriceDetailNew):
    # {"code": 200, "data": "4923435601132850943", "message": "操作成功"}
    with open(file_name, "r", encoding="utf-8") as f:
        dict_str = str(f.readline()).replace("'", '"')
        dict_str = json.loads(dict_str)
        dict_str["code"] = data_dict["code"]
        if "data" in data_dict:
            dict_str["order_number"] = data_dict["data"]
        else:
            dict_str["order_number"] = ""
        # 商品金额
        dict_str["productDiscountAmount"] = result_CartPriceDetailNew["data"]["productDiscountAmount"]
        # 包装费
        dict_str["packingAmount"] = result_CartPriceDetailNew["data"]["packingAmount"]
        # 运费 freightAmount
        dict_str["freightAmount"] = result_CartPriceDetailNew["data"]["freightAmount"]
        # 优惠金额
        dict_str["discountAmount"] = result_CartPriceDetailNew["data"]["discountAmount"]
        # 优惠券金额
        # if "couponDiscountPrice" in result_CartPriceDetailNew["data"]["promotionVO"]:
        # KeyError: 'promotionVO'
        if "promotionVO" in result_CartPriceDetailNew["data"]:
            if "couponDiscountPrice" in result_CartPriceDetailNew["data"]["promotionVO"]:
                dict_str["couponDiscountPrice"] = result_CartPriceDetailNew["data"]["promotionVO"][
                    "couponDiscountPrice"]
            else:
                dict_str["couponDiscountPrice"] = float(0.00)
        else:
            dict_str["couponDiscountPrice"] = float(0.00)
        # 订单金额
        dict_str["cart_totalPrice"] = result_CartPriceDetailNew["data"]["orderTotalAmount"]
        # 实付金额
        dict_str["productTotalAmount"] = result_CartPriceDetailNew["data"]["productTotalAmount"]
        dict_str["message"] = data_dict["message"]
        file_name_excel = file_system_path() + "/case_data_file/order_run_result.xlsx"
        lines = OperaExcel.get_lines(file_name_excel)
        OperaExcel.save_order_result(lines + 1, dict_str["run_time"], dict_str["order_number"], str(dict_str["data"]),
                                     dict_str["productTotalAmount"], dict_str["packingAmount"],
                                     dict_str["freightAmount"],
                                     dict_str["discountAmount"], dict_str["couponDiscountPrice"],
                                     dict_str["cart_totalPrice"], dict_str["productTotalAmount"],
                                     dict_str["code"], dict_str["message"],
                                     file_name_excel)
    show_order_log(dict_str)


def read_write_order_dict_success(file_name, data_dict, result_CartPriceDetailNew, orderDetailInfo,
                                  cashierPaymentresult):
    # {"code": 200, "data": "4923435601132850943", "message": "操作成功"}
    # file_dict_name, result, result_CartPriceDetailNew, orderDetailInfo
    with open(file_name, "r", encoding="utf-8") as f:
        dict_str = str(f.readline()).replace("'", '"')
        dict_str = json.loads(dict_str)
        dict_str["code"] = data_dict["code"]
        if "data" in data_dict:
            dict_str["order_number"] = data_dict["data"]
        else:
            dict_str["order_number"] = ""
        # 商品金额
        dict_str["productDiscountAmount"] = orderDetailInfo["data"]["orderInfoVO"]["saleAmount"]
        # 包装费
        dict_str["packingAmount"] = orderDetailInfo["data"]["orderInfoVO"]["packageAmount"]
        # 运费 freightAmount
        dict_str["freightAmount"] = orderDetailInfo["data"]["orderInfoVO"]["fare"]
        # 优惠金额
        dict_str["discountAmount"] = orderDetailInfo["data"]["orderInfoVO"]["discountAmount"]
        # 优惠券金额
        dict_str["couponDiscountPrice"] = float(0.00)
        # 订单金额
        dict_str["cart_totalPrice"] = float(0.00)
        # 实付金额
        dict_str["productTotalAmount"] = orderDetailInfo["data"]["orderInfoVO"]["payAmount"]
        dict_str["message"] = data_dict["message"]
        file_name_excel = file_system_path() + "/case_data_file/order_run_result.xlsx"
        lines = OperaExcel.get_lines(file_name_excel)
        OperaExcel.save_order_result(lines + 1, dict_str["run_time"], dict_str["order_number"], str(dict_str["data"]),
                                     dict_str["productDiscountAmount"], dict_str["packingAmount"],
                                     dict_str["freightAmount"],
                                     dict_str["discountAmount"], dict_str["couponDiscountPrice"],
                                     dict_str["cart_totalPrice"], dict_str["productTotalAmount"],
                                     cashierPaymentresult["code"], cashierPaymentresult["message"],
                                     file_name_excel)
    show_order_log(dict_str)


def read_write_order_dict_cancelOrder(file_name, data_dict, result_CartPriceDetailNew, result_cancelOrder):
    # {"code": 200, "data": "4923435601132850943", "message": "操作成功"}
    with open(file_name, "r", encoding="utf-8") as f:
        dict_str = str(f.readline()).replace("'", '"')
        dict_str = json.loads(dict_str)
        dict_str["code"] = data_dict["code"]
        if "data" in data_dict:
            dict_str["order_number"] = data_dict["data"]
        else:
            dict_str["order_number"] = ""
        # 商品金额
        dict_str["productDiscountAmount"] = result_CartPriceDetailNew["data"]["productDiscountAmount"]
        # 包装费
        dict_str["packingAmount"] = result_CartPriceDetailNew["data"]["packingAmount"]
        # 运费 freightAmount
        dict_str["freightAmount"] = result_CartPriceDetailNew["data"]["freightAmount"]
        # 优惠金额
        dict_str["discountAmount"] = result_CartPriceDetailNew["data"]["discountAmount"]
        # 优惠券金额
        #   if "couponDiscountPrice" in result_CartPriceDetailNew["data"]["promotionVO"]:
        # KeyError: 'promotionVO'
        if "promotionVO" in result_CartPriceDetailNew["data"]:
            if "couponDiscountPrice" in result_CartPriceDetailNew["data"]["promotionVO"]:
                dict_str["couponDiscountPrice"] = result_CartPriceDetailNew["data"]["promotionVO"][
                    "couponDiscountPrice"]
            else:
                dict_str["couponDiscountPrice"] = float(0.00)
        else:
            dict_str["couponDiscountPrice"] = float(0.00)
        # 订单金额
        dict_str["cart_totalPrice"] = result_CartPriceDetailNew["data"]["orderTotalAmount"]
        # 实付金额
        dict_str["productTotalAmount"] = result_CartPriceDetailNew["data"]["productTotalAmount"]
        dict_str["message"] = data_dict["message"]
        file_name_excel = file_system_path() + "/case_data_file/order_run_result.xlsx"
        lines = OperaExcel.get_lines(file_name_excel)
        OperaExcel.save_order_result(lines + 1, dict_str["run_time"], dict_str["order_number"], str(dict_str["data"]),
                                     dict_str["productTotalAmount"], dict_str["packingAmount"],
                                     dict_str["freightAmount"],
                                     dict_str["discountAmount"], dict_str["couponDiscountPrice"],
                                     dict_str["cart_totalPrice"], dict_str["productTotalAmount"],
                                     result_cancelOrder["code"], result_cancelOrder["message"],
                                     file_name_excel)
    show_order_log(dict_str)


def write_order_dict(file_name, data_dict):
    with open(file_name, "w", encoding="utf-8") as f:
        f.write(str(data_dict))


if __name__ == '__main__':
    result = {"code": 200, "data": "4923435601132850943", "message": "操作成功"}
    result_CartPriceDetailNew = {
        "code": 200,
        "data": {
            "productDiscountAmount": 41.82,
            "differenceAmount": 17.18,
            "selfRaisedPrice": 20,
            "exemptionAmount": 59,
            "freightAmount": 5,
            "deliveryRule": "1: 20元起送，配送订单重量≤10kg，距离≤3km，5元运费；<br/>2: 重量超出10kg部分，每增加1kg加1元服务费；<br/>3: 距离超出3km部分，每增加1km加1元服务费；<br/>4: 券后实付59元，10KG内免运费；",
            "orderTotalAmount": 47.82,
            "productTotalAmount": 41.82,
            "deliveryAmount": 20,
            "packingAmount": 1,
            "discountAmount": 0,
            "promotionVO": {
                "unAvailableSkuCouponList": [],
                "availableSkuCouponList": {
                    "singleCouponList": []
                }
            }
        },
        "message": "操作成功"
    }
    read_write_order_dict("order_dict.txt", result, result_CartPriceDetailNew)
