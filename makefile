INCL = -I . -I uOS -I uart

SRC	= \
uOS/uOS.c \
uart/uart.c \
main.c 

CC = avr-gcc
CFLAGS = -mmcu=atmega328 -O2 -std=gnu11

default: build

build:
	mkdir -p bin
	$(CC) -o bin/out.o $(SRC) $(CFLAGS) $(INCL) -D CARD_ID=$(ID)
	avr-objcopy -j .text -j .data -O ihex bin/out.o bin/out.hex

deploy: build
	avrdude -p atmega328 -c usbtiny -v -U flash:w:bin/out.hex

test: 
	avrdude -p atmega328 -c usbtiny

clean: 
	rm -rf bin