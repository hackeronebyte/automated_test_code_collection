import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())


def data_header_format_handle():
    file_patch = "../text.txt"
    with open(file_patch, "r", encoding="utf-8") as f:
        reads = f.readlines()
        for re in reads:
            # print(re.split(":"))
            res = re.split(":")
            str1 = res[0]
            str2 = res[1].replace("\n", "").replace(" ", "")
            print('"' + str1 + '":' + '"' + str2 + '",')

        # print(type(reads))
        # print(reads)


def get_header(authorization):
    '''
    处理header
    :param authorization:
    :return: header
    device-id: D37B97CBF381AF501366465BFE85A64E9E4F720B
    jdstoreid: 100001
    store-code: 0001
    store-id: 99999
    storecode: 0001
    chan: test_android
    merchantid: 3
    test-version: 1.6.6
    Authorization: f65edd8e31d642898512c77e36f99a5005a9137a76068421cc33ca0ba1d4b66c
    '''
    header = {
        "chan": "test_android",
        "store-id": "99999",
        "authorization": authorization,
        "content-type": "application/json",
        "device-id": "7172CA8E066E7AF92F8B35F3139C7C11D9CA8A1F",
        "store-code": "0001",
        "storecode": "0001",
        "merchantid": "3",
        "jdstoreid": "100001",
        "test-version": "1.6.6",
    }
    return header


def get_header_not_author():
    '''
    处理header
    :param authorization:
    :return: header
    '''
    header = {
        "Connection": "keep-alive",
        "chan": "test_android",
        "store-id": "99999",
        "content-type": "application/json",
        "device-id": "7172CA8E066E7AF92F8B35F3139C7C11D9CA8A1F",
        "store-code": "0001",
        "storecode": "0001",
        "merchantid": "3",
        "jdstoreid": "100001",
        "test-version": "1.6.6",
        "authorization": "",

    }
    return header


if __name__ == '__main__':
    data_header_format_handle()
