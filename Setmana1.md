# 🖥️ Apunts de Sistemes Operatius - TEMA 1

## 📋 Índex
- [Setmana 1 - Introducció](#setmana-1---introducció)
- [Exemples Pràctics](#exemples-pràctics)
- [Dubtes i Preguntes](#dubtes-i-preguntes)
- [Reflexions Personals](#reflexions-personals)

---

## 🎯 TEMA 1 - Introducció

### 🔍 Què és un Sistema Operatiu?
El **Sistema Operatiu (SO)** és el programa fonamental que actua com a intermediari entre el maquinari i les aplicacions, gestionant tots els recursos del sistema.

### 🏗️ Sistema Informàtic

Un sistema informàtic és la **interconnexió d’elements de maquinari**, i es pot representar amb el següent esquema:

![Esquema del funcionament d'un sistema informàtic, vist a EDC II](image.png)  
*Figura 1. Representació del funcionament d’un sistema informàtic*

👉 Per tant, **un sistema informàtic és diferent d’un SO**.

---

### 🔹 Bucles infinits i processos

Un bucle infinit pot ser utilitzat per **crear processos infinitament**.  

**Exemple:**
```c
int main() {
    while (1) {
        fork(); //Per sort no l'he executat al meu ordinador
    }
}
```
### 🔹 Màquina Virtual i rols del SO

**Màquina Virtual**: Il·lusió dels programes secundaris; se’ls fa creure que tenen accés exclusiu a tot l’espai d’adreces de memòria del processador.  

**Rols del Sistema Operatiu (SO):**
- **Il·lusionista** → ofereix una interfície simple.  
- **Àrbitre** → responsable de distribuir els recursos disponibles entre usuaris i aplicacions de manera eficient i justa.  
- **Pega** → proporciona serveis i funcionalitats comunes que poden ser compartits i reutilitzats.  

## 🎯 Setmana 1 - Introducció a la programació de Sistema (I) (C)

## Procés de compilació
1. **Preprocessador** → resol `#include`, `#define`, macros → genera `.i`
2. **Compilador** → tradueix a assemblador → genera `.s`
3. **Assemblador** → converteix a codi objecte → genera `.o`
4. **Enllaçador** → combina `.o` + biblioteques → executable final

## Arguments d'entrada

Es deixa l'estructura:
```c
int main(void)
{
    ...
}
```

Per passar a l'estructura:
```c
int 
main(int argc, 
     char *argv[]) 
{...}
```
On:

Argc: Es la longitud del vector d'argument de la terminal

Argv: Matriu de punters de caràcters

## Declaracions externes

Una **declaració externa** en C es aquella que anunica la existencia de una varaiable o funció definida en **un altre fitxer font** o en una altra part del mateix programa, sense reservar memòria adicional.

## Sintaxis
```c
extern int a;
```

Exemple 1:

```c
// fichero1.c
int contador = 0;   

// fichero2.c
extern int contador; 
void incrementar() {
    contador++;
}
```

Exemple 2:

```c
// fichero1.c
int sumar(int a, int b) {
    return a + b;
}

// fichero2.c
extern int sumar(int, int);  // declaración externa
int main() {
    return sumar(2, 3);
}
```

## Codi de les comandes de Linux

Es poden fer les comandes que posem per la terminal amb el llenguatge de c. 

Com a exemple tenim:

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
  int i;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    return -1;
  }
  for (i = 1; i < argc; i++) {
    printf("%s ", argv[i]);
  }
  printf("\n");
  return 0;
}
```
```c
#include <stdio.h>  // Per fprintf() i perror()
#include <unistd.h> // Per chdir()

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }
    if (chdir(argv[1]) == -1) {
        perror("chdir");
        return 1;  
    }
    return 0;  
}
```
Que corresponen, respectivament a les comandes, echo i cd.

M'he proposat "retarme" dient-li a la IA que em faci programar funcions semblants als exemples que se'ns ha donat.

## Makefile

Fitxer de text que conté un conjunt de regles utilitzades per construir un programa.

Exemple de MakeFile:

![alt text](image-1.png)

On dins d'aquest MakeFile trobem que:

 * CC és el compilador a utlitzar
 * CFLAGS són els flags de compilació
 * -O2 singinfica optimització de nivell 2
 * BIN és el directori per a executables
 * Src és el directori per al codi font
 * SOURCES busca tots els *.c en sources/
 * EXECUTABLES sources/programa.c --> bin/programa
 * All compila tots els executables
 * Bin: Crea directori si el bin no existeix 
 * $@ = Nombre de l'objectiu (ex: bin/main)
 * $< = Primera dependencia (ex: sources/main.c)

## Fitxers (obrir, tancar,llegir, descriptors)
## Fitxers (obrir, tancar,llegir, descriptors)

Posaré , directament una interprteació de la teoria.  
![alt text](image-2.png)
---

**Pregunta**:En quin descriptor de fitxer aniría el fitxer file.txt?

**Resposta**:Com que els descriptors de fitxers: 0, 1, 2 dins d'una adreça qualsevol de memòria estan preassigantas, especificament, el descriptor 0 está assignat a stdin, 1 a stdout i el 2 a stderr. Per tant, es crearia un descriptor de fitxer número 3 on hi hauria el fitxer file.txt i successivament pels següents fitxers.

(Pendent de corregir)

Codi donat a la teòria:
```c
#include <errno.h>
#include <fcntl.h>
#include <stdio.h> //fileno() 
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO


int
main() {
    int fd1, fd2, fd3;
    FILE *f;

    printf("STDIN_FILENO: %d\n", STDIN_FILENO);
    printf("stdin: %d\n", fileno(stdin));
    printf("STDOUT_FILENO: %d\n", STDOUT_FILENO);
    printf("stdout: %d\n", fileno(stdout));
    printf("STDERR_FILENO: %d\n", STDERR_FILENO);
    printf("stderr: %d\n", fileno(stderr));

    printf("\nObrint /dev/zero...\n");
    if ((fd1 = open("/dev/zero", O_RDONLY)) < 0) {
        fprintf(stderr, "No es pot obrir /dev/zero: %s\n", strerror(errno));
    } else {
        printf("fd1: %d\n", fd1);
    }

    printf("\nObrint /dev/zero una segona vegada...\n");
    if ((fd2 = open("/dev/zero", O_RDONLY)) < 0) {
        fprintf(stderr, "No es pot obrir /dev/zero: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("fd2: %d\n", fd2);

    printf("\nTancant fd1, perÃ² mantenint fd2 obert...\n");
    (void)close(fd1);

    printf("\nObrint /dev/zero una tercera vegada...\n");
    if ((fd3 = open("/dev/zero", O_RDONLY)) < 0) {
        fprintf(stderr, "No es pot obrir /dev/zero: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("fd3: %d\n", fd3);

    printf("\nAra tancant fd2 i fd3.\n");
    (void)close(fd2);
    (void)close(fd3);

    printf("Ara obrint /dev/zero com a flux.\n");
    if ((f = fopen("/dev/zero", "r")) == NULL) {
        fprintf(stderr, "No es pot obrir /dev/zero: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("f: %d\n", fileno(f));
    (void)fclose(f);

    return EXIT_SUCCESS;
}
```
Que entenc jo que fa aquest codi? (Sense veure el que hi ha a la capçalera)

Primer de tot, hem de buscar, amb quin objectiu s'han implementat les llibreies, encara que el mateix codi, ens ajuda a dir quines són les funcions en específic:

### Libreria: <fcntl.h>
#### Funciones Clave
- int open(const char *, int, ...), 
- O_RDONLY Open for reading only
- PERÒ NO EL CLOSE()

### Libreria: <stdio.h>
#### Funciones Clave
- printf
- stderr (Standard error output stream),stdin (Standard input stream).stdout
(Standard output) 
- int fileno(FILE *)
- FILE *fopen(const char *, const char *)
- int, printf(FILE *, const char *, ...)

### Libreria: <stdlib.h>
#### Funciones Clave
 - EXIT_FAILURE (Se expande a 8; lo utiliza la función atexit donde La función atexit() registra la función, a la que apunta func, que el sistema llama al final normal del programa. 
 - També tenim ** EXIT_SUCCESS :Se expande a 0; lo utiliza la función atexit
### Libreria: <string.h>
#### Funciones Clave 
 - He provat a compilar el programa sense string.h però se'm dona un warning de que no troba el prototip de la funció. Que significa això? Vol dir que en la funció strerror crida a la llibería string.h 
### Libreria: <unistd.h>
#### Funciones Clave 
- STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO: Retornen els descriptors de fitxers associats a STDIN, STDOUT, STDERR

Un cop analitzades les funcions, podem dir que fa el codi de manera global:

* Primer s'inicialitzen els enters i un punter que apunta a FILE.
* Després s'ens ensenya que els descriptors de fitxers stdin, stdout, stderror, tenen com a enters associats: 0, 1, 2 respectivament.
* Amb la funció open(), que retorna un enter, s'ens ensenya que l'enter al descriptor (fd1) associat és 3, en la majoría de casos sempre que no es compleixi l'id.
* Passem on el fd2 és obert, si fd1 és 3, llavors fd2 será 4. Altrament fd2 serà 3. Ja que no hi ha cap condició a satisfer.
* Fd3 és obert, però fd1 ha sigut tancat i l'enter 3 ha quedat lliberat, per tant, s'associarà l'enter 3 a fd3.
* Ultimament, els descriptors de fitxers, fd2, fd3, son "alliberats", per tant, quan obrim el fitxer amb la instrucció f = fopen("/dev/zero", "r")) NO estem associant cap enter, sino que unicament volem obrir dev/zero com a flux. Després, quan es fa fileno(f), es retorna l'enter 3.

(Resposta basada en el que diu @Deepseek)

Codi donat a la teòria:
```c
#include <errno.h>
#include <fcntl.h>
#include <stdio.h> //fileno() 
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO


int
main() {
    int fd1, fd2, fd3;
    FILE *f;

    printf("STDIN_FILENO: %d\n", STDIN_FILENO);
    printf("stdin: %d\n", fileno(stdin));
    printf("STDOUT_FILENO: %d\n", STDOUT_FILENO);
    printf("stdout: %d\n", fileno(stdout));
    printf("STDERR_FILENO: %d\n", STDERR_FILENO);
    printf("stderr: %d\n", fileno(stderr));

    printf("\nObrint /dev/zero...\n");
    if ((fd1 = open("/dev/zero", O_RDONLY)) < 0) {
        fprintf(stderr, "No es pot obrir /dev/zero: %s\n", strerror(errno));
    } else {
        printf("fd1: %d\n", fd1);
    }

    printf("\nObrint /dev/zero una segona vegada...\n");
    if ((fd2 = open("/dev/zero", O_RDONLY)) < 0) {
        fprintf(stderr, "No es pot obrir /dev/zero: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("fd2: %d\n", fd2);

    printf("\nTancant fd1, perÃ² mantenint fd2 obert...\n");
    (void)close(fd1);

    printf("\nObrint /dev/zero una tercera vegada...\n");
    if ((fd3 = open("/dev/zero", O_RDONLY)) < 0) {
        fprintf(stderr, "No es pot obrir /dev/zero: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("fd3: %d\n", fd3);

    printf("\nAra tancant fd2 i fd3.\n");
    (void)close(fd2);
    (void)close(fd3);

    printf("Ara obrint /dev/zero com a flux.\n");
    if ((f = fopen("/dev/zero", "r")) == NULL) {
        fprintf(stderr, "No es pot obrir /dev/zero: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("f: %d\n", fileno(f));
    (void)fclose(f);

    return EXIT_SUCCESS;
}
```
Que entenc jo que fa aquest codi? (Sense veure el que hi ha a la capçalera)

Primer de tot, hem de buscar, amb quin objectiu s'han implementat les llibreies, encara que el mateix codi, ens ajuda a dir quines són les funcions en específic:

### Libreria: <fcntl.h>
#### Funciones Clave
- int open(const char *, int, ...), 
- O_RDONLY Open for reading only
- PERÒ NO EL CLOSE()

### Libreria: <stdio.h>
#### Funciones Clave
- printf
- stderr (Standard error output stream),stdin (Standard input stream).stdout
(Standard output) 
- int fileno(FILE *)
- FILE *fopen(const char *, const char *)
- int, printf(FILE *, const char *, ...)

### Libreria: <stdlib.h>
#### Funciones Clave
 - EXIT_FAILURE (Se expande a 8; lo utiliza la función atexit donde La función atexit() registra la función, a la que apunta func, que el sistema llama al final normal del programa. 
 - També tenim ** EXIT_SUCCESS :Se expande a 0; lo utiliza la función atexit
### Libreria: <string.h>
#### Funciones Clave 
 - He provat a compilar el programa sense string.h però se'm dona un warning de que no troba el prototip de la funció. Que significa això? Vol dir que en la funció strerror crida a la llibería string.h 
### Libreria: <unistd.h>
#### Funciones Clave 
- STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO: Retornen els descriptors de fitxers associats a STDIN, STDOUT, STDERR

Un cop analitzades les funcions, podem dir que fa el codi de manera global:

* Primer s'inicialitzen els enters i un punter que apunta a FILE.
* Després s'ens ensenya que els descriptors de fitxers stdin, stdout, stderror, tenen com a enters associats: 0, 1, 2 respectivament.
* Amb la funció open(), que retorna un enter, s'ens ensenya que l'enter al descriptor (fd1) associat és 3, en la majoría de casos sempre que no es compleixi l'id.
* Passem on el fd2 és obert, si fd1 és 3, llavors fd2 será 4. Altrament fd2 serà 3. Ja que no hi ha cap condició a satisfer.
* Fd3 és obert, però fd1 ha sigut tancat i l'enter 3 ha quedat lliberat, per tant, s'associarà l'enter 3 a fd3.
* Ultimament, els descriptors de fitxers, fd2, fd3, son "alliberats", per tant, quan obrim el fitxer amb la instrucció f = fopen("/dev/zero", "r")) NO estem associant cap enter, sino que unicament volem obrir dev/zero com a flux. Després, quan es fa fileno(f), es retorna l'enter 3.

(Resposta basada en el que diu @Deepseek)

**Codi per obrir un fitxer**:

```c
#include < sys/types.h> 
#include < sys/stat.h> 
#include < fcntl.h> 

int open ( const char *path, 
  int flags [, mode_t mode ]);
int creat (const char *path, 
  mode_t mode);
  ```

 Que entenc jo per aquest codi?
 Dins dels codi trobem:

 Que entenc jo per aquest codi?
 Dins dels codi trobem:
 * Linies 1 - 3: Declaració de llibreries:

    * #include < sys/types.h> 
    * #include < sys/stat.h> 
    * #include < fcntl.h>.

    Per saber el que utiltza cada llibreria fem, en la terminal de Linux, o per Google directament busquem la llibería:

    *man 
    *man 
    *man fcntl

    La llibrería fnctl és la que ens permet importar tant les funcions Creat com Open amb els seus repsectius paràmetres d'E/S. Després veiem que els paràmetres d'entrada són: Un punter de char, que bé podría ser argv[1]. Després, per definir el mode, necessitem un enter, on ha d'estar definit per <sys/types.h> (per exemple :0700 vol dir tots els permissos. Ultimament, tenim que <sys/stat.h> és la que defineix les constants del path, encara que es podria definir també el path amb un define tal que 
    ```c
    #define PATH "/home/jordi" 
    ```
    (dubto del que dic sobre <sys/stat.h>)
    * #include < fcntl.h>.

    Per saber el que utiltza cada llibreria fem, en la terminal de Linux, o per Google directament busquem la llibería:

    *man 
    *man 
    *man fcntl

    La llibrería fnctl és la que ens permet importar tant les funcions Creat com Open amb els seus repsectius paràmetres d'E/S. Després veiem que els paràmetres d'entrada són: Un punter de char, que bé podría ser argv[1]. Després, per definir el mode, necessitem un enter, on ha d'estar definit per <sys/types.h> (per exemple :0700 vol dir tots els permissos. Ultimament, tenim que <sys/stat.h> és la que defineix les constants del path, encara que es podria definir també el path amb un define tal que 
    ```c
    #define PATH "/home/jordi" 
    ```
    (dubto del que dic sobre <sys/stat.h>)

    Dins d'aquestes llibreries, es produeixen les següents crides a sistema (Creat per l'IA):
    * open()	sys_open	Abre archivo en el kernel
    * creat()	sys_open	Crear archivo (especialización de open)
    * close()	sys_close	Cierra descriptor de archivo
    * fopen()	sys_open + buffering	Abre con buffer (stdio.h)
    * fclose()	sys_close	Cierra archivo con buffer
    * printf()	sys_write	Escribe a stdout (a través de buffer)
    * scanf()	sys_read	Lee de stdin (a través de buffer)
    * malloc()	sys_brk / sys_mmap	Asigna memoria del heap
    * free()	sys_brk / sys_munmap	Libera memoria del heap

**Codi per llegir un fitxer**:
```c
#include <unistd.h> 
ssize_t read(int fd, void *buf, size_t);

ssize_t write(int fd, void *buf, size_t);
 ```

 ### Intepretació de codi:
```c
int main(int argc, char* argv[]) {
  char string[11]; int b_read;
  int file = open ("my_file", O_RDONLY); 
  if(file == -1) { 
    perror("Error while opening file");
    exit(1);
  }
  b_read = read(file, string, 10);
  close(file);
  string[10] = 0;
  printf("%d B have been read. The obtained string is: %s\n", 
    b_read, string);
  return 0;
}
```
Que entenc jo d'aquest codi?

* Primerament, declarem tant un array de caràcters de MIDA 11, i un index per fer la lectura del fitxer.
Seguidament, es llegeix el fitxer, si es retorna -1 vol dir que hi ha hagut un error obrint el fitxer. Un cop s'ha obrit, l'hem de llegir, indicant la mida de bytes (10 en aquest cas), pasant-li el buffer, que en aquest cas és string[11]. Podem dir que s'imprimira els strings: string[0], string[1], string[2],... , string[9] amb el nombre de bytes llegits, ja que string[10] = 0 es NULL. Per tant un exemple d'output seria: 
Fitxer:{'H','e','l','l','o','W','o','r','l','d'}
Output: HelloWorld

Com a equivalent, podem dir que aquest codi, fa més del mateix però utilitzant seek: 
```c
#include <fcntl.h>  // Open modes
#include <unistd.h> // Many POSIX functions
#include <stdlib.h> // File functions
#include <stdio.h>  // Standard I/O

int main() {
  char string[11];
  int b_read;

  int file = open ("files/my_file", O_RDONLY); 
  if(file == -1) { 
    perror("Error while opening file");
    exit(1);
  }

  lseek(file, 46, SEEK_SET);
  b_read = read(file, string, 10); // Read 10 bytes
  close(file);

  string[10] = 0;
  printf("%d B have been read. The obtained string is: %s\n", 
  b_read, string);

  return 0;
}
```
* Sent SEEK_SET: el punter es col·loca offset bytes.(10 en aquest cas)

**Codi per escruire en un fitxer**:
```c
int main(int argc, char* argv[]) {

  const char* string = "\nWinter is coming\n\n";

  int file = open("new_file", O_CREAT|O_WRONLY, 0644);

  if(file == -1) { 
    perror("Error when opening file");
    exit(1);
  }

  write(file, string, strlen(string));
  close(file);

  exit(0);
}
```
* Es declara un const char* string amb el contingut que volem posar dins del fitxer. Després, tenim que sobre el fitxer amb uns certs permissos, en específic, només escriure i crear el fitxer si no existeix amb un cert mode(ara no m'en enrecordo).
En cas d'error es retorna -1 i en cas de succès s'esciriu l'string dins del fitxer indicant la seva mida amb strlen.

```c
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main() {
  int fd;
  if((fd = creat("new_file2", 0644)) < 0) {
    perror("new_file2"); exit(-1);
  }

  if(write(fd, buf1, 10) != 10)       perror("buf1");    // offset == 10
  if(lseek(fd, 4, SEEK_SET) == -1)    perror("lseek");   // offset == 4
  if(write(fd, buf2, 10) != 10)       perror("buf2");    // offset == 14

  return 0;
}
```
* En aquest cas, inicialitzem dos buffers amb lletres minuscúles i majúscules.Dins del main, s'inicialtza un fitxer amb fd, es crea un fixter. En cas d'error es retorna -1.Després, volem escriure abcdefghij, que justament són 10 bytes, per tant, s'escriuran sense cap problema. Amb seek_set és mouen un total de 14 bytes i després s'escriuen els 10 caràcters amb majúscles restants.

### Punters

&: Retorna l’adreça de l’apuntador. Per exemple &x ens dóna l’adreça de la variable x.

*: Retorna el valor de la variable situada a l’adreça especificada pel seu operand (dereferencing).

```c
int 
main (int argc, 
    char * argv[]){
    int s=10;
    float f=10.5;
    char a='a';

    int *pt1 = &s;
    float *pt2 = &f;
    char *pt3= &a;
    printf(%d,%f,&c, *pt1,*pt2,*pt3);
};
```

En aquest codi, podem veure que si fessim printf tal que:

 veuirem respectivament, 10, 10,5,a, ja que amb la instrucció int *pt1 = &s, dona el que hi ha dins de l'adreça de memòria.

 ```c
 int n = 2;
int *ptr1 = NULL;
ptr1 = &n;
(*ptr1)++        //Modifiquem el valor de la variable a la que apunta
ptr1++           //Modifiquem l'adreça de memòria on apunta
```
Tenim que l'output serà l'adreça de memòria de n incrementada una posició i dins d'aquesta adreça de memòria, tenim que el contigut n'és 3.

```c
#include <stdio.h>

void sumar_per_referencia(int *a, int *b) {
    *a = *a + *b;
}

int main() {
    int x = 5; int y = 3;
    printf("Abans de la crida per referència: x = %d, y = %d\n", x, y);
    sumar_per_referencia(&x, &y);
    printf("Després de la crida per referència: x = %d, y = %d\n", x, y);
    return 0;
}
```

En aquest programa podem veure els pàs de paràmetre per refèrencia, es pasa a la funció l'adreça de memòria tant d'x com a y, però en la funció es tracten amb els punters que apunten a l'adreça de memòria, per tant, simplement s'incrementa el contingut que hi ha dins de l'adreça de memòria de x a + b vegades.

### Stack Vs LIFO

Stack: És una estructura LIFO (Last-In,First-Out). La pila és una regió especial de memòria i la gestiona automàticament la CPU, de manera que no cal assignar ni desassignar memòria.

![Esquema del funcionament d'una pila LIFO, vist a EDC II](image-3.png) 

*Figura 1. Representació del funcionament d’una pila LIFO*

HEAP: La heap és una àrea de memòria on s’assigna memòria de manera dinàmica durant el temps d’execució.

He vist que la Heap pot ser representada en forma de graf, no entenc molt bé el perqué, volia posar una imatge però no puc posar quelcom que no entenc.

La heap permet emmagatzemar items a la memòria en quaelvol ordre.Podem accedir a ell en qualsevol moment.És més localitzar la dada específica.

* Interpretació de codi 
```c
int main() {     
    int y;   
    char *str; 
    y = 4;
    printf("stack memory: %d\n", y);
    str = malloc(100*sizeof(char)); 
    str[0] = 'm';
    printf("heap memory:%c\n", str[0]); 
    free(str);         
    return 0;
}
```
En aquest codi, se'ns vol ensenyar com funciona tant l'stack com el heap.
Per una part, podem veure com en l'stack s'emmagatzemen les variables locals i les funcions. En aquest cas són main i y. Després, podem veure com amb malloc reservem 100 * bytes d'un char.Dins del punter de caràcters és posa m a la posició str[0], després es mostra la m emmgagatzemada a la heap i s'allibera la memòria.

![alt text](image-4.png)

```c
void ordenar(int n, int* ptr)
{
    int i, j, t;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (*(ptr + j) < *(ptr + i)) {
                t = *(ptr + i);
                *(ptr + i) = *(ptr + j);
                *(ptr + j) = t;
            }
        }
    }
}

int 
main() {
    char msg[250];
    int *a, n, i;

    sprintf(msg, "Introdueix el nombre d'elements de l'array: \n");
    write(STDOUT_FILENO, msg, strlen(msg));
    scanf("%d", &n);

    a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        perror("Error en reservar memÃ²ria");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        sprintf(msg, "Introdueix un element de l'array: \n");
        write(STDOUT_FILENO, msg, strlen(msg));
        scanf("%d", a + i);
    }

    ordenar(n, a);


    for (i = 0; i < n; i++) {
        sprintf(msg, "a[%d] = %d\n", i, *(a + i));
        write(STDOUT_FILENO, msg, strlen(msg));
    }

    free(a);

    exit(EXIT_SUCCESS);
}
```

* Declaracions

    *char msg[250];
    *int *a, n, i;
* Esquelet del programa
    * Amb la funció sprintf podem printejar una sortida en un buffer de memòria (string)
    * Després s'escriu al fitxer, passant el descriptor de fitxer, essent msg el mateix buffer i strlen determina la mida d'strings de chars.
    * En una adreça de memòria, posem el número que ha posat l'usuari.
    * Es reserva a la heap , la MIDA: malloc(n * sizeof(int)). En cas d'error es retorna NULL.
    * En cas de succés, esrivim els elements que l'usuari vulgui al fitxer, dins la mida que ha introduit.
    * Després dins del mateix fitxer, s'ordena mitjançant bubble sort de més petit a més gran, es a dir de A a la Z.
    * Un cop hem ordenat l'array de chars, printejem els elements de manera ordenada. I els esrivim dins de msg.
    * Un cop acabat alliberem la memòria dinàmica assignada.

Sigui el següent codi, utlitzant la funció anterior:
```c
capta_dades(int n, int* nums) {
  while (scanf("%d", &num) != EOF) {
    if (n >= max_elements) {
      max_elements *= 2;
      int* temp = (int*)realloc(nums, max_elements * sizeof(int));
      if (temp == NULL) {
        printf("Error en l'assignació de memòria.\n");
        free(nums);
        return 1;
      }
      nums = temp;
    }
  nums[n] = num;
  n++;
  }
}
int main() {
    int* nums = NULL;  
    int n = 0, max_elements = 10, num;

    nums = (int*)malloc(max_elements * sizeof(int));
    if (nums == NULL) {
        printf("Error en l'assignació de memòria.\n");
        return 1;
    }

    capta_dades(n, nums);
    ordenar(n, nums);
    free(nums);
    return 0;
}
```
* Declaracions
    * int* nums = NULL;  
    * int n = 0, max_elements = 10, num;
* Esquelet del programa
    * Es reserva memòria a la Heap amb max_elements * sizeof(int).
    * En el captadades es passen tant l'n que és 0 com la Memòria reservada a la Heap.
    * Recorrem tots els elementos mentre hi hagi memòria, altrament es retorna EOF.
    * Després, tenim que si el nombre n > max_elements, es dupliquen el màxim d'elements *2, així ens assugurem de que n sigui < max_elements la següent vegada, també es reassgina la memòria. Per després poder reassignar a nums.
    * Finalement afegim l'element a nums i incrementem n.
    * Ordenem i allibrem la memòria perquè és bona pràctica.
    
### Structs i TypeDef

Typedef: Crear sinònims per a noms de tipus de dades definits prèviament.
Exemples:
```c
typedef int L;
int a;
L a;
```
Struct: Per a crear classes (com en java)
```c
Classe user:
typedef struct 
{
    int pid;
    char * name;
    } User; 

Instància de user:
    User user;
    user.name="
    Jordi Mateo";
    user.pid=5000;
    
Una altra instància de user:
    User * user1;
    user1->name="Jack sparrow";
    *(user1).pid=5001;
    User *user2 = &user;
```
**Codi per llegir un fitxer**:
```c
#include <unistd.h> 
ssize_t read(int fd, void *buf, size_t);

ssize_t write(int fd, void *buf, size_t);
 ```

 ### Intepretació de codi:
```c
int main(int argc, char* argv[]) {
  char string[11]; int b_read;
  int file = open ("my_file", O_RDONLY); 
  if(file == -1) { 
    perror("Error while opening file");
    exit(1);
  }
  b_read = read(file, string, 10);
  close(file);
  string[10] = 0;
  printf("%d B have been read. The obtained string is: %s\n", 
    b_read, string);
  return 0;
}
```
Que entenc jo d'aquest codi?

* Primerament, declarem tant un array de caràcters de MIDA 11, i un index per fer la lectura del fitxer.
Seguidament, es llegeix el fitxer, si es retorna -1 vol dir que hi ha hagut un error obrint el fitxer. Un cop s'ha obrit, l'hem de llegir, indicant la mida de bytes (10 en aquest cas), pasant-li el buffer, que en aquest cas és string[11]. Podem dir que s'imprimira els strings: string[0], string[1], string[2],... , string[9] amb el nombre de bytes llegits, ja que string[10] = 0 es NULL. Per tant un exemple d'output seria: 
Fitxer:{'H','e','l','l','o','W','o','r','l','d'}
Output: HelloWorld

Com a equivalent, podem dir que aquest codi, fa més del mateix però utilitzant seek: 
```c
#include <fcntl.h>  // Open modes
#include <unistd.h> // Many POSIX functions
#include <stdlib.h> // File functions
#include <stdio.h>  // Standard I/O

int main() {
  char string[11];
  int b_read;

  int file = open ("files/my_file", O_RDONLY); 
  if(file == -1) { 
    perror("Error while opening file");
    exit(1);
  }

  lseek(file, 46, SEEK_SET);
  b_read = read(file, string, 10); // Read 10 bytes
  close(file);

  string[10] = 0;
  printf("%d B have been read. The obtained string is: %s\n", 
  b_read, string);

  return 0;
}
```
* Sent SEEK_SET: el punter es col·loca offset bytes.(10 en aquest cas)

**Codi per escruire en un fitxer**:
```c
int main(int argc, char* argv[]) {

  const char* string = "\nWinter is coming\n\n";

  int file = open("new_file", O_CREAT|O_WRONLY, 0644);

  if(file == -1) { 
    perror("Error when opening file");
    exit(1);
  }

  write(file, string, strlen(string));
  close(file);

  exit(0);
}
```
* Es declara un const char* string amb el contingut que volem posar dins del fitxer. Després, tenim que sobre el fitxer amb uns certs permissos, en específic, només escriure i crear el fitxer si no existeix amb un cert mode(ara no m'en enrecordo).
En cas d'error es retorna -1 i en cas de succès s'esciriu l'string dins del fitxer indicant la seva mida amb strlen.

```c
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main() {
  int fd;
  if((fd = creat("new_file2", 0644)) < 0) {
    perror("new_file2"); exit(-1);
  }

  if(write(fd, buf1, 10) != 10)       perror("buf1");    // offset == 10
  if(lseek(fd, 4, SEEK_SET) == -1)    perror("lseek");   // offset == 4
  if(write(fd, buf2, 10) != 10)       perror("buf2");    // offset == 14

  return 0;
}
```
* En aquest cas, inicialitzem dos buffers amb lletres minuscúles i majúscules.Dins del main, s'inicialtza un fitxer amb fd, es crea un fixter. En cas d'error es retorna -1.Després, volem escriure abcdefghij, que justament són 10 bytes, per tant, s'escriuran sense cap problema. Amb seek_set és mouen un total de 14 bytes i després s'escriuen els 10 caràcters amb majúscles restants.

### Punters

&: Retorna l’adreça de l’apuntador. Per exemple &x ens dóna l’adreça de la variable x.

*: Retorna el valor de la variable situada a l’adreça especificada pel seu operand (dereferencing).

```c
int 
main (int argc, 
    char * argv[]){
    int s=10;
    float f=10.5;
    char a='a';

    int *pt1 = &s;
    float *pt2 = &f;
    char *pt3= &a;
    printf(%d,%f,&c, *pt1,*pt2,*pt3);
};
```

En aquest codi, podem veure que si fessim printf tal que:

 veuirem respectivament, 10, 10,5,a, ja que amb la instrucció int *pt1 = &s, dona el que hi ha dins de l'adreça de memòria.

 ```c
 int n = 2;
int *ptr1 = NULL;
ptr1 = &n;
(*ptr1)++        //Modifiquem el valor de la variable a la que apunta
ptr1++           //Modifiquem l'adreça de memòria on apunta
```
Tenim que l'output serà l'adreça de memòria de n incrementada una posició i dins d'aquesta adreça de memòria, tenim que el contigut n'és 3.

```c
#include <stdio.h>

void sumar_per_referencia(int *a, int *b) {
    *a = *a + *b;
}

int main() {
    int x = 5; int y = 3;
    printf("Abans de la crida per referència: x = %d, y = %d\n", x, y);
    sumar_per_referencia(&x, &y);
    printf("Després de la crida per referència: x = %d, y = %d\n", x, y);
    return 0;
}
```

En aquest programa podem veure els pàs de paràmetre per refèrencia, es pasa a la funció l'adreça de memòria tant d'x com a y, però en la funció es tracten amb els punters que apunten a l'adreça de memòria, per tant, simplement s'incrementa el contingut que hi ha dins de l'adreça de memòria de x a + b vegades.

### Stack Vs LIFO

Stack: És una estructura LIFO (Last-In,First-Out). La pila és una regió especial de memòria i la gestiona automàticament la CPU, de manera que no cal assignar ni desassignar memòria.

![Esquema del funcionament d'una pila LIFO, vist a EDC II](image-3.png) 

*Figura 1. Representació del funcionament d’una pila LIFO*

HEAP: La heap és una àrea de memòria on s’assigna memòria de manera dinàmica durant el temps d’execució.

He vist que la Heap pot ser representada en forma de graf, no entenc molt bé el perqué, volia posar una imatge però no puc posar quelcom que no entenc.

La heap permet emmagatzemar items a la memòria en quaelvol ordre.Podem accedir a ell en qualsevol moment.És més localitzar la dada específica.

* Interpretació de codi 
```c
int main() {     
    int y;   
    char *str; 
    y = 4;
    printf("stack memory: %d\n", y);
    str = malloc(100*sizeof(char)); 
    str[0] = 'm';
    printf("heap memory:%c\n", str[0]); 
    free(str);         
    return 0;
}
```
En aquest codi, se'ns vol ensenyar com funciona tant l'stack com el heap.
Per una part, podem veure com en l'stack s'emmagatzemen les variables locals i les funcions. En aquest cas són main i y. Després, podem veure com amb malloc reservem 100 * bytes d'un char.Dins del punter de caràcters és posa m a la posició str[0], després es mostra la m emmgagatzemada a la heap i s'allibera la memòria.

![alt text](image-4.png)

```c
void ordenar(int n, int* ptr)
{
    int i, j, t;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (*(ptr + j) < *(ptr + i)) {
                t = *(ptr + i);
                *(ptr + i) = *(ptr + j);
                *(ptr + j) = t;
            }
        }
    }
}

int 
main() {
    char msg[250];
    int *a, n, i;

    sprintf(msg, "Introdueix el nombre d'elements de l'array: \n");
    write(STDOUT_FILENO, msg, strlen(msg));
    scanf("%d", &n);

    a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        perror("Error en reservar memÃ²ria");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        sprintf(msg, "Introdueix un element de l'array: \n");
        write(STDOUT_FILENO, msg, strlen(msg));
        scanf("%d", a + i);
    }

    ordenar(n, a);


    for (i = 0; i < n; i++) {
        sprintf(msg, "a[%d] = %d\n", i, *(a + i));
        write(STDOUT_FILENO, msg, strlen(msg));
    }

    free(a);

    exit(EXIT_SUCCESS);
}
```

* Declaracions

    *char msg[250];
    *int *a, n, i;
* Esquelet del programa
    * Amb la funció sprintf podem printejar una sortida en un buffer de memòria (string)
    * Després s'escriu al fitxer, passant el descriptor de fitxer, essent msg el mateix buffer i strlen determina la mida d'strings de chars.
    * En una adreça de memòria, posem el número que ha posat l'usuari.
    * Es reserva a la heap , la MIDA: malloc(n * sizeof(int)). En cas d'error es retorna NULL.
    * En cas de succés, esrivim els elements que l'usuari vulgui al fitxer, dins la mida que ha introduit.
    * Després dins del mateix fitxer, s'ordena mitjançant bubble sort de més petit a més gran, es a dir de A a la Z.
    * Un cop hem ordenat l'array de chars, printejem els elements de manera ordenada. I els esrivim dins de msg.
    * Un cop acabat alliberem la memòria dinàmica assignada.

Sigui el següent codi, utlitzant la funció anterior:
```c
capta_dades(int n, int* nums) {
  while (scanf("%d", &num) != EOF) {
    if (n >= max_elements) {
      max_elements *= 2;
      int* temp = (int*)realloc(nums, max_elements * sizeof(int));
      if (temp == NULL) {
        printf("Error en l'assignació de memòria.\n");
        free(nums);
        return 1;
      }
      nums = temp;
    }
  nums[n] = num;
  n++;
  }
}
int main() {
    int* nums = NULL;  
    int n = 0, max_elements = 10, num;

    nums = (int*)malloc(max_elements * sizeof(int));
    if (nums == NULL) {
        printf("Error en l'assignació de memòria.\n");
        return 1;
    }

    capta_dades(n, nums);
    ordenar(n, nums);
    free(nums);
    return 0;
}
```
* Declaracions
    * int* nums = NULL;  
    * int n = 0, max_elements = 10, num;
* Esquelet del programa
    * Es reserva memòria a la Heap amb max_elements * sizeof(int).
    * En el captadades es passen tant l'n que és 0 com la Memòria reservada a la Heap.
    * Recorrem tots els elementos mentre hi hagi memòria, altrament es retorna EOF.
    * Després, tenim que si el nombre n > max_elements, es dupliquen el màxim d'elements *2, així ens assugurem de que n sigui < max_elements la següent vegada, també es reassgina la memòria. Per després poder reassignar a nums.
    * Finalement afegim l'element a nums i incrementem n.
    * Ordenem i allibrem la memòria perquè és bona pràctica.
    
### Structs i TypeDef

Typedef: Crear sinònims per a noms de tipus de dades definits prèviament.
Exemples:
```c
typedef int L;
int a;
L a;
```
Struct: Per a crear classes (com en java)
```c
Classe user:
typedef struct 
{
    int pid;
    char * name;
    } User; 

Instància de user:
    User user;
    user.name="
    Jordi Mateo";
    user.pid=5000;
    
Una altra instància de user:
    User * user1;
    user1->name="Jack sparrow";
    *(user1).pid=5001;
    User *user2 = &user;
```
## Exemples pràctics

M’he creat aquests exercicis amb IA. La idea és **deduir què fa cada programa pas a pas** i relacionar-ho amb la teoria vista a classe. (Com estic repassant el tema 1 en la setmana 3, m'he donat la llibertat de posar conceptes encara no vistos)
M’he creat aquests exercicis amb IA. La idea és **deduir què fa cada programa pas a pas** i relacionar-ho amb la teoria vista a classe. (Com estic repassant el tema 1 en la setmana 3, m'he donat la llibertat de posar conceptes encara no vistos)

#### Exercici 1
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int *p = malloc(sizeof(int));
    printf("Memòria assignada a: %p\n", (void*)p);
    
    for(int i = 1; i <= 5; i++) {
        *p = i;  
        printf("[PID: %d] Valor: %d\n", getpid(), *p);
        fflush(stdout);  
        sleep(1);      
    }
    
    free(p);  
    return 0;
}
````
Amb la següent execució: ./prog1 & ./prog1

Raonament, sense correcció prèvia:
Amb el void dedueixo que es vol entrar dins del contingut de la adreça del punter, pero al posar %p, simplement s'impremeix l'adreça de memòria.
Després s'imprimiria el que hi ha dins del bucle for,el pid que faria referència al procès que s'esta executant i 1, 2, 3, 4, amb pauses d'un segon ja que tenim l'sleep.

Per tant els dos processos utlitzaran la mateixa adreça de memòria i com que el processador escolleix els processos de forma alternada, primerament les adreçes de memòria i després el número de procés amb el valor que hi ha dins del punter.

Si hi ha alguna discrepancia,tant per la meva part m'ho podries notificar?

Correcció per part de la IA:
malloc reserva memòria al heap i p té l’adreça retornada.

Imprimeix aquesta adreça i després, 5 vegades, escriu *p = i i imprimeix [PID: X] Valor: i amb sleep(1) entre iteracions.

Finalment free(p) i el procés acaba.

El primer ./prog1 & llança el primer procés en background i torna el prompt al shell.(Realment no se que vol dir això, ja que havia vist que: Les adreçes virtuals protegeixen els processosos entre ells i permeten que tots dos processos puguin fer servir la mateixa adreça sense afectar-se.

Immediatament després, el shell executa ./prog1 en primer pla (foreground). Així tens dos processos del mateix programa corrent concurrentment: un en background i un en foreground.

Ambdós s’executen simultàniament: el scheduler del SO alternarà l’execució entre ells. Per tant les línies que imprimeixen s’intercalaran de manera no determinista

Exemple de output:
```c
Memòria assignada a: 0x55a1f3b26010
Memòria assignada a: 0x55a1f3b26010
[PID: 2345] Valor: 1
[PID: 1234] Valor: 1
[PID: 2345] Valor: 2
[PID: 1234] Valor: 2
[PID: 1234] Valor: 3
[PID: 2345] Valor: 3
...
```
#### Exercici 2

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    for (int i=0;i<5;i++){
        printf("line %d ", i);    // note: no '\n'
        fflush(NULL);             // (optional—remove to see difference)
        sleep(1);
    }
    return 0;
}
```
Amb les comandes: 

A) ./prog2

B) ./prog2 | cat

C) ./prog2 > out.txt (y mira cat out.txt mientras se ejecuta)

¿Qué diferencias verás entre A, B y C y por qué?

Raonament per a arribar a la solució:
En l'opció a se'ns dona una compilació normal (és a dir del arxiu), per tant, l'output serà: 0,1,2,3,4.

En l'opció b se'ns dona una compilació amb | cat , sabem que la instrucció cat concatena i mostra un arxiu. Després dedueixo que | deu ser algún tipus de , dirigeixte aquí per concatenarte, per tant seria 01234.

En l'opció c se'ns dona una compilació on amb la fletxa es redirigeix al fitxer out.txt, per tant s'escriurà 01234 dins del fietxer out.txt 

Solució:

a line 0 line 1 line 2 line 3 line 4

b line 0 line 1 line 2 line 3 line 4  (el mateix que a l'apartat a)

c Line 0 line 1 line 2 line 3 line 4 dins del fitxer output.txt


#### Exercici 3
#include <stdio.h>
```c
int main(int argc, char *argv[]) {
    printf("argc=%d\n", argc);
    if (argc > 1) printf("argv[1]=%s\n", argv[1]);
    printf("argv[argc] is %p\n", (void*)argv[argc]);
    return 0;
}
```
Amb la comanda:

A) ./optional2

Raonament per a arribar a la solució:

En el primer printf es passen el nombre d'arguments que es reben per terminal, en aquest cas només és un. Després en el condicional if, no compleix la condició així que no es "printeja" res. Ultimament es printeja l'adreça de memoria on apunta argv[]

Solució:

argc=1

argv[argc] is (nil)

#### Exercici 4-13 Preguntes Teòriques-Pràctiques

##### Ex 4
¿Por qué este código es peligroso?

```c
int *p = malloc(sizeof(int));
free(p);
printf("%d", *p);
```

**Resposta**:

Aquest codi és perillós ja s'assigna un punter amb la mida d'un enter (4 bits), però dins de l'adreça de memòria no s'assigna res. Per tant, al fer el free, realment no es "dessasigna" res. Per tant, s'hauria de printar l'adreça de memòria si no s'ha donat un error abans.

**Solució**:

Després de free(p), el punter p és dangling (apunta a memòria alliberada). Accedir a *p és undefined behavior.

##### Ex 5
En el Makefile, ¿qué hace exactamente esta línea?

makefile

EXECUTABLES = $(patsubst $(SRC)/%.c,$(BIN)/%,$(SOURCES))

**Resposta**:
Aquesta línia genera que tots els arxius *.c siguin executables i els guarda al directori BIN. 

**Solució**:

Aquesta línia transforma la llista de fitxers font (SOURCES) en una llista de noms d’objectius dins BIN, amb el mateix nom però sense .c. No converteix directament a executables, sinó que prepara els noms de destí.

##### Ex 6

¿Cuál es la diferencia entre estos dos usos de fflush?

```c
fflush(stdout);    // Caso 1
fflush(NULL);      // Caso 2
```

**Resposta**
En el primer cas, tenim que stdout és un descriptor de fitxer, per tant, si posem stdout simplement estem **netejant** el buffer del descripitor de fitxer, per exemple si un codi imprimis a,b,c després un altre codi no imprimeix res i ultimement un tercer codi on també s'imprimis alguna cosa, si executem els tres codis a la vegada tindrem que hi ha hagut un salt de línia inesperat, per tant la funció de fflush és netejar el buffer.

Altrament, en el segon cas, tenim que simplement s'apunta a una adreça de memòria nula on hi pot haver qualsevol contingut.

**Solució**
fflush(NULL):Buida tots els buffers de sortida de tots els streams oberts

##### Ex 7

Si ejecuto: ./programa arg1 arg2
* ¿Cuánto vale argc?

* ¿Qué contiene argv[0]?

* ¿Qué contiene argv[argc]?

**Respostes**:

2, arg1, [arg1, \n, arg2]

**Solucions**:

Diu que argc = 2 (error: seria 3, perquè sempre compta el nom del programa).

Diu que argv[0] = 'arg1' (error: és "./programa").

Diu que argv[argc] conté [arg1,\n,arg2] (error: és sempre NULL).

##### Ex 8
Explica qué ocurre con la memoria en este proceso:

c
int main() {
    while(1) {
        int *p = malloc(1024);  // 1KB
        // No hay free()
    }
}

La funció malloc assigna 1024 bytes a un punter que apunta a una direcció de memòria, com que no s'allibera l'adreça de memòria, com que és un bucle infinit, s'assignen 1024 bytes a una altra adreça de memòria fins que la memòria no pugui soportar més.

**Solució**:

És correcte :)

##### Ex 9

¿Qué pasa si cierro el descriptor 0 (stdin)?

Doncs que, si es necessita netejar el buffer d'entrada no podrem, ja que hem tancar el descriptor stdin. Ex: En un mateix codi pot passar que volem imprimir:

```c
printf("%c,%c,%c", a, b, c);
```
Però com que el descriptor de fitxer stdin no existeix, pot passar que si b = " " es printeji un salt de línia inesperat.

**Solució**:

Barreges stdin i sortida. Tancar descriptor 0 vol dir que les funcions que intentin llegir d’entrada estàndard fallaran (retornen -1 o EOF). No té res a veure amb printf.

##### Ex 10

En el Makefile, ¿por qué necesitamos .PHONY?

makefile
.PHONY: all clean help

**Resposta**:

Per crear el directori bin si no existeix, si el make tracta aixó com una execució, afegim .PHONY per que no ho faci.

**Solució**:

Dius que .PHONY és “per crear el directori bin si no existeix”. Error: .PHONY indica que una regla no correspon a un fitxer real, així make no confon objectius amb fitxers del mateix nom.

##### Ex 11
¿Cómo gestiona el SO la ilusión de "máquina virtual" para cada proceso en términos de:

Memoria: Fa que les adreçes reals de memòria, és a dir, la unitat de gestió de memòria tinguin les seves adreçes virtuals.

Dispositivos de E/S:Permet als usuaris utilitzar un dispositiu de E/S (hardware) sense conèixer els detalls tècnics d’aquesta impresora.

**Solució**:

Memòria → parles d’adreces virtuals, bé però incomplet.
E/S → correcte, però massa genèric.

##### Ex 12
Si tengo este código, ¿qué descriptor usará el archivo?

c
int main() {
    close(1);  
    int fd = open("output.txt", O_WRONLY);
    printf("¿Dónde va este texto?");
}

**Resposta**:

Utilitzará stdin ja que s'utilitza la instrucció open fa una crida a stdin.

**Solució**:

Dius que utilitzarà stdin. Error: close(1) tanca stdout, i el següent open assignarà el descriptor 1. Per tant, printf enviarà la sortida a output.txt.

##### Ex 13
¿Qué problema soluciona esta regla?

makefile
$(BIN):
    mkdir -p $(BIN)

**Resposta**:

Crea el directori bin si no existeix.

Si cambio un archivo .c, ¿el Makefile recompila solo ese archivo o todos? ¿Por qué?

**Resposta**:

Tots els arxius, ja que la instrcció make vol que es compilin tots els arxius del programa

**Solucions**:

Primera part bé: mkdir -p $(BIN) crea el directori.

Segona part malament: un Makefile ben escrit només recompila els .c modificats (no tots).

##### Ex 14
¿Para qué sirven los flags -Wall -Wextra -O2 en la compilación?

**Resposta**:

Per evitar warnings dins d'un codi,per exemple la comanda -Wall detecta qualsevol incoherencia i O2 vol dir optimització de nivell dos

**Solució**:

Dius que -Wall i -Wextra són per avisos i -O2 optimització. Correcte, però massa superficial:

-Wall: activa molts warnings comuns.

-Wextra: activa advertiments addicionals.

-O2: optimitza velocitat i mida, però sense trencar debugging.

##### Ex15
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    
    printf("Ingresa el tamaño del array: ");
    scanf("%d", &n);
    
    // Completa el código:
    // 1. Asigna memoria dinámica para un array de n enteros
    // 2. Verifica si la asignación fue exitosa
    // 3. Llena el array con valores (pueden ser secuenciales)
    // 4. Imprime el array
    // 5. Libera la memoria asignada
    
    return 0;
}

Resposta:
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
        a = &i;
        i--;

    }

    for(int i = 0; i < n ; i ++)
    {
        printf("L'array %d té el valor %d \n", i , *a);
    }
    free(a);
    return 0;
}

