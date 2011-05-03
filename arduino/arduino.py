#!/bin/python
# vim: set fileencoding=utf-8 noet ts=8 sw=8 sts=8 :

import os, re

from . import serial
from .constants import *

class Arduino:
	
	def __init__(self, serialport):
		"""Takes the string of the serial port
		and connects to that port, binding the
		Arduino object to it.
		"""
		print(serialport)
	#	self.serialport = serial.SerialPort(serialport, 9600)
	#	self.fd = self.serialport.fd
	
	def read_byte(self, block=False):
		d = os.read(self.fd, 1)
		
		while d == "":
			if not block:
				return None
			time.sleep(0.01)
			d = os.read(self.fd, 1)

		return d

	def read_until(self, until):
		return self.serialport.read_until(until)

	def write(self, str):
		return self.serialport.write(str)

	def write_byte(self, byte):
		return self.serialport.write_byte(byte)

	def get_id(self):
		self.write(QUERY_IDENT)
		return read_byte(True)
	

def arduino_list():
	if not os.path.isdir('/dev'):
		raise EnvironmentError('You have no /dev dir!')

	devices = os.listdir('/dev')
	arduino_re = re.compile('tty\.')

	# Get the Arduino's for each device
	devices = [ Arduino('/dev/' + (device)) for device in devices if arduino_re.match(device) != None ]
	

