CC = gcc
LIBS += -lpthread

OBJECTS = \
main.o open.o lseek.o hole.o mycat.o read_write.o read_write_std.o fcntl.o limit.o nonblock.o
 
execute: $(OBJECTS)
	gcc    -o execute $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	-rm -f execute $(OBJECTS)