Solució:
```c
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
```

##### Ex16:
```c
#include <stdio.h>
int main() {
    int x = 10;
    int *p = &x;
    int **q = &p;

    **q += 5;
    *p = *p * 2;
    printf("%d\n", x);
}
```
Quin serà el resultat de la execució? Resposta: 30. Totes les variables, x, p, q apunten a la mateixa variable int.

Solució: 30

##### Ex17 

Completa el codi restant:
```c
#include <stdio.h>
int main() {
    char msg[] = "C language";
    char *p = msg;

    // ???? (Mou el punter al final i imprimeix cap enrere)

    return 0;
}
```
Resposta:
```c
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
```
Solució:
```c
#include <stdio.h>
int main() {
    char msg[] = "C language";
    char *p = msg;
    int len;

    for(len = 0; *p != '\0'; len++)
    {
        p++;
    }

    p--;

    for(;len > 0; len--)
    {
        printf("%c",*p);
        p--;
    }

    return 0;
}
```
##### Ex18
```c
#include <stdio.h>
int main() {
    int arr[] = {10, 20, 30, 40};
    int *p = arr;
    *(p + 2) = *p + 5;
    p++;
    printf("%d %d\n", *p, *(p+1));
}
```
Que impremeix?

Resposta: 20 0

Solució: 20 15

