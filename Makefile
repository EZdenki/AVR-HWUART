#	Makefile for avr-gcc
#	Items marked by a * in the comments need to be updated for
#	each project.

#	*TARGET specifies the desired binary output.
#	*MCU is the name of the AVR device to program.
#	*AVR_PROG is the ISP programmer used to flash the AVR.
TARGET   = main
MCU      = attiny2313
AVR_PROG = usbtiny


#	*AVR_PORT is the USB port the ISP programmer is connected to.
#	Uncomment and set to appropriate port for non usbtiny ISP
#	programmers.
#AVR_PORT =


#	*AVRFUSES
# attiny2313 Int. 8 MHz (no divider), no clock out
#AVR_FUSES = -U lfuse:w:0xe4:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

# attiny2313 Int. 8 MHz (no divider), clock out
AVR_FUSES = -U lfuse:w:0xa4:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

# attiny2313 Int. 1 MHz, clock out
#AVR_FUSES = *-U lfuse:w:0x24:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m


# 	AVRDUDEFLAGS are parameters sent to avrdude. Can add -B255 for
#	slow chips, or even fuse settings if desired.
AVRDUDEFLAGS = -c $(AVR_PROG) -p $(MCU)
ifdef AVR_PORT
AVRDUDEFLAGS += -P $(AVR_PORT)
endif


#	*PASSPARAM are defines "variables" passed and compiled into all
# 	C sources from this Makefile, for example, F_CPU, etc. Each
#	variable should have -D before it with no space between the
#	-D and the defined variable.
#	Comment out if unused.
PASSPARAM = -DF_CPU=8000000UL -DBAUDRATE=9600 -DDEBUG=1


#	*DEPS specify what non-compiled files need to trigger compilation
#	in the event that any of these files are changed. Specifiy
#	library header files here as well as Makefile in case Makefile is
#	sending defines parameters to C sources for compilation.
DEPS = hwuart/hwuart.h Makefile


#	*OBJS are library/include objects based on included libraries.
#	Have an entry for each C library file here.
OBJS = hwuart/hwuart.c $(TARGET).o


#	CC specifies the C compiler.
#	CFLAGS specifies the C compiler command-line flags.
CC     = avr-gcc
CFLAGS = -Os -Wall -I. -g -mmcu=$(MCU)


#	Send program to AVR, and report size info
flash: $(TARGET).hex
	avrdude $(AVRDUDEFLAGS) -U $<
	avr-size -C --mcu=$(MCU) $(TARGET).elf


$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -j .text -j .data $< $@


$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@


#	This is a catch-all line that makes sure all required object
#   files based on any C source will be compiled into the desired
#	object code. It makes sure that these objects are recompiled
#	whenever any of the dependancies in DEPS are changed.
#	Note that the CFLAGS must be added to the compile rule, though
#	it is not required to add $(CFLAGS) to the rule when using .o
#	object files because it will automatically be part of the rule.
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(PASSPARAM)


#	Send desired fuse settings to AVR.
.PHONY: fuse
fuse:
	avrdude $(AVRDUDEFLAGS) $(AVR_FUSES)


.PHONY: clean
clean:
	rm -f *.o *.hex *.elf $(TARGET)
