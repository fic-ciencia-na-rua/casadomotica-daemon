#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=4 sw=4 sts=4 tw=79 :

from constants import *

def parse(str):
	bytes = bytearray(str, "utf-8")
	if bytes[0] == BYTE_STX:
		# First byte is start of text
		key = bytes[1]
		value = bytes[2:(len(bytes)-1)]

		if bytes[len(bytes)-1] != BYTE_ETX:
			raise AssertionError('Arduino format is not valid: ' + \
					'No termination ETX')

	else:
		raise AssertionError('Arduino format is not valid')

	return {'key':key, 'value':value}


