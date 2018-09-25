#!/bin/bash
set -e
if [ $# -eq 0 ]
 then
  echo "Usage: $0 nano/promini/mega"
  exit
fi
FIRMWARE=code/src/firmware.hex

# chequea que NO este seteado mega
# nano
case "$1" in
"nano")
  MCU=atmega328p
  PROG=arduino
  BAUD=57600
  TTY=/dev/ttyUSB0
  ;;
"mega")
  MCU=atmega2560
  PROG=wiring
  BAUD=115200
  TTY=/dev/ttyUSB0
  ;;
"promini")
  MCU=atmega328p
  PROG=arduino
  BAUD=57600
  TTY=/dev/ttyACM0
  ;;
"uno")
  MCU=atmega328p
  PROG=arduino
  BAUD=115200
  TTY=/dev/ttyACM0
  ;;
"programer")
    MCU=atmega328p
    PROG=usbasp
    BAUD=57600
    TTY=/dev/ttyUSB0
    ;;
esac

tup

avrdude \
  -C ./etc/avrdude.conf \
  -p $MCU \
  -P $TTY \
  -c $PROG \
  -b $BAUD \
  -D  \
  -U flash:w:$FIRMWARE:i

picocom $TTY
