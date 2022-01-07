import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
import random


def order_proc(address):
    '''
    处理订单地址：
        "receiveAddr": "九龙路小店路121号",
        "receiveAddrLatitude": "29.62373000",
        "receiveAddrLongitude": "106.47780000",
        "receiveName": "小秦",
        "receivePhone": "13212345678"
    :return:address
    '''
    data_count = int(len(address["data"]))
    index = random.randint(0, data_count - 1)
    if data_count == 1:
        locationArea = address["data"][0]["locationArea"]
        roughAddress = address["data"][0]["roughAddress"]
        detailAddress = address["data"][0]["detailAddress"]
        receiveAddrLatitude = address["data"][0]["lat"]
        receiveAddrLongitude = address["data"][0]["lng"]
        receiveName = address["data"][0]["receiveName"]
        receivePhone = address["data"][0]["receivePhone"]
        receiveAddr = locationArea + roughAddress + detailAddress
        return receiveAddr, receiveAddrLatitude, receiveAddrLongitude, receiveName, receivePhone
    locationArea = address["data"][index]["locationArea"]
    roughAddress = address["data"][index]["roughAddress"]
    detailAddress = address["data"][index]["detailAddress"]
    receiveAddrLatitude = address["data"][index]["lat"]
    receiveAddrLongitude = address["data"][index]["lng"]
    receiveName = address["data"][index]["receiveName"]
    receivePhone = address["data"][index]["receivePhone"]
    receiveAddr = locationArea + roughAddress + detailAddress
    return receiveAddr, receiveAddrLatitude, receiveAddrLongitude, receiveName, receivePhone
