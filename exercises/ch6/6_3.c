#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern char **environ;


int mySetenv(const char *name, const char *value, int overwrite) {
    if (!(getenv(name) == NULL || overwrite != 0)) {
        return 0;
    }
    // name=value
    int n = strlen(name) + strlen(value) + 1;

    char *kv = (char*) malloc(sizeof(char) * (n + 1));
    if (kv == NULL) {
        return -1;
    }

    kv = strcat(kv, name);
    kv = strcat(kv, "=");
    kv = strcat(kv, value);
    kv[n] = '\0';

    putenv(kv);    
    return 0;
    // char **tmp = environ;
    // int oldN = 0;
    // for ( ; *tmp != NULL; tmp++) {
    //     oldN++;
    // }

    // environ = (char**) realloc(environ, sizeof(char*) * (oldN + 1 + 1));
    // if (environ == NULL) {
    //     return -1;
    // }
    // environ[oldN] = kv;
    // environ[oldN + 1] = NULL;
}

int myUnsetenv(const char *name) {
    char key[1024];
    for (char **tmp = environ; *tmp != NULL; tmp++) {
        memset(key, 0, sizeof(key));
        strcat(key, *tmp);
        size_t sz = strlen(*tmp);
        for (size_t i = 0; i < sz; i++) {
            if (key[i] == '=') {
                key[i] = '\0';
                break;
            }
        }
        if (strcmp(key, name) == 0) {
            *tmp = ""; // 此除可以将后面元素往前移
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    clearenv();

    setenv("test", "test", 1);
    setenv("test", "test2", 0);
    
    myUnsetenv("Name");

    mySetenv("Name", "MrBeast", 1);
    mySetenv("GREET", "MrBeast1", 1);
    mySetenv("GREET", "MrBeast2", 0);
    mySetenv("GREET", "MrBeast3", 1);

    myUnsetenv("Name");

    for (char **ep = environ; *ep != NULL; ep++) {
        puts(*ep);
    }
    exit(EXIT_SUCCESS);
}