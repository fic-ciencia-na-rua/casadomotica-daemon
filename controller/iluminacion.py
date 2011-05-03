#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=8 sw=8 sts=8 :

from arduino import constants

digital_status = [
		"LUCES_PASILLO",
		"LUCES_HABITA1"
		]

class Iluminacion:
	def __init__(self, Arduino a):
		self.arduino = a
		self.inputs = inputs
	
	def get_input(self, input):
		status = self.arduino.query_status()
		return self.unzip(status).get(input)

	def unzip(self, bytemask):
		pass # TODO : Implement


