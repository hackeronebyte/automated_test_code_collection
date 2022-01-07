import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
import requests
import json
from tools.logconfig.logingconfig import loging
from tools.operaExcel import OperaExcel
from tools.get_time import get_now_time
from tools.exception_msg_handle import exception_msg_handle
from tools.test_dingSendMessage import test_dingSendMessage


def request_result_write(url="", header="", data="", result=""):
    '''
    将每次请求数据和结果写入excel方便日志追踪
    :param url:
    :param header:
    :param data:
    :param result:
    :return:
    '''
    file_path = OperaExcel.create_excel()
    result = json.loads(result.text)
    #
    if "message" in result:
        msg_str = str(result['message']).split("(")[0]
        with open(file_system_path() + "/tools/fail_keyword.txt", "r", encoding="utf-8") as f:
            for keyword in f.readline().split(","):
                if msg_str.find(keyword) != -1:
                    loging("接口出现问题,及时验证并修复！")
                    # 结果异常发送邮件
                    msg = exception_msg_handle(url, header, data, result)
                    # send_mail_result(msg)
                    test_dingSendMessage(msg)
                    # dingSendMessage(msg)




    else:
        loging("返回结果没有message!")
        loging("返回结果没有message!")
        loging("返回结果没有message!")
        loging("重要的事情说三遍！！！")
    lines = OperaExcel.get_lines(file_path)
    OperaExcel.request_result(lines + 1, get_now_time(), url, str(header), str(data), str(result), str(result["code"]),
                              file_path)


def request_url(url):
    '''
    组装url "http://testtest.test.com/wsd-interface/" + url
    :param url:
    :return: url
    '''
    file_url = file_system_path() + "/api/request_url.txt"
    # file_url = "../../api/request_url.txt"
    with open(file_url, "r", encoding="utf-8") as f:
        url_header = f.read()
    url = url_header + url
    return url


def requests_get(url):
    '''
    处理单个get请求
    :param url:
    :return: result
    '''
    result = requests.get(request_url(url))
    request_result_write(url=url, result=result)
    loging(result)

    return json.load(result.text)


def requests_get_header(url, header):
    '''
    处理get带有header
    :param url:
    :param header:
    :return: result
    '''
    url = request_url(url)
    loging(url)
    loging(header)
    result = requests.get(url=url, headers=header)
    loging(result.text)
    request_result_write(url=url, header=header, result=result)
    return json.loads(result.text)


def requests_post_excel(url, header, data):
    '''
    处理excel post请求
    :param url:
    :param header:
    :param data:
    :return:
    '''
    url = request_url(url)
    loging(url)
    loging(str(header).replace("\n", "").replace(" ", ""))
    loging(str(data).replace("\n", "").replace(" ", ""))
    header = json.loads(header)
    data = json.loads(data)
    data = json.dumps(data)
    result = requests.post(url=url, data=data, headers=header)
    loging(result.text)
    request_result_write(url=url, header=header, data=data, result=result)
    return json.loads(result.text)


def requests_post(url, header, data):
    '''
    处理psot请求
    :param url:
    :param header:
    :param data:
    :return: result
    '''
    url = request_url(url)
    loging(url)
    loging(header)
    loging(data)
    result = requests.post(url=url, data=data, headers=header)
    loging(result.text)
    request_result_write(url=url, header=header, data=data, result=result)
    return json.loads(result.text)


if __name__ == '__main__':
    request_result_write()
    # with open(file_system_path() + "/tools/fail_keyword.txt", "r", encoding="utf-8") as f:
    #     for keyword in f.readline().split(","):
    #         print(keyword)
