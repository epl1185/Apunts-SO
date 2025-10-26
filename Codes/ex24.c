#include <stdio.h>

struct alumne {
    int id;
    char *nom;
};

int main() {
    struct alumne classe[] = {
        {1, "Marc"}, {2, "Júlia"}, {3, "Pau"}
    };
    int n = sizeof(classe) / sizeof(classe[0]);

    struct alumne *p = classe;

    for(; (int) p < n; p++)
    {
        printf("%d, |%s|",classe[(int) p]);
    }
}
