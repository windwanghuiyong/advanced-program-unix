#include <stdio.h>

#define		_X86 2016
#undef		_X86
#ifdef		_X86
#pragma message("_X86 macro activated!")
#endif
