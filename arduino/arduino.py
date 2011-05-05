#!/bin/python
# vim: set fileencoding=utf-8 noet ts=4 sw=4 sts=4 tw=79 :

import os, re, time

import serial
from constants import *

class Arduino:
	
	def __init__(self, serialport):
		"""Takes the string of the serial port
		and connects to that port, binding the
		Arduino object to it.
		"""
		print(serialport)
		try:
			self.serialport = serial.SerialPort(serialport, 9600)
			self.fd = self.serialport.fd
			self.error = False
			self.id = None
		except:
			self.error = True
			self.id = -666
			raise

	def read_byte(self, block=False):
		print 'Lendo byte...'
		d = os.read(self.fd, 1)
		print 'Lido byte "%s"' % d
		
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
		if self.error:
			return self.id

		if self.id != None:
			return self.id

		# Consume all bytes for this query
		while self.read_byte(block=False) != None:
			pass

		self.write_byte(QUERY_IDENT)
		self.id = self.read_byte(True)
		return self.id



def device_list():
	if not os.path.isdir('/dev'):
		raise EnvironmentError('You have no /dev dir!')

	devices = os.listdir('/dev')
	arduino_re = re.compile('tty\.usbserial')

	# Get the Arduino's for each device
	devices = [ Arduino('/dev/' + (device)) for device in devices if arduino_re.match(device) != None ]
	return devices
	

