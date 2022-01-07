import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
def data_str_proc(data):
    '''
    对data进行统一处理【非json格式，传输为字符串】
    :param data:
    :return:
    '''
    data = str(data).replace("'", '\"')
    return data