##### Ex19
```c
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
```
Que imprimeix?

Resposta: 20 20

Solució: 5 20 

##### Ex20
```c
#include <stdio.h>
int main() {
    int n = 5;
    int *p = &n;
    int **r = &p;

    *p = *p + 3;
    **r = **r - 2;

    printf("%d\n", n);
}
```
Que imprimeix?

Resposta: 6

Solució: 6

##### Ex21

```c
#include <stdio.h>
int main() {
    char *s = "Hola";
    char t[] = "Hola";
    if (s == t)
        printf("Iguals\n");
    else
        printf("Diferents\n");
}
```
Resposta: Diferents, ja que el punter apunta a l'adreça de memòria de h i t és l'array en si.

Solució:Diferents, 
char *s = "Hola";

👉 s és un punter a una constant de cadena que es troba en una zona de memòria de només lectura (normalment del segment text del programa).

char t[] = "Hola";

👉 t és un array local que conté una còpia dels caràcters "Hola" dins de la memòria automàtica (stack).

##### Ex22
```c
#include <stdio.h>
int main() {
    int a[3] = {1,2,3};
    int *p = a;
    printf("%d\n", *p++ + *p);
}
```
Resposta: 3.Ja que, els punters se sumen, en aquest cas apunten a l'array a[1] i a[0], si els sumen tenim a[2].

