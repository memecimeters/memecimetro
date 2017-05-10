#!/bin/bash
set -e

FIRMWARE=code/src/firmware.hex
TTY=/dev/ttyUSB0

tup

# asume nano
avrdude \
  -C ./etc/avrdude.conf \
  -p atmega328p \
  -P $TTY \
  -c arduino \
  -b 57600 \
  -D  \
  -U flash:w:$FIRMWARE:i

picocom $TTY
