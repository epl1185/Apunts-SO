#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    pid_t pid;
    printf("PID actual: %d\n", getpid());
    
    pid = fork();
    
    if (pid == 0) {
        printf("Soy el HIJO - PID: %d, PPID: %d\n", getpid(), getppid());
    } else {
        printf("Soy el PADRE - PID: %d, Hijo: %d\n", getpid(), pid);
    }
    
    sleep(20);
    exit(0);
}