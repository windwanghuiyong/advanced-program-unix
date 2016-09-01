#include <stdio.h>
#include <errno.h>

#include "error_handing.h"
#include "exit_handler.h"
#include "create_process.h"
#include "posix_thread.h"
#include "pthread_cleanup_handler.h"
#include "macros.h"
#include "preprocess_pragma.h"

int main(int argc, char const *argv[])
{
	// pthread_cleanup_handler();
	macro_test();
	
	return 0;
}
