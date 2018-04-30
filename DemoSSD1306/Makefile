CC = gcc
LD = gcc

CFLAGS=-I/usr/include/glib-2.0 -I/usr/local/include -std=c11
CFLAGS+=-D_POSIX_C_SOURCE=200809L -D_DEFAULT_SOURCE

LDFLAGS=-lwiringPi -lglib-2.0 -lpthread

all: main

demo: main.o ssd1306_i2c.o
	$(LD) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<
