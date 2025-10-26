#include <stdio.h>
int main() {
    char msg[] = "C language";
    char *p = msg;
    int len;

    for(len = 0; *p != '\0'; len++)
    {
        p++;
    }

    for(;len >= 0; len--)
    {
        printf("%c",*p);
        p--;
    }

    return 0;
}
