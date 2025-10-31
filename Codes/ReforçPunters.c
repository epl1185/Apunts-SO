#include <stdio.h>
int main(int argc, char * argv[])
{
    int a = 10;
    int *p = &a;
    printf("%d \n", p);
    printf("%d \n",*p);
    printf("size of integer is %d bytes \n", sizeof(int));
    printf("%d \n", p + 1);
    printf("%d \n",*(p + 1));
    

}