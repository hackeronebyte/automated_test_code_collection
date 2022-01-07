import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from api.requests_api import requests_post_excel
from tools.operaExcel import OperaExcel
from tools.excel_results_status import excel_results_status
from tools.logconfig.logingconfig import loging
from order_handle.addCartItem import addCartItem
from tools.get_time import get_now_time_y_m_d
from tools.get_time import get_now_time
import unittest
import traceback
from tools.send_mail import send_mail
import os
from tools.run_result_handle import cancelorder_add
from tools.run_result_handle import order_result_statistics
from order_handle.deleteOrder import deleteOrder
from order_handle.address.address_handle import address_handle
from order_handle.presell.presell_handle import presell_handle
from order_handle.groupbuying.groupbuying_handle import groupbuying_handle
from tools.dingSendMessage import dingSendMessage
from order_handle.deleteCartItems import deleteCartItems

# 用户登录

file_system_path = file_system_path()


class Test_order_login(unittest.TestCase):

    def setUp(self):
        with open(file_system_path + "/tools/order_tools/cancelOrder_ID.txt", "w", encoding="utf-8") as f:
            f.write("")
        loging("test_order_login start .....")

    def test_login(self):

        ticket = "null"
        try:
            success = 0
            fail = 0
            file_path = file_system_path + "/case_data_file/login.xlsx"
            # 5 11
            lines_count = OperaExcel.get_lines(file_path)
            for lines in range(lines_count - 1):
                lines += 1
                is_run = OperaExcel.get_cell(file_path, lines, 0)
                if is_run == "Y":
                    method = OperaExcel.get_cell(file_path, lines, 4)
                    if method == "POST":
                        url = OperaExcel.get_cell(file_path, lines, 5)
                        header = OperaExcel.get_cell(file_path, lines, 6)
                        data = OperaExcel.get_cell(file_path, lines, 7)
                        # sendMsg(data)
                        res = requests_post_excel(url, header, data)
                        # 报文返回的实际结果
                        response_status = res["code"]
                        # excel预期结果
                        results_status = excel_results_status(OperaExcel.get_cell(file_path, lines, 8))
                        if response_status == results_status["code"]:
                            b = True
                            OperaExcel.save_kp(b, lines + 1, 10, str(res), file_path)
                            loging(OperaExcel.get_cell(file_path, lines, 1) + "    Success")
                            # 添加购物车 从这里开始 需要从实际结果得到Authorization
                            ticket = res["data"]["ticket"]
                            loging(ticket)
                            addCartItem(ticket)
                            success += 1

                        else:
                            b = False
                            OperaExcel.save_kp(b, lines + 1, 10, str(res), file_path)
                            loging(OperaExcel.get_cell(file_path, lines, 1) + "    Fail")
                            fail += 1
                            loging("预期结果: " + str(results_status[
                                                      "code"]) + "实际结果: " + str(
                                response_status) + ",预期结果与实际结果不符用，例执行失败(Fail)")
                        # self.assertEqual(results_status["code"], response_status, msg="预期结果与实际结果不符")
        except:
            deleteCartItems(ticket)
            path = file_system_path + "/tools/logs/" + get_now_time_y_m_d() + "/except_logs"
            isExists = os.path.exists(path)
            if not isExists:
                # 如果不存在则创建目录
                # 创建目录操作函数
                os.makedirs(path)
            tra = str(traceback.format_exc())
            str_except = '未知错误异常：' + tra
            loging(str_except)
            with open(path + "/" + get_now_time_y_m_d() + ".txt", "a+", encoding="utf-8") as f:
                f.write(str(get_now_time()) + " " + str_except)
                f.write("\r\n")
            # send_mail(str_except)
            dingSendMessage(str_except)



        else:
            loging("未出现异常继续执行".center(100, "*"))
            loging("ticket:" + ticket)
            if ticket != "null":
                # 取消订单
                cancelorder_add(ticket)
                # 订单删除
                deleteOrder(ticket)
                # 修改搜索地址
                address_handle(ticket)
                # 预售操作流程
                presell_handle(ticket)
                # 团拼商品
                groupbuying_handle(ticket)
            # 测试运行结果统计
            order_result_statistics(success, fail)

    def tearDown(self):
        loging("test_order_login end .....")
        loging("购买结束".center(100, "-"))
        loging("购买结束".center(100, "-"))
        loging("购买结束".center(100, "-"))
        loging("")
        loging("")


if __name__ == '__main__':
    unittest.main()
