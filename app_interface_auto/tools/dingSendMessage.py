import requests
import json
from tools.logconfig.logingconfig import loging


def dingSendMessage(msg):
    # 请求的URL，WebHook地址
    url = "https://oapi.dingtalk.com/robot/send?access_token=e72e56957ea4304795f58ff7"
    # 构建请求头部
    header = {
        "Content-Type": "application/json",
        "Charset": "UTF-8"
    }
    # 构建请求数据
    # tex = "接口测试写信息"
    message = {

        "msgtype": "text",
        "text": {
            "content": msg
        },
        "at": {

            "isAtAll": True
        }

    }
    # 对请求的数据进行json封装
    message_json = json.dumps(message)
    # 发送请求
    info = requests.post(url=url, data=message_json, headers=header)
    # 打印返回的结果
    loging("钉钉机器人报警提示" + str(info.text))


if __name__ == "__main__":
    dingmessage()
