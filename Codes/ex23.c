int main() {
    int a[4] = {1, 2, 3, 4};
    int *p = a;

    printf("%d\n", *p++ + *p++);
    return 0;
}
