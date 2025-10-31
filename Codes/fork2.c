#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
static int i = 11; //.data
int main() {
    int j= 22; // Stack
    int *z = malloc(sizeof(int)); // Heap

    pid_t pid;
    switch (pid=fork())
    {
    case 0:
        i *= 3; 
        j *= 3;
        *z=44;
        break;
    default:
        sleep(3);
        *z=55;
        break;
    }
 
    printf("PID=%ld %s data=%d stack=%d heap=%d\n", 
        (long) getpid(), 
        (pid == 0) ? "(child) " : "(parent)",i,j,*z);
    free(z);
    exit(0);
}