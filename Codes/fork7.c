#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int a = 10;
    if (fork() == 0)
    {
     a = a + 5;
    printf("x=%d\n", a);
    printf("Dirección de a: %p\n", &a);  // Mismo valor en padre e hijo
    exit(0);
    }
    else{
    wait(NULL);
    a = a- 5;
    printf("y=%d\n", a);
    printf("Dirección de a: %p\n", &a);  // Mismo valor en padre e hijo
    }
}