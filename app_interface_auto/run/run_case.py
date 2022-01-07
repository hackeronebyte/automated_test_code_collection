import os, sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import unittest
from tools.file_system_path import file_system_path

test_dir = file_system_path() + "/case"

# assiic
discover = unittest.defaultTestLoader.discover(test_dir, pattern="test*.py")

if __name__ == '__main__':
    runner = unittest.TextTestRunner()
    runner.run(discover)
