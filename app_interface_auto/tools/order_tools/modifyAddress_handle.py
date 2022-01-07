import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
def modifyAddress_hanle(result):
    if int(len(result["data"])) != 0:
        data = result["data"][0]
        data["receiveName"] = data["receiveName"] + "1"
        data["receivePhone"] = "13312345678"
        data["roughAddress"] = data["roughAddress"] + "_测试"
        data["detailAddress"] = data["detailAddress"] + "11"
        data["tag"] = "3"
        data["hasStore"] = "false"
        return data
    else:
        return "null"
