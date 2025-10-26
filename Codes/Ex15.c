#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int n;
    
    printf("Ingresa el tamaño del array: ");
    scanf("%d", &n);
    
    int *a = (int *) malloc (n * sizeof(int));
    int *ptr = a;
    if(a == NULL)
    {
        perror("Error en reservar memòria");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n ; i++ && a++)
    {
       *ptr = i * 3;
       ptr++;
    }

    ptr = a;

    for(int i = 0; i < n ; i ++)
    {
        printf("L'array [%d] té el valor %d \n", i , *ptr);
        ptr++;
    }
    free(a);
    return 0;
    /* Errors:
    #include <stdlib.h>
#include <errno.h>

int main() {
    int n;
    
    printf("Ingresa el tamaño del array: ");
    scanf("%d", &n);
    
    int *a;

    a = (int *) malloc (n * sizeof(int));
    if(a == NULL)
    {
        perror("Error en reservar memòria");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n ; i++ && a++)
    {
        i++;
        a = &i; // Bucle infinit
        i--;

    }

    for(int i = 0; i < n ; i ++)
    {
        printf("L'array %d té el valor %d \n", i , *a); //Sempre mateixa pos
    }
    free(a); //No apunta al malloc
    return 0;
}
    */
}
