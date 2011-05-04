#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=4 sw=4 sts=4 tw=79 :

from arduino.constants import *

arduino_id = 4

variables = { \
		'digital' : \
		{ \
			'in' : \
			{ \
				LUZ_PASILLO		: "Luz del pasillo", \
				LUZ_HABITACION	: "Luz de la habitación" \
			} \
		} \
}

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

_iluminacion = None

def run():
	pass

def use_arduino(arduino):
	"""Sets the module to use the arduino specified"""
	_iluminacion = iluminacion(arduino)

