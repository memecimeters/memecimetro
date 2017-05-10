#!/bin/bash
set -e

OBJ=obj-`gcc -dumpmachine`
FIRMWARE=code/src/firmware.hex
SIMAVR_LIBS=virt/simavr/simavr/${OBJ}/
TTY=/tmp/simavr-uart0

tup

SIMAVR_UART_XTERM=1 LD_LIBRARY_PATH=${SIMAVR_LIBS} virt/${OBJ}/simduino_pcd8544demo.elf ${FIRMWARE}
