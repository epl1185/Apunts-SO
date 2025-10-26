#include <stdio.h>
int main() {
    int n = 5;
    int *p = &n;
    int **r = &p;

    *p = *p + 3;
    **r = **r - 2;

    printf("%d\n", n);
}
