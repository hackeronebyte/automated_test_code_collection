import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
def removeAddress_handle(result):
    if int(len(result["data"])) != 0:
        return result["data"][0]["id"]
    else:
        return "null"