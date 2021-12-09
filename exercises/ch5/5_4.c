#include <fcntl.h>
#include <tlpi_hdr.h>

int mydup(int oldfd) {
    // 为oldfd创建一个副本，且将使用大于等于starfd的最小未用值作为描述符编号
    return fcntl(oldfd, F_DUPFD, 0);
}

int mydup2(int oldfd, int newfd) {
    if (oldfd == newfd) {
        if (fcntl(oldfd, F_GETFL) < -1) {
            errno = EBADF;
            return -1;
        } else {
            return newfd;
        }
    } else {
        close(newfd);
        return fcntl(oldfd, F_DUPFD, newfd);
    }
}