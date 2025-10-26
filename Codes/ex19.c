#include <stdio.h>
int main() {
    int x = 5;
    int y = 10;
    int *p = &x;
    int *q = &y;
    p = q;
    *p = 20;
    printf("%d %d\n", x, y);
}
