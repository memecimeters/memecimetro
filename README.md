# memecimetro

## arduino + display nokia 5110 + reed switch + bicicletas = ???

### instalacion
- instalar las deps (lista de paquetes para arch y ubuntu en `deps/`)
- instalar [tup](http://gittup.org/tup/) y asegurarse de que quede en el path
- asegurarse de estar en el grupo `dialout` (ubuntu) o `uucp` (arch)
  - `gpasswd -a USER GROUP` para agregarse
  - `su USER` para abrir un shell con el grupo actualizado (sin tener que hacer logout/login)
- clonar este repo
- `git submodule init && git submodule update`
- `make -C virt/simavr` compila simavr

### uso
- `./runvirt.sh` ejecuta en simulador
- `./upload.sh` upload a arduino
- (ambos comandos corren `tup` antes, que compila si es necesario)

#### cosas que usamos
- [tup](http://gittup.org/tup/)
- [Arduino](https://www.arduino.cc/)
- [SparkFun's Graphic LCD Hookup Guide](https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide)
- [aseprite](https://github.com/aseprite/aseprite)
- [simavr](https://github.com/buserror/simavr)
- GNU/Linux, Ubuntu, gcc-avr, avrdude, freglut3, make, python, etc
