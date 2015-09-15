#!/usr/bin/python2.7
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

import pygame
import SimpleXMLRPCServer
import threading

pygame.init()

size = (800,800)
screen = pygame.display.set_mode(size)

grid = [100,200,300,350,450,500,600,700]
matrix = (
	(2,0),(5,0),
	(5,1),(2,1),
	(0,3),(1,3),(3,3),(4,3),(6,3),(7,3),
	(7,4),(6,4),(4,4),(3,4),(1,4),(0,4),
	(3,6),(4,6),
	(4,7),(3,7)
)


nLeds = len(matrix)
dataRgb = [0]*nLeds*3
dataRgbLock = threading.Lock()

class RequestHandler(SimpleXMLRPCServer.SimpleXMLRPCRequestHandler):
	rpc_paths = ("/RPC2",)

def cmd(s):
	if len(s) < 1:
		return "?"
		
	if s[0] == "m":
		if len(s) < 9:
			return "?"
		iLed = int(s[1:3],16)
		r,g,b = int(s[3:5],16), int(s[5:7],16), int(s[7:9],16)
		if iLed < nLeds:
			dataRgbLock.acquire()
			dataRgb[3*iLed] = r
			dataRgb[3*iLed+1] = g
			dataRgb[3*iLed+2] = b
			dataRgbLock.release()
		else:
			return "?"
		return "M"+"".join(["%02x"%d for d in dataRgb])
	elif s[0] == "r":
		return "R"+"".join(["%02x"%d for d in dataRgb])
	else:
		return "?"

def serve():
	srv.serve_forever()

srv = SimpleXMLRPCServer.SimpleXMLRPCServer(("localhost", 8000), requestHandler=RequestHandler)
srv.register_function(cmd)
t = threading.Thread(target=serve)
t.daemon = True
t.start()




done = False
clock = pygame.time.Clock()

cnt = 0
while not done:
	for evt in pygame.event.get():
		if evt.type == pygame.QUIT:
			done = True
			break
			
	if done:
		break
	
	screen.fill((0,0,0))
	
	dataRgbLock.acquire()
	for i in range(0,len(matrix)):
		x,y = grid[matrix[i][0]], grid[matrix[i][1]]
		pygame.draw.circle(screen, dataRgb[3*i:3*i+3], [x,800-y], 40)
	dataRgbLock.release()
	
	pygame.display.flip()
	clock.tick(100) # 100 Hz update rate
	
	cnt += 1

pygame.quit()
