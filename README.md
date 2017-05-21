# memecimetro 

## otro velocímetro para bicicletas
## arduino + display nokia 5110 + reed switch + bicicletas = ???

### instalacion
- instalar las deps (lista de paquetes para arch y ubuntu en `deps/`)
- instalar [tup](http://gittup.org/tup/) y asegurarse de que quede en el path
- asegurarse de estar en el grupo `dialout` (ubuntu) o `uucp` (arch)
  - `gpasswd -a USER GROUP` para agregarse
  - `su USER` para abrir un shell con el grupo actualizado (sin tener que hacer logout/login)
- clonar este repo
- `git submodule init && git submodule update` clonar repo de simavr 
- `make -C virt/simavr` compila simavr

### uso
- `./runvirt.sh` ejecuta en simulador
- `./upload.sh` upload a arduino
- (ambos comandos corren `tup` antes, que compila si es necesario)

### customización
- en el archivo code/src/config.h se configuran las cosas como
	- las posiciones de los iconos y del texto
	- SLEEP_THRESHOLD_SECS setea el sleep time 
	- WHEEL_RADIUS_CSM radio de la rueda en pulgadas
	- WHEEL_DEVELOPMENT desarrollo de la rueda para calcular la cadencia y la distancia recorridaa
	- existe un layout alternativo en code/src/config.h.example

#### cosas que usamos
- [tup](http://gittup.org/tup/)
- [Arduino](https://www.arduino.cc/)
- [SparkFun's Graphic LCD Hookup Guide](https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide)
- [aseprite](https://github.com/aseprite/aseprite)
- [simavr](https://github.com/buserror/simavr)
- GNU/Linux, Ubuntu, gcc-avr, avrdude, freglut3, make, python, etc

## EN
## yet another bike speedometer
## arduino + display nokia 5110 + reed switch + bikes = ???
 
### installation
- install deps (list of packages for arch and ubuntu in 'deps/')
- install [tup](http://gittup.org/tup/) and make sure that is in path
- make sure that your user is un dialout (ubuntu) or uucp (arch) group
  - `gpasswd -a USER GROUP` if not
  - `su USER` to open a new sheel with updated groups (without logout and login)
- clone repo 
- `git submodule init && git submodule update` clone simavr repo
- `make -C virt/simavr` compile simavr

### use
- `./runvirt.sh` execute simavr
- `./upload.sh` upload to arduino
- (both commands run 'tup' before, it compiles if is necessary)

### customization
- in code/src/config.h you can configure things like
  - position of text and icons
  - SLEEP_THRESHOLD_SECS sleep time
  - WHEEL_RADIUS_CSM wheel radio in inches
  - WHEEL_DEVELOPMENT wheel develpment to calculate cadence and distance
  - an alternative layout exists in code/src/config.h.example

#### things we use
- [tup](http://gittup.org/tup/)
- [Arduino](https://www.arduino.cc/)
- [SparkFun's Graphic LCD Hookup Guide](https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide)
- [aseprite](https://github.com/aseprite/aseprite)
- [simavr](https://github.com/buserror/simavr)
- GNU/Linux, Ubuntu, gcc-avr, avrdude, freglut3, make, python, etc