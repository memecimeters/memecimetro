OBJ := obj-${shell gcc -dumpmachine}

all: tup build upload serial

tup:
	tup

clean:
	ano clean

build:
	ano build

upload:
	ano upload

serial:
	ano serial


virt: build runsim

runsim:
	LD_LIBRARY_PATH=../virt/simavr/simavr/${OBJ}/ ../virt/${OBJ}/simduino_pcd8544demo.elf &
	ano serial -p /tmp/simavr-uart0
