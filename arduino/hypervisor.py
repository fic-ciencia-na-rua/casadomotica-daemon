#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=4 sw=4 sts=4 tw=79 :

import controller, arduino
from threading import Thread
import queue

# from controller import *

DAEMON_RUNNING = True


def join_alive_threads(thread_list):
	"""This function waits for alive threads to join
	and blocks until that happens.
	In order to downgrade memory requirements, each time a
	thread joins it is removed from the thread_list
	"""
	for thread in thread_list:
		if not thread.is_alive():
			thread_list.remove(thread)
			print("Removed thread %" % thread)
		thread.join(1)
	pass

# ArduinoHypervisor is the class that handles the supervising of the N threads
# (one for each Arduino) and attaches the modules to the arduino they demand.
class ArduinoHypervisor:
	class ArduinoHandler():
		# ArduinoHandler is the class that handles each Arduino in a concurrent
		# way so inputs/outputs are nonblocking and transfered when the buffers
		# allow us to, controller-agnostic.
		def __init__(self, arduino):
			self.arduino = arduino
			self.in_queue = queue.Queue()
			self.out_queue = queue.Queue()
			self.listeners = []

		def addListener(self, callback):
			"""Adds a listener to the list of listeners to be warned about
			updates in this arduino channel
			"""
			self.listeners.append(callback)

		def queue_put(self, str):
			"""This function allows to put data on the output queue in order to
			be sent to the Arduino
			"""
			self.out_queue.put(msg, block=True)

		def run(self):
			"""Main Handler loop:

			While the daemon is started, it will read bytes from the Arduino
			serial port and send data if it is required to.
			"""
			while DAEMON_RUNNING:
				byte = self.arduino.read_byte(False)
				if byte == None:
					if self.out_queue.empty():
						sleep(0.01)
					pass
				else:
					if byte == BYTE_STX:
						msg = self.arduino.read_until(BYTE_ETX)
						msg = msg[:-1]
					else:
						msg = byte
					self.in_queue.put(msg, block=False)

				# Do we have to send data?
				if not self.out_queue.empty():
					# Send one message
					try:
						msg = self.out_queue.get_nowait()
						self.arduino.write(msg)
						self.out_queue.task_done()
					except:
						print 'Data was not avaliable in out_queue'
			pass

		def _wakeupListeners(self):
			while not self.in_queue.empty():
				msg = self.in_queue.get(block=False)
				for listener in self.listeners:
					listener.recv_msg(msg)
				self.in_queue.task_done()
			pass

	## End of class ArduinoHandler
	def __init__(self, device_list):
		self.arduino_handlers = []
		for device in device_list:
			self.arduino_handlers.append(ArduinoHandler(Arduino(device)))

	def run(self):
		"""This funcion runs each arduinoHandler in a separate thread.
		Then blocks until join from the child threads.
		"""
		threads = []
		for obj in self.arduino_handlers:
			thread.append(Thread(target=obj.run))
			thread.start()

		join_alive_threads(threads)


def run():
	hypervisor = ArduinoHypervisor(arduino.device_list())

	# Take all controllers:
	modules = controller.load_all()
	workers = {}
	for module_name, module in modules.iteritems():
		arduino_id = module.arduino_id
		if arduino_id in workers:
			workers[arduino_id].append(cobj)
		else:
			workers[arduino_id] = [cobj]

	for arduino_id, mod_list in workers.iteritems():
		for module in mod_list:
			hypervisor.get_handler(arduino_id).addListener(module)

	hypervisor.run()
	return None



