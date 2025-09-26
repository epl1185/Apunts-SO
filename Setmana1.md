# 🖥️ Apunts de Sistemes Operatius - Setmanes 1-3

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

---

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
Sé que en el primer print, si fos un simple %p, llavors s'imprimiria la adreça de memoria de p, però amb el void dedueixo que es vol entrar dins del contingut de la adreça del punter, pero al posar %p, simplement s'impremeix l'adreça de memòria.
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
En l'opció b se'ns dona una compilació amb | cat , sabem que la instrucció cat concatena i mostra un arxiu. Després dedueixo que | deu ser algún tipus de , dirigeixte aquí per concatenarte, per tant seria 01234
En l'opció c se'ns dona una compilació on amb la fletxa es redirigeix al fitxer out.txt, per tant s'escriurà 01234 dins del fietxer out.txt 

Solució:

a line 0 line 1 line 2 line 3 line 4

b line 0 line 1 line 2 line 3 line 4  (Literalment el mateix)

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

Raonament per a arribar a la solució:





