#!/usr/bin/python3

import sys
import serial

if len(sys.argv) < 3:
	print("usage: testclient.py SERIALPORT COMMAND")
	print("example: testclient.py /dev/ttyUSB0 e")
	sys.exit(1)

port = sys.argv[1]
cmd = sys.argv[2]

s = serial.Serial(port, 115200, timeout=1)

def devRequest(msg):
	data = ("!%02x%s;" % (len(msg), msg)).encode()
	s.write(data)
	s.flush()

def devResponse():
	tmp = ""
	while tmp != "@":
		tmp = s.read(1).decode()
		if tmp == "":
			raise Exception("timeout")
	l = int(s.read(2).decode(),16)
	data = s.read(l).decode()
	e = s.read(1).decode()
	if e != ";":
		raise Exception("invalid end of response")
	return data

devRequest(cmd)
ans = devResponse()
print("reply:", "\"" + ans + "\"")

