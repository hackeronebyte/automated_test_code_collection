import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.get_time import get_now_time


def exception_msg_handle(url, header, data, result):
    msg = "自动化测试APP接口异常\r 【时间】:  " + str(get_now_time()) + "\r 【URL】:  " + str(url) + "\r 【HEADER】:  " + str(
        header) + "\r 【DATA】:  " + str(data) + "\r 【RESPONSE】:  " + str(result)
    return msg
