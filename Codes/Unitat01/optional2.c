
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("argc=%d\n", argc);
    if (argc > 1) printf("argv[1]=%s\n", argv[1]);
    printf("argv[argc] is %p \n", (void*)argv[argc]);
    return 0;
}
