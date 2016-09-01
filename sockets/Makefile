CC = gcc
LIBS += -lpthread

OBJECTS = \
main.o address.o connect.o listen.o
 
execute: $(OBJECTS)
	gcc    -o execute $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	-rm -f execute $(OBJECTS)
