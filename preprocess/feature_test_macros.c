#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/* print_defined_default_feature_test_macros */
/* $ cc -D_GNU_SOURCE ftm.c */
int prt_ftm(void)
{
	#ifdef _POSIX_SOURCE
	printf("_POSIX_SOURCE defined\n");	// yes
	#endif

	#ifdef _POSIX_C_SOURCE
	printf("_POSIX_C_SOURCE defined: %ldL\n", (long) _POSIX_C_SOURCE);	// yes
	#endif

	#ifdef _ISOC99_SOURCE
	printf("_ISOC99_SOURCE defined\n");
	#endif

	#ifdef _ISOC11_SOURCE
	printf("_ISOC11_SOURCE defined\n");
	#endif

	#ifdef _XOPEN_SOURCE
	printf("_XOPEN_SOURCE defined: %d\n", _XOPEN_SOURCE);
	#endif

	#ifdef _XOPEN_SOURCE_EXTENDED
	printf("_XOPEN_SOURCE_EXTENDED defined\n");
	#endif

	#ifdef _LARGEFILE64_SOURCE
	printf("_LARGEFILE64_SOURCE defined\n");
	#endif

	#ifdef _FILE_OFFSET_BITS
	printf("_FILE_OFFSET_BITS defined: %d\n", _FILE_OFFSET_BITS);
	#endif

	#ifdef _BSD_SOURCE
	printf("_BSD_SOURCE defined\n");
	#endif

	#ifdef _SVID_SOURCE
	printf("_SVID_SOURCE defined\n");
	#endif

	#ifdef _DEFAULT_SOURCE
	printf("_DEFAULT_SOURCE defined\n");	// yes
	#endif

	#ifdef _ATFILE_SOURCE
	printf("_ATFILE_SOURCE defined\n");	// yes
	#endif

	#ifdef _GNU_SOURCE
	printf("_GNU_SOURCE defined\n");
	#endif

	#ifdef _REENTRANT
	printf("_REENTRANT defined\n");
	#endif

	#ifdef _THREAD_SAFE
	printf("_THREAD_SAFE defined\n");
	#endif

	#ifdef _FORTIFY_SOURCE
	printf("_FORTIFY_SOURCE defined\n");
	#endif

	return 0;
}

void functions_need_ftm()
{
	acct(NULL);
	// readahead(2, 2, 2);
}
