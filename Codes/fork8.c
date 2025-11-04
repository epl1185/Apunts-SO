#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

 int main(void) {
 int fd;
 pid_t pid = fork();
 fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
 char msg [100];
 sprintf(msg, "Hola, sóc el procés %d\n", getpid());
 write(fd, msg, strlen(msg));
 exit(0);
 }