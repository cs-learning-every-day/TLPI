#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void generateHoleFile() {
    int fd = open("tmp", O_CREAT | O_TRUNC | O_RDWR, 0666);
    write(fd, "ddd", 3);
    lseek(fd, 4096, SEEK_END);
    for (int i = 0; i < 4096; i++) {
        write(fd, "\0", 1);
    }
    write(fd, "bbb", 3);
    close(fd);
}

int main() {
    generateHoleFile();
    int holeFd = open("tmp", O_RDWR);
    int fd = open("tmp2", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    char buf = '\0';
    int n;

    // 不行了，读取空洞文件返回0，
    while ((n = read(holeFd, &buf, 1)) > 0) {
        if (buf == '\0') {
            if (lseek(fd, 1, SEEK_CUR) < 0) {
                printf("lseek error\n");
                exit(1);
            }
        } else if (write(fd, &buf, 1) != 1) {
            printf("write error\n");
            exit(1);
        }
    }

    if (n < 0) {
        printf("read error\n");
        exit(1);
    }

    close(fd);
    close(holeFd);
    return 0;
}