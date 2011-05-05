#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=4 sw=4 sts=4 tw=79 :

import controller, arduino
import threading
import multiprocessing

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
		def __init__(self, arduino, parentcv):
			self.arduino = arduino
			self.parentcv = parentcv
			self.in_queue = multiprocessing.Queue()
			self.out_queue = multiprocessing.Queue()
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
			global DAEMON_RUNNING

			while DAEMON_RUNNING:
				try:
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
						self.parentcv.notify()

					# Do we have to send data?
					if not self.out_queue.empty():
						# Send one message
						try:
							msg = self.out_queue.get_nowait()
							self.arduino.write(msg)
							self.out_queue.task_done()
						except:
							print 'Data was not avaliable in out_queue'

				except KeyboardInterrupt:
					DAEMON_RUNNING = False
			pass

		def getListeners(self):
			return self.listeners

		def wakeupListeners(self):
			"""To be done by the parent
			Wakes up all the listeners involved in the first message
			of the in_queue of this controller
			"""
			while not self.in_queue.empty():
				msg = self.in_queue.get(block=False)
				for listener in self.listeners:
					listener.recv_msg(msg, self.queue_put)
				self.in_queue.task_done()
			pass

	## End of class ArduinoHandler
	def __init__(self, device_list):
		self.arduino_handlers = {}
		self.cv = threading.Condition()

		print 'Lista de dispositivos: '
		print device_list
		for device in device_list:
			try:
				device = arduino.Arduino(device)
			except Exception as e:
				print('Error while initializing device %s: %s' % (device, e))
				continue
			id = device.get_id()
			self.arduino_handlers[id] = device
			print 'Got device with ID=%d' % id

	def get_handler(self, id):
		if self.arduino_handlers.has_key(id):
			return self.arduino_handlers[id]
		else:
			return None

	def loop(self):
		"""This function runs a multiprocessing queue
		so that each arduino handler won't lock while
		waiting from info to be done
		"""
		global DAEMON_RUNNING

		pool = multiprocessing.Pool(processes=6)
		while DAEMON_RUNNING:
			self.cv.acquire()
			try:
				self.cv.wait(10)
				for arduino in self.arduino_handlers:
					if not arduino.in_queue().empty():
						for listener in arduino.getListeners():
							pool.apply_async(listener.recv_msg, [msg,
								arduino.in_queue])

			except KeyboardInterrupt:
				DAEMON_RUNNING = False
			finally:
				self.cv.release()
		pass


	def run(self):
		"""This funcion runs each arduinoHandler in a separate thread.
		Then waits for processing from them to call a pool of workers
		(see self.loop(self))
		"""

		threads = []

		for (id, obj) in self.arduino_handlers.iteritems():
			myobj = self.ArduinoHandler(obj, self.cv)
			thread = threading.Thread(target=myobj.run)
			threads.append(thread)

		for thread in threads:
			thread.start()

		try:
			self.loop()
		except KeyboardInterrupt:
			pass

		join_alive_threads(threads)


def run():
	hypervisor = ArduinoHypervisor(arduino.device_list())

	# Take all controllers:
	modules = controller.load_all()
	workers = {}
	for module_name, module in modules.iteritems():
		arduino_id = module.arduino_id
		if arduino_id in workers:
			workers[arduino_id].append(module)
		else:
			workers[arduino_id] = [module]

	for arduino_id, mod_list in workers.iteritems():
		for module in mod_list:
			handler = hypervisor.get_handler(arduino_id)
			if handler != None:
				handler.addListener(module)

	hypervisor.run()
	return None



