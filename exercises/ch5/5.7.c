#include "tlpi_hdr.h"
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

ssize_t myreadv(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t numRead = 0;
    for (int i = 0; i < iovcnt; i++) {
        int n = read(fd, iov[i].iov_base, iov[i].iov_len);
        if (n < 0) {
            return -1;
        } else if (n == 0) {
            return numRead;
        }
        numRead += iov[i].iov_len;
    }
    return numRead;
}

ssize_t mywritev(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t numWrite = 0;
    for (int i = 0; i < iovcnt; i++) {
        if (write(fd, iov[i].iov_base, iov[i].iov_len) != iov[i].iov_len) {
            return -1;
        }
        numWrite += iov[i].iov_len;
    }
    return numWrite;
}

/* 小测试 */
int main(int argc, char *argv[]) {
    int fd;
    struct iovec iov[2];

    char str1[3];  /* first buffer */
    char str2[11]; /* seoncd buffer */
    ssize_t numRead, needWrite;

    fd = open("tmp2", O_RDWR | O_APPEND);
    if (fd == -1) {
        errExit("open");
    }

    needWrite = 0;

    iov[0].iov_base = str1;
    iov[0].iov_len = sizeof(str1);
    needWrite += iov[0].iov_len;

    iov[1].iov_base = str2;
    iov[1].iov_len = sizeof(str2);
    needWrite += iov[1].iov_len;

    numRead = myreadv(fd, iov, 2);
    if (numRead == -1) {
        errExit("readv");
    }
    
    str1[2] = '\0';
    printf("read content:%s %s\n", str1, str2);
    
    
    memset(str1, 0, sizeof(str1));
    memset(str2, 0, sizeof(str2));

    strcpy(str1, "21");
    strcpy(str2, "sunhuayang");

    assert(mywritev(fd, iov, 2) == needWrite);

    exit(EXIT_SUCCESS);
}