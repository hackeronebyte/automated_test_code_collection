import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_post
from tools.order_tools.modifyAddress_handle import modifyAddress_hanle
from order_handle.address.getAddressList import getAddressList
from tools.order_tools.data_str_proc import data_str_proc


def modifyAddress(authorization):
    result = getAddressList(authorization)

    url = "user/userAddress/modifyAddress"
    header = get_header(authorization)
    m_data = modifyAddress_hanle(result)
    data = data_str_proc(m_data).encode("utf-8")
    requests_post(url, header, data)


if __name__ == '__main__':
    authorization = "1e15634577304a8f90e9cfc3d281b2983153ebec73b66c743bb880be26cc47a2"
    modifyAddress(authorization)