Solució: p apunta inicialment a a[0].
L’expressió *p++ retorna el valor de a[0] (1) i després incrementa el punter perquè apunti a a[1].
Després, *p és a[1] (2).
La suma és 1 + 2 = 3.

##### Ex23
```c
#include <stdio.h>

int main() {
    int a[4] = {1, 2, 3, 4};
    int *p = a;

    printf("%d\n", *p++ + *p++);
    return 0;
}
```
Resposta: 4

Solució: 3.

Primer *p++:

Usa el valor apuntat actualment (a[0] = 1)

Després incrementa p → ara p apunta a a[1]

Segon *p++:

    Usa el valor actual (a[1] = 2)

    Després incrementa p → ara p apunta a a[2]

    Suma:

    1 + 2 = 3 1 + 2 = 3

Compte perquè també es podria fer :
```c 
printf("%d\n", *p + *p++); 
```

Aquí l’ordre d’avaluació de *p i *p++ és indefinit segons l’estàndard de C (comportament indefinit).
Això vol dir que pot imprimir coses diferents segons el compilador (una trampa de veritat 🧠🔥).

##### Ex24
```c
#include <stdio.h>

struct alumne {
    int id;
    char *nom;
};

int main() {
    struct alumne classe[] = {
        {1, "Marc"}, {2, "Júlia"}, {3, "Pau"}
    };

    // ???? (Usa un punter a struct per recórrer l’array i imprimir)

    return 0;
}
```
Completa el codi.
Resposta:
```c
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
```
Solució:
```c
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

    for (; p < classe + n; p++) {
        printf("%d |%s|\n", p->id, p->nom);
    }

    return 0;
}
```

