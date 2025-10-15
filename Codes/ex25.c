#include <stdio.h>
#include <ctype.h>

int main() {
    char msg[] = "hello";
    char output[6];
    char *src = msg;
    char *dst = output;

    for(int i = 0; i < *dst ; i++)
    {
	dst = src;
	src++;
	dst++;
    }


    printf("%s\n", output);
}
