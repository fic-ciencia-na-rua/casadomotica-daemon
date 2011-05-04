#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=4 sw=4 sts=4 tw=79 :

############# DAEMON CODE ##############
########################################
arduinos = []

WEBPORT = 3000
BAUDRATE = 9600

import os, sys, re

import asyncore
import socket

import arduino.hypervisor


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

def main():
	# Spawn threads
	from multiprocessing import Process
	frontend = Process(target=FrontendServer)
	arduino_ctl = Process(target=arduino.hypervisor.run)

	#frontend.start()
	arduino_ctl.start()

	#frontend.join()
	arduino_ctl.join()


if __name__ == "__main__":
	print 'Executing main thread...'
	main()



