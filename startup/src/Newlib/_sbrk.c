#include <sys/types.h>

extern int  _heap_start;
extern int _heap_end;

caddr_t _sbrk(int incr)
{
	static unsigned char *heap = NULL;
	unsigned char *prev_heap;

	if (heap == NULL) 
		heap = (unsigned char *)&_heap_start;
	prev_heap = heap;

	heap += incr;

	if ((unsigned)heap > (unsigned)_heap_end)
		return (caddr_t) -1;

	return (caddr_t) prev_heap;
}
