@echo off
SET FIRMWARE=code/src/firmware.hex

::setting path
SET PATH=%PATH%;C:\Program Files (x86)\Arduino\hardware\tools\avr\bin;avr;tup

:SETTINGS
SET /P MODEL="Choose an Arduino model (type NANO, MEGA, PROMINI or UNO): "
SET /P PORT="Choose a COM port (usually COM1): "

2>NUL CALL :CASE_%MODEL%

:CASE_NANO
  SET MCU=atmega328p
  SET PROG=arduino
  SET BAUD=57600
  GOTO PROGRAMER
:CASE_MEGA
  SET MCU=atmega2560
  SET PROG=wiring
  SET BAUD=115200
  GOTO PROGRAMER
:CASE_PROMINI
  SET MCU=atmega328p
  SET PROG=arduino
  SET BAUD=57600
  GOTO PROGRAMER
:CASE_UNO
  SET MCU=atmega328p
  SET PROG=arduino
  SET BAUD=115200
  GOTO PROGRAMER

:PROGRAMER
echo Running TUP
tup
echo Flashing %MODEL%
avrdude ^
  -C etc/avrdude.conf ^
  -p %MCU% ^
  -P %PORT% ^
  -c %PROG% ^
  -b %BAUD% ^
  -D  ^
  -U flash:w:%FIRMWARE%:i
