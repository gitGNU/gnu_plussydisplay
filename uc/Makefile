##
## This file is part of the libopencm3 project.
##
## Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
##
## This library is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library.  If not, see <http://www.gnu.org/licenses/>.
##

V=1
BINARY = src/plussyuc

ANIM_SRC=$(shell find src/animations -name '*.c')
OBJS += src/hwversion.o src/ws2811.o src/util.o src/usart.o src/usb.o $(ANIM_SRC:.c=.o)

LDSCRIPT = nucleo-f401re.ld

include libopencm3.target.mk

clean2:
	-rm -f src/*.o src/*.d src/*.elf src/*.hex src/*.map src/animations/*.d src/animations/*.o

debug:
	openocd -f interface/ftdi/ft232h.cfg \
		    -f board/nucleo_f401re_ftdiswd.cfg \
		    -c "init" -c "reset init"

.PHONY: clean2
