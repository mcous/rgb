# rgb
rgb led lighting. modules are (read: will be) daisy-chainable over cat5/6 cabling.

## status
### what works now
* the leds

### what doesn't yet
* all other features

## firmware
### requirements
#### software (for mac, just download [CrossPack for AVR](http://www.obdev.at/products/crosspack/index.html))
* avrdude
* avr-objcopy
* avr-objdump
* avr-size
* avr-gcc

#### equipment
* some sort of avr isp

### instructions (mac or linux)
1. edit rgb/firmware/Makefile to use your isp
  * depending on your isp, you may need to add `-P /whatever/your/port/is` after the isp name
  * per usual, [ladyada](http://www.ladyada.net/learn/avr/avrdude.html) can help
2. navigate your terminal to rgb/firmware/
3. first time flashing:
  1. `$ make test` (ensures avr and isp are working)
  2. fix any connectivity problems; this will range from unplugging your isp and plugging it back in to re-soldering your mcu
  3. `$ make fuse` (writes correct fuse values to the avr)
  4. `$ make test` (ensure the new fuse values match the desired ones)
3. `$ make clean`
4. `$ make flash`
5. mess around with rgb.cpp and rgb.h to make different effects

### instructions (windows)
1. google

## hardware
### requirements
* [KiCad eda software suite](http://kicad-pcb.org)
* KiCad libraries from http://github.com/mcous/kicad-lib

### instructions
1. open kicad
2. open rgb-pcb.pro
3. ensure all component and footprint libraries from mcous/kicad-lib are installed
4. generate gerbers
5. order pcbs from your favorite manufacturer and parts from your favorite distributor
6. don't breathe the solder fumes
