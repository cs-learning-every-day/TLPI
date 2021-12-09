#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int fd = open("tmp", O_RDONLY);
    lseek(fd, 10, SEEK_CUR);

    int copyFd = dup(fd);

    assert(lseek(fd, 0, SEEK_CUR) == lseek(copyFd, 0, SEEK_CUR));

    int flag1 = fcntl(fd, F_GETFL);
    int flag2 = fcntl(copyFd, F_GETFL);

    assert(flag1 == flag2);
    
}