Explicació:

Aquí classe + n apunta justo al elemento después del último del array.

La sintaxi para imprimir es simplemente p -> id.

##### Ex25
Completa el codi perquè output tingui HELLO
```c
#include <stdio.h>
#include <ctype.h>

int main() {
    char msg[] = "hello";
    char output[6];
    char *src = msg;
    char *dst = output;

    // ????
    printf("%s\n", output);
}
```

Resposta:
```c
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
```
Solució:
```c
#include <stdio.h>
#include <ctype.h>

int main() {
    char msg[] = "hello";
    char output[6];
    char *src = msg;
    char *dst = output;

    while (*src != '\0') {
        *dst = *src;  // Copia el carácter
        src++;
        dst++;
    }
    *dst = '\0'; // Finaliza la cadena

    printf("%s\n", output);
}
```

### Ex26 El pitjor exerici que podries imaginar (faig això després de haver fet el tema3 i el tema 2)

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int ***crear_matriz_locura(int n) {
    int ***triple = malloc(n * sizeof(int**));
    for (int i = 0; i < n; i++) {
        triple[i] = malloc(n * sizeof(int*));
        for (int j = 0; j < n; j++) {
            triple[i][j] = malloc(sizeof(int));
            *triple[i][j] = i * n + j;
        }
    }
    return triple;
}

