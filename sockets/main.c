#include <stdio.h>
#include "prototype.h"

int main(int argc, char const *argv[]) 
{
	get_hostent();
	get_netent();
	get_protoent();
	get_servent();
	// print_hint_flags();
	// print_addr_info(argv[1], argv[2]);
	return 0;
}
