#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#define UNUSED_PARAM \
    (void) fd;       \
    (void) buffer;   \
    (void) size

#define SYS_ALIAS(name) __attribute__((__alias__(#name), __weak__))
#define IO_IMP(name) \
    int name(int fd, char *buffer, int size) SYS_ALIAS(sys_io_handler)

int sys_io_handler(int fd, char *buffer, int size)
{
    UNUSED_PARAM;
    return -ENOSYS;
}

IO_IMP(_open);
IO_IMP(_close);
IO_IMP(_write);
IO_IMP(_read);

IO_IMP(_exit);
IO_IMP(_getpid);
IO_IMP(_sbrk);
IO_IMP(_kill);

IO_IMP(_isatty);
IO_IMP(_fstat);
IO_IMP(_lseek);