void modificar_matriz(int ****cuadruple_ptr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*cuadruple_ptr)[i][j] += 100;
        }
    }
}

void funcion_senial(int sig) {
    static int contador = 0;
    int *p = malloc(sizeof(int));
    *p = sig + contador++;
    printf("Señal %d, valor: %d\n", sig, *p);
    // LEAK INTENCIONAL - para confundir más
}

int main() {
    int n = 3;
    int ***matriz = crear_matriz_locura(n);
    
    // Puntero a puntero a puntero a puntero
    int ****ptr_matriz = &matriz;
    
    modificar_matriz(ptr_matriz, n);
    
    // Fork y pipes
    int pipefd[2];
    pipe(pipefd);
    
    pid_t pid = fork();
    
    if (pid == 0) { // Hijo
        close(pipefd[0]); // Cierra lectura
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                write(pipefd[1], matriz[i][j], sizeof(int));
            }
        }
        close(pipefd[1]);
        exit(0);
    } else { // Padre
        close(pipefd[1]); // Cierra escritura
        int *buffer = calloc(n * n, sizeof(int));
        read(pipefd[0], buffer, n * n * sizeof(int));
        
        // Manipulación confusa de punteros
        int *(*func_ptrs[3])(int*) = {NULL, NULL, NULL};
        
        signal(SIGUSR1, funcion_senial);
        kill(pid, SIGUSR1);
        
        wait(NULL);
        
        // Liberar memoria (¿correctamente?)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                free(matriz[i][j]);
            }
            free(matriz[i]);
        }
        free(matriz);
        free(buffer);
    }
    
    return 0;
}



















## Reflexions personals

- Tardo massa en fer els apunts
- Hauria d'expressarme millor
- He millorat bastant en el tema punters i memòria dinàmica.
- Encara així, se'm dona bastant malament combarlos amb struct i tydefs




![alt text](image-5.png)

