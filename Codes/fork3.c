#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pid_t pid;
  if ((pid = fork()) < 0) {
    exit(-1);
  } else if (pid == 0) {  
    printf("My name is Rhaenyra \n");
  } else {
    printf("My name is King Viserys \n");
  }
  exit(0);
}