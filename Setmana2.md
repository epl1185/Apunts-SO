# 🖥️ Apunts de Sistemes Operatius - TEMA 2

## 📋 Índex
- [Setmana 2 - Kernel de Linux i Crides a Sistema](#setmana-2---Kernel de Linux i Crides a Sistema)
- [Exemples Pràctics](#exemples-pràctics)
- [Dubtes i Preguntes](#dubtes-i-preguntes)
- [Reflexions Personals](#reflexions-personals)

---

## 🎯 TEMA 2 - Kernel de Linux i Crides a Sistema

### 🔍 Dualitat

![alt text](image-3.png)
En aquesta imatge se'ns ensenya la dualitat entre usuari i kernel. Primerament, l'usuari disposa d'uns certs permissos que el kernel no té, per exemple l'accès a la shell o al navegador.
Per una altra part el kernel és el que gestiona la part de alt nivell i la que dosifica la memòria virtual.

### Estructures de kernels.

Li he demanat a la IA que em relacionai la teoria amb gossos( soc molt dolent d'enrecordarme de la teoria). Així que aquest exemple m'anirà bé.

##### Estructura Simple:
![alt text](image-4.png)

🏢 Kernel Simple - Perro "Viejo"

Ha perdut facultats, per tant, no está ben definit.

Podem dir-li al gos que faci totes les tasques sense limitació, però és díficil fer-li aprendre una nova comanda, está saturat.

És díficil saber que li passa en certs moments (depuració)


##### Estructura Monolítica:
![alt text](image-5.png)

🏢 Kernel Monolítico - Perro Guardián Grande

* Todo en uno: Como un Gran Danés que hace guardia, ataca, protege

* Linux: Todos los controladores en el kernel

* Ventaja: Rápido (comunicación directa)

* Desventaja: Si falla un driver (componente de software que permite que el sistema operativo y un dispositivo se comuniquen) → todo el sistema cae

Que extrec? 

* És un gran programa amb molts mòduls (controladors, gestió de memoria, etc) que es comuniquen entre si directament dintre del nucli del kernel.

    Avantatges:
 * Molt ràpid (tot està en el mateix espai de memòria).

-Desventatges:
* Si un mòdul falla, pot afectar a tot el sistema; difícil d'actualizar o separar errors.


##### Estructura Per Capes:
![alt text](image-6.png)

🥞 Kernel por Capas - Perro con Arnés

* Capas como un arnés: Cada capa solo habla con la de arriba/abajo

* Teoría bonita, poco usada en práctica

* Como ponerle arnés, correa, bozal al perro

Qué s'extreu?

* Divideix el sistema operatiu en nivells jeràrquics, on cada capa només pot comunicarse amb la de dalt o la de sota.

* Aventatges: Més ordenat, fàcil de depurar i mantenir.

* Desaventatges: Menor rendimient por el temps de comunicació entre capes.


##### Estructura MicroKernel:

🧩 Microkernel - Perro Pequeño + Adiestrador

* Kernel mínimo: Solo lo esencial (como un Chihuahua)

* Servicios separados: Drivers como procesos separados

* Ventaja: Si falla un driver, solo se reinicia ese proceso

* Ejemplo: QNX, Minix

Extracció

* Manté al nucli només les funcions essencials (comunicació, planificació, interrupcions). Tota la resta (arxius, drivers, etc.) s'executen com a processos d'usuari.

* Aventatges: Molt modular, més segur i estable (els errors en serveis no afecten el nucli).

* Desaventatges: Més lent per la comunicació entre processos (més “missatgeria”).

##### Estructura híbrida
Combinen elements de nuclis monolítics i microkernel.

Pel que fa a tot això del 'nucli híbrid', només és màrqueting. És oh, aquests micronuclis tenien una bona relació qualitat-preu, com podem intentar obtenir una bona relació qualitat-preu per al nostre nucli funcional? Ah, ja ho sé, fem servir un nom interessant i intentem insinuar que té tots els avantatges de relació qualitat-preu que té aquest altre sistema'» - Linus Torvalds

### Kernel Modular

“Modular” quiere decir que el cervell està fet de peces que es poden posar o deixar sense tenir que canviar tot el sistema.
Cada mòdul és com un petit bloc que fa una tasca concreta:

Un mòdul per al rató 🖱️

Otro per al so 🔊

Otro para la red 🌐

### Pralab7 Espiant el kernel

**Strace és una eina que permet monitoritzar i fer un seguiment de les crides al sistema que realitza un programa.**

Quines crides a sistema utilitza el procés?

Quins fitxers esta utilitzant l’aplicació?

Quins arguments es passen a les crides a sistema?

Quines crides a sistema estan fallant, i per què?

Fem **strace cat /dev/null** per veure la seva sortida i analitzar-la.

Després intentaré deduir la seva sortida, es á dir, el perqué aquest exemple mostra totes les crides a sistema realitzades pel programa cat.

 * Strace mostra totes les crides a sistema que executa un programa
 * Cat  /dev/null, la comanda cat (per xemple si fessim cat a.txt), ens mostraria el seu contingut per terminal, per es fan dues operacions, una de lectura al fitxer i una d'escriptura a la terminal. Però l'arxiu /dev/null no sé que significa, per tant li he preguntat a la IA. 
* /dev/ es un directorio especial en Linux que contiene archivos de dispositivo. Estos no son archivos normales, sino interfaces hacia dispositivos del sistema.??
* Directament se m'ha dit /dev/null → Es un dispositivo que siempre devuelve EOF 
* Per té sentit que es mostrin totes les crides a sistema realitzades pel programa cat.

**strace -e trace=close cat /dev/null**

En aquest cas, només veurem les crides close que fa el programa cat.

Perquè? Respecte a la comanda anterior el que ha canviat és que hem afegit la opció -e, fent strace -h , trobem que -e fa una mena de "Tampering", finalemnt si fem trace = close, només mostrarem les crides que fa close:

**strace -e trace=/get* ls**

Mostra totes les crides que comencin per get que fa el programa ls.

**strace -o strace.log -e trace=open,close ls**

Escriu en el fitxer strace.log totes les crides a sistema que siguin open o close.

Exlcoure una crida a sistema en particular:

**strace -o strace.log -e trace!=gettimeofday ls** 

Excloure una crida a sistema en particular, com gettimeofday.

**strace -o strace.log -e trace=%{X} ls.**

On {X} representa la categoria que t’interessa.

### Crides a sistema

Concepte: És un telefon intern que els programes utilitzen per a demanar serveis al SO.

![alt text](image-13.png)

En aquesta imatge podem veure la portecció de la CPU(unitat central de processament) en múltiples nivells de seguretat.

En el Ring 0, desde el punt de vista del Kernel podem dir que  el ring 0 és on té més llibertat i l'anell 3 és on es troben els serveis de l'usuari, per exemple on es troben els meus programes.

Per tant, té sentit que el kernel s'executi en mode priveligiat (ring 0) amb accés complet al maquinari. Els serveis del mode usuari demanen permís al kernel. Aquests s'executen en l'anell 3 que és el més restringit, de manera segura.

Com pot un procés en mode usuari notificar al kernel que necessita fer alguna cosa? Si no tenim cap instrucció que ho permeti?

"Com pot un procés, que està tancat en una presó (mode usuari), demanar ajuda al guarda (kernel) si no li està permès obrir la porta?"

Resposta: No pot obrir la porta... però pot fer soroll fins que el guarda vingui a veure què passa.

A partir d'aquesta pregunta podem deduir el concepte d'interrupció.

### FUNCIONAMENT DEL PROCESSADOR

Tenim la següent tabla dins del funcionament de la ram:

| Adreça| Opcode | Operand |
|------------|------------|------------|
| 0 | Fila 1, C2 | Fila 1, C3 |
| 1 | Fila 2, C2 | Fila 2, C3 |

| Adreça| Valor|
------------|------------|
|30| Fila 1, C2 | Fila 1, C3 |
| 31 | Fila 2, C2 | Fila 2, C3 |

Que és cada cosa?

* Adreça : Adreçes de memòria dins de la RAM

* Opcode, operand : Instruccions en sí que la CPU vol fer. Per altra part. l'operand és la direcció de memòria. (Do this ---> to this)

* Valors: Valors amb els que la CPU pot treballar

Suposem que tenim el següent programa a executar 
```c

int main(int argc, char * argv[])
int a = atoi(argv[1]);
int b = atoi(argv[2]);

return a + b;
```
Suposant que l'usuari ha passat com a paramètres el 5 i el 7, tenim, dins de la segona taula:

| Adreça| Valor|
------------|------------|
|30| 5| 
| 31 | 7|

Dins de la primera taula, tenim( hi ha instrccions que m'enrecordo de EDC II), la relació entre aquestes dos taules s'anomena **pipelining**:

| Adreça| Opcode | Operand |
|------------|------------|------------|
| 0 | LOAD | 30 |
| 1 | ADD | 31|
| 2 | STORE | 32|

La CPU té un rellotge intern, un tick d'aquest, señala el començaent d'un nou fetch.

Es pot dir que es segueix el següent procés:

Fetch → Decode → Execute → Memory → Writeback.

### Interrupcions

Tenim que un dispostiu de E/S com podria ser un teclat, té menys velocitat que la CPU o la RAM. 

Tipus d'interrupció:

Hardware:

* Polling: Esperem fins que el dispositiu no estigui ocupat. Si no està ocupat, fem una operació E/S

* Hardware: Prenem una tecla del teclat (ctrl c) a la terminal. (Es fa un sleep i desprésuna subrutina)

Software:

* Int 0, 6, 7.Senyals que s'han fet a teoria.

### Taules d'interrupció

![alt text](image-14.png).

És una estructura de dades que asocia una llista de drivers d'interrupcions. Cadascuna de les entrades en la taula de vectors d'interrupcions, és la direcció d'un driver d'interrupció.

Si rebo una instrucció serà el propi kernel el que em dirà quina adreça apunta la ISR corresponent. 

Per tant, té sentit que la CPU no sapigui quin codi executis si es produis això. 

```c
static __init void
idt_setup_from_table(gate_desc *idt, const struct idt_data *t, int size, bool sys)
{
	gate_desc desc;

	for (; size > 0; t++, size--) {
		idt_init_desc(&desc, t);
		write_idt_entry(idt, t->vector, &desc);
		if (sys)
			set_bit(t->vector, system_vectors);
	}
}
```
### Excepcions

Concepte: Evento que se produce cuando se ejecuta el programa de forma que interrumpe el flujo normal de instrucciones.

Hi ha més tipus d'excepcions però prefereixo tractar-ho als exercicis.

### Trap
Intentaré, amb les meves paraules, explicar com s'origina el concepte de trap a partir d'aquesta imatge.
![alt text](image-15.png)
En aquesta imatge podem veure la dualitat entre el mode usuari i el mode kernel. Tenint el mode usuari, qualsevol programa que generi una excepció o una interrupció. Llavors les ha de tractar el kernel. Per això s'origina el concepte de trap que és la interrupció software que li demana permís al kernel.
El kernel accepta la trap, gestiona la interrupció o la excepció i torna a mode usuari.

Es pot explicar amb la següent imatge:
![alt text](image-16.png)

En aquest cas, tenim que en l'espai d'usuari s'ha escrit en programa en C amb la funció int open(const char * ruta , int oflag , ...); tal que cridi al kernel mitjançant una syscall (trap en el kernel). La CPU canvia a mode supervisor i salta a la rutina del kernel indicada a la IDT. En l'espai del Kernel, es comproven els descriptors i els permissos. I s'executa la rutina de tractament de open() llegint les dades del dispositiu E/S. Es retorna un nombre positiu o -1 en cas d'error.El mode kernel torna a l'espai usuari i retorna el valor.
```c
//Executem a user space
mov edx,4;// message length
mov ecx,msg;//message to write
mov ebx,1;//file descriptor (stdout)
mov eax,4;//system call number (sys_write)
int 0x80;//interrupt! Number 128 (0x80 in hex)
```

### Punters i seguretat (I)





### MECANISMES D'EXECUCIÓ

Flux d'una syscall:

Preparació: Programa posa arguments en registres

Trap: Instrucció syscall/int 0x80 (interrupció software)

Canvi a mode kernel: CPU salta a rutina del kernel via IDT

Execució: Kernel valida i executa la funció corresponent

Retorn: Resultat torna via registres + torna a mode usuari.

## Exemples pràctics
### P1 Un kernel pot desactivar les interrupcions en algún moment? Perquè?

Sí. Perquè en el moment que es tracti una interrupció durant la rutina d'aquesta podria ser interrumpuda per una latra interrupció i així creant un bucle infinit. Per tant, necessitem l'acció del kernel en algún moment.

### P2.En aquesta imatge, quines diferencies observes entre el microkernel i el monólitic?

![alt text](image-7.png)

En aquesta imatge podem veure com en la estructura microkernel,té dins de l'espai de l'usuari tant L'unix/Linux com els drivers, és a dir, un component de software que permet que tot el SO i el dispositiu se comuniquen, el kernel té accés a la memòria virtual i demés coses que l'usuari no pot.Per això, podem dir que el microkernel té una mida més reduida. Per una altra part, podem veure que en el kernel monolític, és simplement tot en un, és a dir, que no hi ha un espai d'usuari a part de l'apliació, és a dir, tant les crides a sistema, el sistema de fitxers, ..., fins al driver són espai del Kernel. Però tenim que la comuniació és més rápida en el kernel monolític que en el microkernel.

#### Correccions:

En el monolític SÍ hi ha espai d'usuari per a les aplicacions:

Has dit: "en el kernel monolític, és simplement tot en un, és a dir, que no hi ha un espai d'usuari a part de l'aplicació". Això no és del tot exacte.

Correcció: En un sistema monolític, les aplicacions sí que s'executen en espai d'usuari, però els serveis del sistema operatiu (com drivers, sistema de fitxers, etc.) estan integrades dins del nucli. És a dir, la separació entre "espai de nucli" i "espai d'usuari" segueix existint, però els components del SO estan tots al nucli. La imatge ho reflecteix: veiem "Application" fora del nucli, i la resta dins.

Has assenyalat que la comunicació és més ràpida en el monolític, però és important especificar per què.

Matís: En el microkernel, la comunicació entre serveis (ex: entre una aplicació i el servidor de fitxers) requereix passos de missatgeria a través del nucli, el qual implica canvis de context (canvi d'espai d'usuari a nucli i viceversa). Això afeggeix overhead. En canvi, en el monolític, la comunicació es fa mitjançant simples crides a funcions dins del mateix espai de memòria del nucli.

### P3. Preguntes d'exàmen.

Cert o fals.

**"L’arquitectura monolítica integra totes les funcionalitats de sistema, inclosos serveis i controladors, en un espai d’adreçament compartit."**

Resposta:Cert. (M'he fixat en la iamtge dels meus apunts però no sé com explicar-ho).

Perquè és cert?

En un kernel monolítico, todos los servicios del sistema operativo (gestión de memoria, planificación, sistema de archivos, controladores de dispositivos, etc.) se ejecutan en el mismo espacio de direcciones del kernel. Esto implica que no hay separación entre módulos y el kernel opera como un único programa en modo privilegiado.

**"Els sistemes de microkernel ofereixen generalment un rendiment més elevat que els sistemes monolítics perquè distribueixen els serveis en espai d’usuari."**

Resposta:Fals, s'ha justificat en l'exercici anterior tot just.

**"Un Microkernel pot millorar la resiliència d’un sistema contra errors en el sistema operatiu."**

Resposta: Cert. Perquè, perque abans en la teoria hem dit, si falla driver, només es reinicia aquell procés, per tant, només  es afectat per aquell driver i es pot detectar l'error facilment. Així millorant la resiliència. (Bona paraula la veritat sigui dita)


Fetes per IA:

**"L'adopció de mòduls carregables en temps d'execució en nuclis moderns com Linux invalida la classificació clàssica de 'monolític', transformant-lo de facto en una arquitectura de micronucli, ja que la funcionalitat no essencial resideix en espais de memòria separats i pot ser manejada de manera independent."**

Fals

**"La capacitat dels nuclis moderns com Linux de carregar mòduls dinàmicament (com drivers) els converteix en micronuclis, ja que aquests mòduls es poden carregar i descarregar sense reiniciar el sistema."**

Fals, abans hem justificat que Linux es una estructura monolítica. De fet el que diu l'enunciat és uan característica de l'estructura monolítica.

**"Un micronucli sempre serà més lent que un nucli monolític perquè la comunicació entre serveis passa obligatòriament pel nucli, afegint una sobrecarga de canvis de context."**

Cert

**"Els nuclis híbrids, com Windows NT o XNU (macOS), són en realitat micronuclis purs als quals s'hi han afegit algunes optimitzacions de rendiment, sense incorporar característiques dels nuclis monolítics."**

Fals, sí que incorporen elements dels nuclis monolitics per definció d'estructura híbrida.

**"En una arquitectura monolítica, si un controlador de dispositiu (driver) falla, el sistema operatiu sencer es bloquejarà i es reiniciarà obligatòriament, ja que tot s'executa en el mateix espai.**

Cert, hem dit que si Si un mòdul falla, pot afectar a tot el sistema.

**"En un micronucli, si el servidor del sistema de fitxers falla, les aplicacions que no estiguin accedint a disc en aquell moment no es veuran afectades en absolut."**

Cert, entenc que en el micronucli cada cosa va per separat.

LES HE ENCERTAT TOTES :))

### P4 Digues que fa aquest codi en relació a les syscalls.
```c
__visible noinstr bool do_syscall_64(struct pt_regs *regs, int nr)
{
    nr = syscall_enter_from_user_mode(regs, nr); 
    if (!do_syscall_x64(regs, nr) && !do_syscall_x32(regs, nr) && nr != -1) {
        regs->ax = __x64_sys_ni_syscall(regs);
    }
    syscall_exit_to_user_mode(regs);
    return true;

	/* syscall_enter_from_user_mode(regs, nr)
Canvia a mode kernel.
Realitza validacions de seguretat i prepara els registres (RAX, RDI, RSI, etc.).
*/
/*
syscall_exit_to_user_mode(regs)
Prepara els registres per tornar a mode usuari.
*/
}
```
Podem veure que en aquesta funció és passen dos arguments d'entrada, un que és una classe de punter cap als registes i un enter que indica el mode en el qual s'accedeix a ells.
Després es canvia a mode kernel tal com diuen els comentaris, es retorna un enter que hauria d'indicar el mode de lectura. En el cas que no es pugui fer la syscall ni el RAX ni en el EAX ni tampoc tinguem permissos de lectura o escriptura. La propietat ax dels registres es inicialitzada a uns nous registres. Finalment tornem a mode usuari i com que s'ha fet bé la crida retornem true.

Correccions per part de la IA:


❌ Lo que necesita corrección:
"un enter que indica el mode en el qual s'accedeix a ells"

❌ Incorrecto: nr no es un "modo de acceso" - es el número de syscall que el usuario quiere ejecutar (ej: 1 = exit, 2 = fork, 3 = read, etc.)

"es retorna un enter que hauria d'indicar el mode de lectura"

❌ Incorrecto: syscall_enter_from_user_mode() retorna un número de syscall posiblemente modificado, no un "modo de lectura".

"En el caso que no es pugui fer la syscall ni el RAX ni en el EAX"

❌ Confuso: RAX y EAX son el mismo registro (RAX en 64-bit, EAX en 32-bit). No se trata de "no poder hacerla en RAX ni EAX".

"ni tampoc tinguem permissos de lectura o escriptura"

❌ Parcialmente correcto: La condición verifica si la syscall no existe o no está implementada, no específicamente permisos.

"La propietat ax dels registres es inicialitzada a uns nous registres"

❌ Incorrecto: regs->ax = __x64_sys_ni_syscall(regs) establece el registro AX (donde va el valor de retorno) a lo que retorne la función "not implemented", no a "nuevos registros".




## Dubtes i Preguntes
Que és el directori /dev/? Perquè amb l'expliació de la IA no ho acabo d'entendre.

## Reflexions personals
- Treballar més perquè sino no arribaré a cobrir el temari.

![alt text](image-12.png)