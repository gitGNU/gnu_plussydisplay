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
import time
import signal
import serial

bufLen = 2
timeout = 5.0
dummyTx = [0]*bufLen

intReq = False

def devRequest(s,msg):
	data = ("!%02x%s;" % (len(msg), msg)).encode()
	print("req: ", data)
	s.write(data)
	s.flush()

def devResponse(s):
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

def query(s, msg):
	if len(msg) < bufLen:
		msg = msg + [0]*(bufLen - len(msg))
	ascMsg = "".join(["%02x"%d for d in msg])
	
	devRequest(s,"~"+ascMsg)
	ans = devResponse(s)
	print(ans)
	return
	if len(c) != msgLen:
		print("got invalid message: ", c)
		sys.exit(2)
	for i in range(0,len(ascMsg)):
		ans.append( int(c[4+2*i:6+2*i],16) )
	return ans

def u32bytes(v):
	b = [0]*4
	b[0] = v & 0xff
	b[1] = (v>>8) & 0xff
	b[2] = (v>>16) & 0xff
	b[3] = (v>>24) & 0xff
	return b

def getStr(d):
	return "".join([chr(c) for c in d])

def getHexStr(d):
	return "".join(["%02x" % c for c in d])

def getBinStr(d):
	return [ord(c) for c in d]

def sigint(sig, stack):
	print("interrupt, exiting ...")
	intReq = True
	sys.exit(1)

if __name__ == "__main__":
	
	signal.signal(signal.SIGINT, sigint)
	
	if len(sys.argv) != 3:
		print("usage example: bootclient.py /dev/ttyACM0 pr0gram.bin")
		sys.exit(1)
		
	dev = sys.argv[1]
	fname = sys.argv[2]
	
	h = serial.Serial(dev, timeout=1)
	
	query(h,[0x01])
	print("ans:", getHexStr(ans))
	sys.exit(0)
	
	print("reading file ...")
	f = open(fname, "rb")
	dat = f.read()
	dat = list(dat)
	print(len(dat))

	print("erase sector 4 ...")
	ans = query(h, [0xf1, 4])
	print("ans:", getHexStr(ans))
	
	if len(dat) > 64*1024:
		l = len(dat) - 64*1024
		sec = 5
		while l > 0:
			print("erase sector %d ..." % sec)
			ans = query(h, [0xf1, sec])
			print("ans:", getHexStr(ans))
			
			l -= 128*1024
			sec += 1

	print("write data ...")
	offs = 0x08010000
	pos = 0
	while pos < len(dat):
		if (pos+32) <= len(dat):
			tmp = dat[pos:(pos+32)]
		else:
			tmp = dat[pos:] + [0xff]*(len(dat)-pos)
	
		print("write pos %08x, len=%d ..." % (offs+pos, len(tmp)))
		ans = query(h, [0xf0] + u32bytes(offs+pos) + tmp)
		#print("ans:", getHexStr(ans))
		
		pos += 32
		
	print("verify data ...")
	pos = 0
	datRead = []
	while pos < len(dat):
		ans = query(h, [0xf2] + u32bytes(offs+pos))
		#print "ans:", getHexStr(ans)
		datRead.extend(ans[1:33])
		
		pos += 32
	
	print("compare ...")
	err = 0
	for i in range(0,len(dat)):
		if dat[i] != datRead[i]:
			if err < 10:
				print("%d (%08x): should be %02x, is %02x" % (i, i, dat[i], datRead[i]))
			err += 1
	print("%d errors." % err)

	print("reboot ...")
	gpio_boot_release()
	ans = query(h, [0xff])
	print("ans:", getHexStr(ans))

