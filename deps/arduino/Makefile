install: arduino-1.8.2-linux64.tar.xz
	if [ ! -d "arduino-1.8.2" ]; then \
		tar xf arduino-1.8.2-linux64.tar.xz; \
	fi
	@while [ -z "$$CONTINUE" ]; do \
		read -r -p "Pisar ~/.arduino con 1.8.2?. [y/N]: " CONTINUE; \
	done ; \
	[ $$CONTINUE = "y" ] || [ $$CONTINUE = "Y" ] || (echo "Exiting."; exit 1;)
	if [ -d "~/.arduino" ]; then \
		mv ~/.arduino ~/.arduino.old.memecimetro; \
	fi
	mkdir -p ~/.arduino/
	cp -r arduino-1.8.2/* ~/.arduino/
	
arduino-1.8.2-linux64.tar.xz:
	curl https://downloads.arduino.cc/arduino-1.8.2-linux64.tar.xz > arduino-1.8.2-linux64.tar.xz
