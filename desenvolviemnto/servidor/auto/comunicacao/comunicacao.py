import serial
import RPi.GPIO as GPIO

class Comunicacao(object):
	
	serial = serial.Serial('/dev/ttyAMAO',4800,timeout=1)
	
	def __init__(self):
		serial.open()

	def sendComand(self,comando):
		ser.write(comando)


	