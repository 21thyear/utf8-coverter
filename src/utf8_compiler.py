"""
	UTF-8 to Windows 1251 (CP 1251)
	Author: 21th year
	Links: github.com/21thyear
"""

import os
from sys import *
import chardet




def reverseText():
	with open("main.pwn", 'rb') as f:
	    raw_data = f.read()
	    result = chardet.detect(raw_data)

	encoding = result['encoding']
	decoded_content = raw_data.decode(encoding)

	utf8_content = decoded_content.encode('utf-8')
	print(utf8_content.decode('utf-8'))
reverseText()
