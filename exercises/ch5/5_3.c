#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        usageErr("atomic_append filename num-bytes [x]\n");
    }

    int flag = O_RDWR | O_APPEND | O_CREAT;
    if (argc > 3 && strcmp(argv[3], "x") == 0) {
        flag ^= O_APPEND;
    }

    int fd = open(argv[1], flag, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        errExit("open error\n");
    }

    int n = atoi(argv[2]);
    bool useLseek = ((flag & O_APPEND) != O_APPEND);
    for (int i = 0; i < n; i++) {
        if (useLseek) {
            if (lseek(fd, 0, SEEK_END) == -1) {
                errExit("lseek error\n");
            }
        }

        if (write(fd, "x", 1) != 1) {
            errExit("write error\n");
        }
    }

    exit(EXIT_SUCCESS);
}