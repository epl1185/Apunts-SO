# 🖥️ Apunts de Sistemes Operatius - Setmana 1

## 📋 Índex
- [Setmana 1 - Introducció](#setmana-1---introducció)
- [Exemples Pràctics](#exemples-pràctics)
- [Dubtes i Preguntes](#dubtes-i-preguntes)
- [Reflexions Personals](#reflexions-personals)

---

## 🎯 Setmana 1 - Introducció

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

## Fitxers

Posaré , directament una interprteació de la teoria.  
![alt text](image-2.png)
---


**Pregunta**:En quin descriptor de fitxer aniría el fitxer file.txt?

**Resposta**:Com que els descriptors de fitxers: 0, 1, 2 dins d'una adreça qualsevol de memòria estan preassigantas, especificament, el descriptor 0 está assignat a stdin, 1 a stdout i el 2 a stderr. Per tant, es crearia un descriptor de fitxer número 3 on hi hauria el fitxer file.txt i successivament pels següents fitxers.

(Pendent de corregir)

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
 On dins dels codi trobem:
 * Linies 1 - 3: Declaració de llibreries:

    * #include < sys/types.h> 
    * #include < sys/stat.h> 
    * #include < fcntl.h> 

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

Encara falta acabar més teoria.




## Exemples pràctics

M’he creat aquests exercicis amb IA. La idea és **deduir què fa cada programa pas a pas** i relacionar-ho amb la teoria vista a classe. (Com estic repassant el tema 1 en la setmana 3, m'he doant la llibertat de posar conceptes encara no vistos)

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





