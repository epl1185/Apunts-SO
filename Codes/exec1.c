#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // HIJO: Se transforma en 'ls'
        printf("Hijo [%d] antes de exec\n", getpid());
        
        execl("/bin/ls", "ls", "-l", "-a", NULL);
        
        // ESTA LÍNEA NUNCA SE EJECUTA si exec() tiene éxito
        perror("exec falló");
        exit(1);
    } else {
        // PADRE: Sigue siendo el mismo programa
        wait(NULL);
        printf("Padre [%d] terminó\n", getpid());
    }
    
    return 0;
}