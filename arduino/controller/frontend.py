#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=4 sw=4 sts=4 tw=79 :

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


