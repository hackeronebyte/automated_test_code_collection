import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from order_handle.address.getAllStoresByLocation import getAllStoresByLocation
from order_handle.address.getAddressList import getAddressList
from order_handle.address.addAddress import addAddress
from order_handle.address.modifyAddress import modifyAddress
from order_handle.address.removeAddress import removeAddress
from tools.logconfig.logingconfig import loging


def address_handle(authorization):
    loging("收货地址增删改查".center(100, "*"))
    getAllStoresByLocation(authorization)
    getAddressList(authorization)
    addAddress(authorization)
    modifyAddress(authorization)
    removeAddress(authorization)


if __name__ == '__main__':
    authorization = "1e15634577304a8f90e9cfc3d281b2983153ebec73b66c743bb880be26cc47a2"
    address_handle(authorization)
