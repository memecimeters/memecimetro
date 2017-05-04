all: atlas.png atlas.json

atlas%png atlas%json: font-x2.ase
	../deps/aseprite/aseprite/build/bin/aseprite -b *.ase --sheet-pack --sheet atlas$*png --data atlas$*json

font-x2.ase:
	../deps/aseprite/aseprite/build/bin/aseprite -b font.ase --scale 2 --save-as font-x2.ase
