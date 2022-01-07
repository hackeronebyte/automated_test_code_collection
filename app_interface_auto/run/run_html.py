import sys

sys.path.append("D:\pythonworkspace\order_interface_atuo")
import unittest
import time
from tools.HTMLTestRunner import HTMLTestRunner
from tools.send_mail_html import *

if __name__ == '__main__':
    test_dir = "../case"
    # 第一步：组装测试套件
    discover = unittest.defaultTestLoader.discover(test_dir, pattern='test_*.py')
    # 第二步：指定报告存放路径及文件名称
    file_path = "../report/{}.html".format(time.strftime("%Y_%m_%d-%H_%M_%S"))
    # 第三步：运行测试套件并生成测试报告
    with open(file_path, "wb") as f:
        runner = HTMLTestRunner(stream=f, title="自动化测试下单接口自动化测试报告", description="自动化测试下单接口自动化测试报告 测试版本1.8")
        runner.run(discover)
        file_path = new_report("../report")
        send_mail(file_path)
