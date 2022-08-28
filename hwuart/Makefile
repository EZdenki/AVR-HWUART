# Makefile for Single File (No local libraries)

TARGET     = hwuart-test
AVR_PROG   = usbtiny
MCU		   = attiny2313

# AVR_FUSE for internal 8 MHz clock, no CLK divider, and clock output
AVR_FUSE   = -U lfuse:w:0xA4:m hfuse:w:0xDF

# AVR_FUSE for external crystal, no CLK divider, and clock output
#AVR_FUSE   = -U lfuse:w:0xAF:m hfuse:w:0xDF

# CPU and serial speed parameters passed to main c code
# SPEEDPARAMS = -DBAUDRATE=9600 -DF_CPU=8000000UL
# CFLAGS = -Wall -Os -mmcu=$(MCU) $(SPEEDPARAMS)

# CFLAGS = -Wall -Os -mmcu=$(MCU)
CFLAGS = -Wall -Os -mmcu=$(MCU)


program: $(TARGET).hex
	avrdude -c $(AVR_PROG) -p $(MCU) $(AVR_FUSE)
	avrdude -c $(AVR_PROG) -p $(MCU) -U $(TARGET).hex
	avr-size -C --mcu=$(MCU) $(TARGET).elf

# Compile object to binary (elf), and then convert binary to ihex
$(TARGET).hex: $(TARGET).o
	avr-gcc $(CFLAGS) $(TARGET).o -o $(TARGET).elf
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

# Compile source to object
$(TARGET).o: $(TARGET).c
	avr-gcc $(CFLAGS) -c $(TARGET).c -o $(TARGET).o

#$(TARGET).bin: $(OBJS)
#	avr-gcc -Os -mmcu=$(MCU)-g -o $(TARGET).elf $(OBJS)
#	avr-gcc -Wall -Os -mmcu=$(MCU) $(OBJS) -o $(TARGET).bin


## Get rid of all tertiary files and do full recompile and upload to AVR
clean:
	rm -f *.bin; rm -f *.hex; rm -f *.o; rm -f *.elf
