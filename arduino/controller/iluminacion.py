#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=4 sw=4 sts=4 tw=79 :

from arduino import constants

variables = {
	'digital' :
			{
		'in' : 
			{
				LUZ_PASILLO		: "Luz del pasillo",
				LUZ_HABITACION	: "Luz de la habitación"
			}
		}
					
digital_status = [
		"LUCES_PASILLO",
		"LUCES_HABITA1"
		]

class iluminacion:
	def __init__(self, arduino):
		self.arduino = arduino
		self.inputs = inputs
	
	def get_input(self, input):
		status = self.arduino.query_status()
		return self.unzip(status).get(input)

	def unzip(self, bytemask):
		pass # TODO : Implement

print "Iluminacion controller loaded"

def run():
	pass

