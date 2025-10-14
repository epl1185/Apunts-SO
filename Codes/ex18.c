#include <stdio.h>
int main() {
    int arr[] = {10, 20, 30, 40};
    int *p = arr;
    *(p + 2) = *p + 5;
    p++;
    printf("%d %d\n", *p, *(p+1));
}
