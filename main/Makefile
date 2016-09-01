CC = gcc
LIBS += -lpthread

OBJECTS = \
main.o error_handing.o environment_pointer.o \
time_obtain.o exit_handler.o create_process.o \
std_read_write.o get_socket_information.o \
feature_test_macros.o macros.o \
posix_thread.o pthread_cleanup_handler.o
 
execute: $(OBJECTS)
	gcc    -o execute $(OBJECTS) $(LIBS)

main.o: main.c error_handing.h
error_handing.o: error_handing.c error_handing.h
time_obtain.o: time_obtain.c
exit_handler.o: exit_handler.c exit_handler.h
create_process.o: create_process.c create_process.h
std_read_write.o: std_read_write.c std_read_write.h
environment_pointer.o: environment_pointer.c
get_socket_information.o: get_socket_information.c
posix_thread.o: posix_thread.c posix_thread.h
feature_test_macros.o: feature_test_macros.c
macros.o: macros.c macros.h

backup:

tar:

.PHONY: clean
clean:
	-rm -f execute $(OBJECTS)
