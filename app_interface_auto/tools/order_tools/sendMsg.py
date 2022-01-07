from tools.order_tools.data_str_proc import data_str_proc
from api.requests_api import requests_post
import json


def sendMsg(data):
    data = json.loads(data)
    mobile = data['mobile']
    url = "user/sms/send/sendMsg"
    headers = {
        "device-id": "D37B97CBF381AF501366465BFE85A64E9E4F720B",
        "chan": "test_android",
        "content-type": "application/json",
        "store-id": "99999",
        "store-code": "0001",
        "Authorization": ""
    }
    data = data_str_proc({"smsType": "1", "mobile": str(mobile)})
    requests_post(url, headers, data)
