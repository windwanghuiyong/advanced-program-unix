CC = gcc
LIBS += -lpthread

OBJECTS = \
main.o tellwait.o user.o mask.o
 
execute: $(OBJECTS)
	gcc    -o execute $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	-rm -f execute $(OBJECTS)
