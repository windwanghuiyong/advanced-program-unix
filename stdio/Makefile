CC = gcc
LIBS += -lpthread

OBJECTS = \
main.o mycat.o buffer.o tempfiles.o memorystream.o
 
execute: $(OBJECTS)
	gcc    -o execute $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	-rm -f execute $(OBJECTS)
