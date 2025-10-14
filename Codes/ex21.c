#include <stdio.h>
int main() {
    char *s = "Hola";
    char t[] = "Hola";
    if (s == t)
        printf("Iguals\n");
    else
        printf("Diferents\n");
}
