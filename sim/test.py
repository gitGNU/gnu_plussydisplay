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
import sim

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
	
	screen.fill((0xff,0xff,0xff))
	
	nLeds = len(matrix)
	dataRgb = [0]*nLeds*3
	sim.callAnimation(dataRgb)
	
	for i in range(0,len(matrix)):
		x,y = grid[matrix[i][0]], grid[matrix[i][1]]
		pygame.draw.circle(screen, dataRgb[3*i:3*i+3], [x,800-y], 40)
	
	pygame.display.flip()
	clock.tick(100) # 100 Hz update rate
	
	cnt += 1

pygame.quit()
