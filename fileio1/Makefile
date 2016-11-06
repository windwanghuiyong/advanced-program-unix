CC = gcc
LIBS += -lpthread

OBJECTS = \
main.o open.o lseek.o hole.o mycat.o flock.o fcntl.o limit.o nonblock.o \
read_write.o read_write_std.o \
../signals/tellwait.o
 
execute: $(OBJECTS)
	gcc    -o execute $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	-rm -f execute $(OBJECTS)
