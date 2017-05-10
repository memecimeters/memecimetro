#
# 	Copyright 2008-2011 Michel Pollet <buserror@gmail.com>
#
#	This file is part of simavr.
#
#	simavr is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	simavr is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with simavr.  If not, see <http://www.gnu.org/licenses/>.

target = simduino_pcd8544demo
simavr = simavr

all: lib obj ${target}

IPATH = .
IPATH += ${simavr}/examples/parts
IPATH += ${simavr}/simavr/sim

VPATH = .
VPATH += ${simavr}/examples/parts

include ${simavr}/Makefile.common
include ${simavr}/examples/Makefile.opengl

LDFLAGS += -lpthread -lutil -L${simavr}/simavr/${OBJ}


board = ${OBJ}/${target}.elf

${board} : ${OBJ}/uart_pty.o
${board} : ${OBJ}/pcd8544_virt.o
${board} : ${OBJ}/pcd8544_glut.o
${board} : ${OBJ}/${target}.o

${target}: ${board}
	@echo $@ done

clean: clean-${OBJ}
	rm -rf *.hex *.a *.axf ${target} *.vcd .*.swo .*.swp .*.swm .*.swn

lib:
	cd ${simavr}/simavr; make
