#include <stdio.h>
#include <setjmp.h>

static jmp_buf env;

void fun() {
    int a = 1;
    printf("func return: %d\n", a);
    switch (setjmp(env))
    {
    case 0: // init setjmp
        return;
    case 1:
        printf("back: %d\n", a);
        break;
    }
}

int main(int argc, char *argv[]) {
    fun();
    longjmp(env, 1);
    return 0;
}