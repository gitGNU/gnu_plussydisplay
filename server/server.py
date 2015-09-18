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
import socket
import socketserver
import threading
import time
import queue
import xmlrpc.client
import serial

########################################################################
# Discovery Broadcast
########################################################################

# send an UDP broadcast packet every second on first available interface (usually eth0)
class BroadcastThread(threading.Thread):
	def __init__(self, interface):
		super().__init__()
		self.contRun = True # stores wheather to exit thread
		self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP socket
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # allow multiple program starts ;-)
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1) # broadcast
		self.s.bind((interface,0)) # use interface that has given address associated
		self.ip = interface
	
	def run(self):
		while self.contRun:
			time.sleep(1) # send every second
			self.s.sendto(("plussyDisplay@"+self.ip).encode(), ("255.255.255.255", 60000)) # send magic packet
		
	def stop(self):
		self.contRun = False

########################################################################
# Hardware Thread
########################################################################

class HardwareRequest():
	def __init__(self, command, replyQueue):
		self.command = command # string command
		self.replyQueue = replyQueue # queue object for reply

requestQueue = queue.Queue() # thread-safe queue

class HardwareThread(threading.Thread):
	def __init__(self, serialPort):
		super().__init__()
		self.contRun = True
		
		self.s = None
		if serialPort != None:
			self.s = serial.Serial(serialPort, 115200, timeout=2)
	
	def run(self):
		if self.s == None:
			sim = xmlrpc.client.ServerProxy("http://localhost:8000") # Debug only!
		lastM = None
		while self.contRun:
			try:
				req = requestQueue.get(timeout=1)
			
				if (req.command[0] == "r") and (lastM != None): # quick reply for read command if we know the state
					req.replyQueue.put("R"+lastM[1:])
				else: # hardware query
					#print("hw: " + req.command)
					
					if self.s == None:
						# Debug: Send to simulation program
						ans = sim.cmd(req.command)
					else:
						# real hardware: use serial protocol
						self.s.write( ("!%02x%s;" % (len(req.command), req.command)).encode() )
						self.s.flush()
						tmp = ""
						while tmp != "@":
							tmp = self.s.read(1).decode()
							if tmp == "":
								raise Exception("timeout")
						l = int(self.s.read(2).decode(),16)
						ans = self.s.read(l).decode()
						e = self.s.read(1).decode()
						if e != ";":
							raise Exception("invalid end of response")
					
					if ans[0] == "M": # store answer for quick replies if command was 'm'
						lastM = ans
					req.replyQueue.put(ans)
				
			except queue.Empty:
				pass
			except serial.SerialException as e:
				print(e)
			except Exception as e:
				print(e)
		
	def stop(self):
		self.contRun = False

########################################################################
# Threaded TCP Server
########################################################################

class PlussyTCPHandler(socketserver.StreamRequestHandler):
	def handle(self):
		q = queue.Queue() # thread-safe queue for replies
		tname = threading.current_thread().name # thread name
		pname = self.request.getpeername() # peer ip and port (as tuple)
		label = tname + ", ip=" + pname[0] + ", port=" + str(pname[1]) + ": "
		print(label + "new connection")
		
		while True:
			req = self.rfile.readline().decode().strip() # get one line from socket
			if len(req) == 0: # socket has probably been closed
				break
			#print(label + "got request", "\"" + req + "\"")
			
			requestQueue.put(HardwareRequest(req, q)) # send request to hardware thread
			resp = q.get(timeout=1) # get reply from reply queue
			self.wfile.write((resp+"\n").encode()) # send reply to peer
			
		print(label + "disconnect")

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
	allow_reuse_address = True


########################################################################
# Main
########################################################################

if __name__ == "__main__":

	if len(sys.argv) < 2:
		print("usage: server.py INTERFACE [SERIAL]")
		print("example (simulation): server.py 192.168.0.1")
		print("example (hardware): server.py 192.168.0.1 /dev/ttyO1")
		sys.exit(1)

	# get interface ip
	interface = sys.argv[1]
	
	# get serial
	serialPort = None
	if len(sys.argv) > 2:
		serialPort = sys.argv[2]
	
	# start broadcast thread
	bt = BroadcastThread(interface)
	bt.start()
	
	# start hardware thread
	hwt = HardwareThread(serialPort)
	hwt.start()
	
	# start tcp server
	srv = ThreadedTCPServer((interface, 60000), PlussyTCPHandler)
	srvThread = threading.Thread(target=srv.serve_forever)
	srvThread.daemon = True
	srvThread.start()
	
	try:
		while True:
			time.sleep(1)
	except KeyboardInterrupt:
		print("exit request, exiting ...")
		# stop broadcast thread
		bt.stop()
		hwt.stop()
		bt.join()
		hwt.join()
		# stop server thread
		srv.shutdown()
		srv.server_close()

