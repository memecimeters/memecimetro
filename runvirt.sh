#!/bin/bash
set -e

OBJ=obj-`gcc -dumpmachine`
FIRMWARE=code/src/firmware.hex
TTY=/tmp/simavr-uart0

tup

LD_LIBRARY_PATH=virt/simavr/simavr/${OBJ}/ virt/${OBJ}/simduino_pcd8544demo.elf ${FIRMWARE} &

picocom $TTY
