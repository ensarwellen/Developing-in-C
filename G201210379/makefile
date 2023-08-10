# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

CLASSDIR = ./Libfdr
INCLUDE = -I$(CLASSDIR)/include
CFLAGS = $(INCLUDE)
LIBS = $(CLASSDIR)/lib/libfdr.a

EXECUTABLES = bin/ödev3
CC = gcc

all: $(EXECUTABLES)

clean:
	rm -f bin/*

	
bin/ödev3: src/ödev3.c
	$(CC) $(CFLAGS) -o bin/ödev3 src/ödev3.c $(LIBS)
	
		

