CC = gcc
LIBS += -lpthread
CFLAGS += -ansi -I ../include
LDFLAGS=
OBJECTS = \
main.o test.o
 
execute: $(OBJECTS)
	gcc    -o execute $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	-rm -f execute $(OBJECTS)
