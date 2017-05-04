all: make_aseprite

.PHONY: make_aseprite
make_aseprite: aseprite deps_aseprite
	mkdir -p aseprite/build
	cd aseprite/build; cmake -G Ninja ..; ninja aseprite

aseprite: 
	git clone --recursive https://github.com/aseprite/aseprite.git

.PHONY: deps_aseprite
deps_aseprite:
	# asume ubuntu
	sudo apt install -y g++ libx11-dev libxcursor-dev cmake ninja-build
