#!/usr/bin/python
# vim: set fileencoding=utf-8 noet ts=8 sw=8 sts=8 :

import controller, arduino
from threading import Thread
# from controller import *



def join_alive_threads(thread_list):
	for thread in thread_list:
		if not thread.is_alive():
			thread_list.remove(thread)
			print("Removed thread %" % thread)
		thread.join(1)
	pass


def ArduinoHypervisor():
	"""This is the master class for the arduino controllers"""
	arduino_devices = arduino.device_list()
	
	# Take all controllers:
	modules = controller.load_all()
	workers = {}
	for key, module in modules.iteritems():
		arduino_id = module.arduino_id
		if arduino_id in workers:
			workers[arduino_id].append(cobj)
		else:
			workers[arduino_id] = [cobj]
	
	# Take all devices:
	for device in arduino_devices:
		obj = Arduino(device)
		obj_id = obj.get_id()
		
		""" And assign each to a worker """
		for worker in workers[obj_id]:
			worker.use_arduino(obj)

	arduino_workers = []
	for arduino_id, worker_list in workers.iteritems():
		for i in worker_list:
			arduino_workers.append(Thread(target=i.run))

	for worker in arduino_workers:
		worker.start()

	join_alive_threads(arduino_workers)

	return None



