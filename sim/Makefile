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

ANIM ?= anim_test
CFLAGS = -fPIC -std=c99 -DANIMATION=$(ANIM)

all:
	gcc $(CFLAGS) -c ../uc/src/animations/common.c -o common.o
	gcc $(CFLAGS) -c ../uc/src/animations/$(ANIM).c -o $(ANIM).o
	gcc $(CFLAGS) -c sim.c -o sim.o
	gcc -shared -fPIC sim.o common.o $(ANIM).o -o sim.so -lpython2.7
	./test.py

clean:
	-rm *.o *.so

.PHONY: all clean

