#!/usr/bin/python3
#
#	Plussy Display
#	Copyright (C) 2015  Christian Carlowitz <chca@cmesh.de>
#
#	This program is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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

