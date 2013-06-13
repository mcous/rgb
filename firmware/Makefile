# makefile for rgb project
#
# written by michael cousins
# http://github.com/mcous/rgb
#
# targets:
#   all:    compiles the source code
#   test:   tests the isp connection to the mcu
#   flash:  writes compiled hex file to the mcu's flash memory
#   fuse:   writes the fuse bytes to the MCU
#   disasm: disassembles the code for debugging
#   clean:  removes all .hex, .elf, and .o files in the source code directory

# parameters (change this stuff accordingly)
# project name
PRJ = rgb
# avr mcu
MCU = atmega328p
# mcu clock frequency
CLK = 16000000
# avrdude programmer and port (if necessary)
PRG = usbtiny
# fuse values for avr: low, high, and extended
LFU = 0xFF
HFU = 0xDE
EFU = 0x05
# program source files (not including libraries)
SRC = $(PRJ).cpp Effects.cpp
# where to look for libraries (consisting of a .cpp and a .h files)
LIB = ../../TLC5940

##########################################################################################
# stuff nobody needs to worry about until such time that worrying about it is appropriate
# flags
CFLAGS 	 = -Wall -Os -DF_CPU=$(CLK) -mmcu=$(MCU)
CFLAGS  += $(foreach dir, $(LIB), -I$(dir))
CPPFLAGS =

# executables
AVRDUDE = avrdude -c $(PRG) -p $(MCU)
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE    = avr-size --format=avr --mcu=$(MCU)
CC 	    = avr-gcc

# generate list of objects objects
CFILES    = $(filter %.c, $(SRC))
CPPFILES  = $(filter %.cpp, $(SRC))
LIBFILES := $(foreach dir, $(LIB), $(wildcard $(dir)/*.cpp))
OBJ       = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) $(LIBFILES:.cpp=.o)

# user targets
# compile all files
all: $(PRJ).hex

# test programmer connectivity
test:
	$(AVRDUDE) -v

# flash program to mcu
flash: all
	$(AVRDUDE) -U flash:w:$(PRJ).hex:i

# write fuses to mcu
fuse:
	$(AVRDUDE) -U lfuse:w:$(LFU):m -U hfuse:w:$(HFU):m -U efuse:w:$(EFU):m

# generate disassembly files for debugging
disasm: $(PRJ).elf
	$(OBJDUMP) -d $(PRJ).elf

# remove compiled files
clean:
	rm -f *.hex *.elf *.o
	$(foreach dir, $(LIB), rm -f $(dir)/*.o)

# other targets
# objects from c files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# objects from c++ files
.cpp.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# elf file
$(PRJ).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $(PRJ).elf $(OBJ)

# hex file
$(PRJ).hex: $(PRJ).elf
	rm -f $(PRJ).hex
	$(OBJCOPY) -j .text -j .data -O ihex $(PRJ).elf $(PRJ).hex
	$(SIZE) $(PRJ).elf
