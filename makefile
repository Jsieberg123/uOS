INCL = -I . -I uOS

SRC	= \
uOS/uOS.c \
main.c 

CC = avr-gcc
CFLAGS = -mmcu=atmega328 -O2 -std=gnu11

default: build

build:
	mkdir -p bin
	$(CC) -o bin/out.o $(SRC) $(CFLAGS) $(INCL) -D CARD_ID=$(ID)
	avr-objcopy -j .text -j .data -O ihex bin/out.o bin/out.hex
deploy: build


clean: 
	rm -rf bin