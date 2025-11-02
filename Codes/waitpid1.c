#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
pid_t pid, w; int status;
pid = fork();
if (pid == 0) 
{ 
  if (argc == 1) pause(); exit(atoi(argv[1]));
} else {                    
  do {
    w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
    if (w == -1) {
      perror("waitpid"); 
      exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)) {
      printf("exited, [%d] status=%d\n", pid, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("killed by signal, [%d] -> %d\n", pid, WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      printf("stopped by signal [%d] -> %d \n", pid, WSTOPSIG(status));
    } else if (WIFCONTINUED(status)) { 
      printf("continued\n"); }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    exit(0);
    }
}