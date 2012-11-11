#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int _close(int fd)
{
	(void)fd;
	return 0;
}

int _fstat(int fd, struct stat *buf)
{
	(void)fd;
	buf->st_mode = S_IFCHR; /* Always pretend to be a tty */

	return 0;
}

int _isatty(int fd)
{
	(void)fd;
	return 1;
}

off_t _lseek(int fd, off_t offset, int whence)
{
	(void)fd;
	(void)offset;
	(void)whence;
	errno = ESPIPE;
	return ((off_t)-1);
}
