all: lapis

CC=gcc
INCLUDE=.
CFLAGS=-g -Wall -ansi
#CFLAGS=-O -Wall -ansi

lapis: lapis.c errnum.h
	$(CC) -o lapis -I$(INCLUDE) $(CFLAGS) -c lapis.c 
