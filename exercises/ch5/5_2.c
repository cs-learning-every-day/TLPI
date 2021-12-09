#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    fd = open("tmp", O_WRONLY | O_APPEND);

    if (fd == -1) {
        errExit("file not found");
    }

    lseek(fd, 0, SEEK_SET);
    write(fd, "MrBeast", 7);
    
    exit(EXIT_SUCCESS);
}