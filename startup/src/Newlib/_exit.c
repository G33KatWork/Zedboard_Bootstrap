#include <unistd.h>

void _exit(int status)
{
	(void)status;
	while(1);
}
