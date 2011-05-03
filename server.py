#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=8 sw=8 sts=8 :

############# DAEMON CODE ##############
########################################
arduinos = []

WEBPORT = 3000
BAUDRATE = 9600

import os, sys, re

import asyncore
import socket


class FrontendConnector(asyncore.dispatcher_with_send):

	def handle_read(self):
		data = self.recv(8192)
		if data:
			self.send(data)

class FrontendConnector(asyncore.dispatcher):

	def __init__(self, host, port):
		asyncore.dispatcher.__init__(self)
		self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
		self.set_reuse_addr()
		self.bind((host, port))
		self.listen(5)

	def handle_accepted(self, sock, addr):
		print('Incoming connection from %s' % repr(addr))
		handler = FrontendConnector(sock)


def FrontendServer():
	server = FrontendConnector('localhost', WEBPORT);
	asyncore.loop()


def get_arduinos() :
	if(not os.path.isdir('/dev')):
		raise EnvironmentError('You have no /dev dir!')

	p_devs = os.listdir('/dev');
	prog = re.compile('tty');
	p_devs = [device for device in p_devs if None != prog.match(device) ]

	## Order the devices:
	def query_and_order_arduinos(arduino_list):
		return arduino_list
	
	return query_and_order_arduinos(p_devs)



def ArduinoHypervisor():
	"""This is the master class for the arduino controllers"""
	arduino_devices = get_arduinos()
	return None



def main():
	# Spawn threads
	from multiprocessing import Process
	frontend = Process(target=FrontendServer)
	arduino_ctl = Process(target=ArduinoHypervisor)
	
	frontend.start()
	arduino_ctl.start()
	
	frontend.join()
	arduino_ctl.join()



