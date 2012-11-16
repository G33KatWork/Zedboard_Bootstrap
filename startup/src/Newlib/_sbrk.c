#include <sys/types.h>
#include <errno.h>

extern char _heap_start[];
extern char _heap_end[];

caddr_t _sbrk(int incr)
{
	static char* cur_heap_end;
	char* prev_heap_end;

	if(cur_heap_end == NULL) cur_heap_end = _heap_start;
	prev_heap_end = cur_heap_end;

	if((unsigned)cur_heap_end + incr > (unsigned)_heap_end)
	{
		errno = ENOMEM;
	 	return (caddr_t)-1;
	}

	cur_heap_end += incr;

	return (caddr_t) prev_heap_end;
}
