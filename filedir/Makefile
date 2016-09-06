CC = gcc
LIBS += -lpthread

OBJECTS = \
main.o type.o access.o mode.o
 
execute: $(OBJECTS)
	gcc    -o execute $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	-rm -f execute $(OBJECTS)
