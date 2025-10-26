#include <stdio.h>
int main() {
    int x = 10;
    int *p = &x;
    int **q = &p;

    **q += 5;
    *p = *p * 2;
    printf("%d\n", x);
}
