OBJ := obj-${shell gcc -dumpmachine}

all: build upload serial

clean:
	ano clean
	rm -f src/sprites.*
	make -C sprites clean

build:
	make -C sprites
	ano build

upload:
	ano upload

serial:
	ano serial


virt: build runsim

runsim:
	LD_LIBRARY_PATH=../virt/simavr/simavr/${OBJ}/ ../virt/${OBJ}/simduino_pcd8544demo.elf &
	ano serial -p /tmp/simavr-uart0
