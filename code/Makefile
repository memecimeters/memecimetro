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

