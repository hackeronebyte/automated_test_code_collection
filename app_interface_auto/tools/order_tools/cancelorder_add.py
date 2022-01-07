import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.logconfig.logingconfig import loging


def cancelorder_add():
    '''
    处理再次购买订单数据 获取 orderID并返回
    :return: orderID
    '''
    # file_orderid ="cancelOrder_ID.txt"
    file_orderid = file_system_path() + "/tools/order_tools/cancelOrder_ID.txt"
    with open(file_orderid, "r", encoding="utf-8") as f:
        lines = f.readlines()
        lines_count = int(len(lines))
        if lines_count > 0:
            orderID = lines[lines_count - 1].replace("\n", "")
            loging("订单再次购买 orderID:" + str(orderID))
            lines.remove(lines[lines_count - 1])
            with open(file_orderid, "w", encoding="utf-8") as f:
                f.write("")
            for line in lines:
                with open(file_orderid, "a+", encoding="utf-8") as f:
                    f.write(line)
            return orderID
        else:
            loging("订单再次购买 orderID: null")
            return "null"


if __name__ == '__main__':
    print("=======", cancelorder_add())
