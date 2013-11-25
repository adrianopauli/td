from controles.comunicacao import rs485
from controles.singleton import Singleton
import array

class Con(object):
	__metaclass__=Singleton
	
	def __init__(self):
		rs = rs485()
		self.rs = rs
con = Con()
class TAGS(object):
	MASTER_ADDRESS = '1'
	BYTE_START  = '#'
	BYTE_STOP   = '$'
	BYTE_SEPARATOR  = '/'
	DATA_SEPARATOR  = '?'

	ACTION_READ     = '1'
	ACTION_WRITE    = '2'
	ACTION_RESPONSE = '3'

	HARDWARE_IR       = '91'
	HARDWARE_RELE     = '92'
	HARDWARE_WEATHER  = '93'

	PROTOCOL_ADRESSES    = 0
	PROTOCOL_TYPE        = 1
	PROTOCOL_HARDWARE    = 2
	PROTOCOL_NODE_ORIGIN = 3
	PROTOCOL_DATA        = 4

	DATA_ERROR = "ERROR"
	DATA_NULL  = "null"

	NEC        = 1
	SONY       = 2
	RC5        = 3
	RC6        = 4
	DISH       = 5
	SHARP      = 6
	PANASONIC  = 7
	JVC        = 8
	SANYO      = 9
	MITSUBISHI = 10
	RAW_IR     = 11


class Protocolo(object):	

	def sendIR(self,node,ir):		
		comando =  TAGS.BYTE_START+node
		comando += TAGS.BYTE_SEPARATOR+TAGS.ACTION_WRITE
		comando += TAGS.BYTE_SEPARATOR+TAGS.HARDWARE_IR
		comando += TAGS.BYTE_SEPARATOR+TAGS.MASTER_ADDRESS
		comando += TAGS.BYTE_SEPARATOR+ir
		comando += TAGS.BYTE_STOP
		return con.rs.sendComand(comando)

	def sendRele(self,node,data):
		comando =  TAGS.BYTE_START+node		
		comando += TAGS.BYTE_SEPARATOR+TAGS.ACTION_WRITE
		comando += TAGS.BYTE_SEPARATOR+TAGS.HARDWARE_RELE
		comando += TAGS.BYTE_SEPARATOR+TAGS.MASTER_ADDRESS
		comando += TAGS.BYTE_SEPARATOR+data
		comando += TAGS.BYTE_STOP
		return con.rs.sendComand(comando)

	def sendWeather(self,node):
		comando =  TAGS.BYTE_START+node		
		comando += TAGS.BYTE_SEPARATOR+TAGS.ACTION_READ
		comando += TAGS.BYTE_SEPARATOR+TAGS.HARDWARE_WEATHER
		comando += TAGS.BYTE_SEPARATOR+TAGS.MASTER_ADDRESS
		comando += TAGS.BYTE_SEPARATOR+TAGS.DATA_NULL
		comando += TAGS.BYTE_STOP
		if con.rs.sendComand(comando):
			weather = Weather(str(self.interpreterWeather(str(con.rs.readComand()))))			
			return weather
		else:
			return None
			
	def interpreterWeather(self,comandos):		
		print(comandos)
		comandos = comandos.replace(TAGS.BYTE_START, '')
		comando = ""
		for c in comandos.split(TAGS.BYTE_STOP):
			d = c.split(TAGS.BYTE_SEPARATOR)
			if (d[TAGS.PROTOCOL_ADRESSES] == TAGS.MASTER_ADDRESS 
			and d[TAGS.PROTOCOL_HARDWARE] == TAGS.HARDWARE_WEATHER):
				return d[TAGS.PROTOCOL_DATA]
		return None
class Weather(object):
	
	def __init__(self,data):
		self.umidade = 0
		self.temperatura = 0			
		try:
			if data != TAGS.DATA_ERROR:
				d = data.split(TAGS.DATA_SEPARATOR)
				if len(d) == 2:
					self.umidade = d[0]
					self.temperatura = d[1] 
		except e:
			self.umidade = 0
			self.temperatura = 0			
