import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from tools.order_tools.data_header_format_handle import get_header
from api.requests_api import requests_get_header
from order_handle.address.getAddressList import getAddressList
from tools.order_tools.removeAddress_handle import removeAddress_handle


def removeAddress(authorization):
    result = getAddressList(authorization)
    id = removeAddress_handle(result)
    url = "user/userAddress/removeAddress/" + str(id)
    header = get_header(authorization)
    requests_get_header(url, header)


if __name__ == '__main__':
    authorization = "1e15634577304a8f90e9cfc3d281b2983153ebec73b66c743bb880be26cc47a2"
    removeAddress(authorization)
