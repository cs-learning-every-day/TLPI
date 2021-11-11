#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_READ 256

int main(int argc, char* argv[]) {
    int opt, n;
    char buffer[MAX_READ];
    int fdCount = 0;
    bool isAppend = false;
    int fileFdArr[256];

    while ((opt = getopt(argc, argv, "a-:")) != -1) {
        switch (opt)
        {
        case 'a': 
            isAppend = true;
            break;
        case '-':
            if (strcmp(optarg, "help") == 0) {
                printf("usage: tee [-a] <filename>\n");
            }
            exit(1);
        default:
            break;
        }
    }

    // 剩下的非命令解析 参数
    for (int i = optind; i < argc && fdCount < 256; i++, fdCount++) {
        if (isAppend) {
            fileFdArr[fdCount] = open(argv[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
        } else {
            fileFdArr[fdCount] = open(argv[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        }

        if (fileFdArr[fdCount] < 0) {
            printf("open %s error\n", argv[i]);
            exit(1);
        }
    }

    while ((n = read(STDIN_FILENO, buffer, MAX_READ)) > 0) {
        if (fdCount == 0) {
            if (write(STDOUT_FILENO, buffer, n) != n) {
                printf("write error\n");
                exit(1);
            }
        } else {
            for (int i = 0; i < fdCount; i++) {
                if (write(fileFdArr[i], buffer, n) != n) {
                    printf("write error\n");
                    exit(1);
                }
            }
        }
    }

    if (n < 0) {
        printf("read error\n");
        exit(1);
    }

    for (int i = 0; i < fdCount; i++) {
        if (close(fileFdArr[i]) < 0) {
            printf("close error\n");
            exit(1);
        }
    }
    return 0;
}