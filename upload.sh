#!/bin/bash
set -e

FIRMWARE=code/src/firmware.hex
TTY=/dev/ttyUSB0

tup

source tup.config

# chequea que NO este seteado mega
if [ -z "$CONFIG_MEGA" ]; then
  # nano
  MCU=atmega328p
  PROG=arduino
  BAUD=57600
else
  # mega
  MCU=atmega2560
  PROG=wiring
  BAUD=115200
fi

avrdude \
  -C ./etc/avrdude.conf \
  -p $MCU \
  -P $TTY \
  -c $PROG \
  -b $BAUD \
  -D  \
  -U flash:w:$FIRMWARE:i

picocom $TTY
