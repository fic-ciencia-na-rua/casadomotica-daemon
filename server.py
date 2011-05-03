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


def ArduinoHypervisor():
	"""This is the master class for the arduino controllers"""
	arduino_devices = arduino.arduino_list()

	# TODO: Implement magic here
	# arduino_workers = [ arduino.worker for arduino in arduino_devices ]
	arduino_workers = []
	arduino_workers = [ Process(target=arduino.worker) for arduino in arduino_workers ]

	for worker in arduino_workers:
		worker.start()

	for worker in arduino_workers:
		worker.join()

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



