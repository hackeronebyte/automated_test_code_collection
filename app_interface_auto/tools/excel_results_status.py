import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
import json


def excel_results_status(results):
    '''
    获取excel预期结果
    '''
    return json.loads(results)
