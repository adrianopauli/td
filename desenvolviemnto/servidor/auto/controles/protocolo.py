class Protocolo(object):
	BYTE_START  = '#'
 	BYTE_STOP   = '$'
    BYTE_SEPARATOR  = '/'
    DATA_SEPARATOR  = '?'

    ACTION_READ     = 1
    ACTION_WRITE    = 2
    ACTION_RESPONSE = 3

    HARDWARE_IR       = 91
	HARDWARE_RELE     = 92
	HARDWARE_WEATHER  = 93

	PROTOCOL_ADRESSES    = 0
	PROTOCOL_TYPE        = 1
	PROTOCOL_HARDWARE    = 2
	PROTOCOL_NODE_ORIGIN = 3
	PROTOCOL_DATA        = 4

	DATA_ERROR = "ERROR"

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