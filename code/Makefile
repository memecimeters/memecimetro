all: build upload serial

clean:
	ano clean
	rm -f src/atlas_gen*
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
	../board_pcd8544/obj-x86_64-linux-gnu/simduino_pcd8544demo.elf &
	ano serial -p /tmp/simavr-uart0
