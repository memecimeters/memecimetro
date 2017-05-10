# memecimetro

## arduino + display nokia 5110 + reed switch + bicicletas = ???

### instalacion
- instalar las deps (lista de paquetes para arch y ubuntu en `deps/`)
- instalar [tup](http://gittup.org/tup/) y asegurarse de que quede en el path
- asegurarse de estar en el grupo `dialout` (ubuntu) o `uucp` (arch)
  - `gpasswd -a USER GROUP` para agregarse
  - `su USER` para abrir un shell con el grupo actualizado (sin tener que hacer logout/login)

### uso
- `tup init` inicializa la db de tup
- `make -C virt` compila el simulador (y simavr)
- `tup` compila todo (salvo el simulador)
- `./runvirt.sh` ejecuta en simulador
- `./upload.sh` upload a arduino

#### cosas que usamos
- [tup](http://gittup.org/tup/)
- [Arduino](https://www.arduino.cc/)
- [SparkFun's Graphic LCD Hookup Guide](https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide)
- [aseprite](https://github.com/aseprite/aseprite)
- [simavr](https://github.com/buserror/simavr)
- GNU/Linux, Ubuntu, gcc-avr, avrdude, freglut3, make, python, etc
