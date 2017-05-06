ASEPRITE_BIN = ../../deps/aseprite/aseprite/build/bin/aseprite

all: clean atlas_gen.h

clean:
	rm -f atlas.png atlas.json

atlas_gen.%: atlas.png
	./codegen_atlas.py

atlas.png: font_x2.ase
	${ASEPRITE_BIN} -b *.ase --sheet-pack --sheet atlas.png --data atlas.json

%_x2.ase:
	${ASEPRITE_BIN} -b $*.ase --scale 2 --save-as $@
