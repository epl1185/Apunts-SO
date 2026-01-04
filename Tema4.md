# 🖥️ Apunts de Sistemes Operatius - TEMA 4

## 📋 Índex
- [Setmana 2 - Planificació de processos](#setmana-2--- Planificació de processos)
- [Exemples Pràctics](#exemples-pràctics)
- [Dubtes i Preguntes](#dubtes-i-preguntes)
- [Reflexions Personals](#reflexions-personals)

---

## 🎯 TEMA 4 - Planificació de Processos 

### Conceptes bàsics
Cicles de burst:
![alt text](image-28.png)
Alterna entre períodes d'activtat intensiva d'ús del processador (CPU) i períodes d'activtat d'entrada/sortida (E/S)

Situació 1:
![alt text](image-30.png)

* 1: El SO carrega el procés a memòria principal
* 2: El planificador selecciona el procés
* 3: El despatxa a la CPU
* 4: L'usuari interactua amb l'aplicació.

Execució concurrent:
![alt text](image-31.png)
Definció segons la IA: La ejecución concurrente ocurre cuando múltiples procesos/tareas (APP1 y APP2) comparten el mismo procesador y avanzan en su ejecución de forma aparentemente simultánea, aunque en realidad el procesador va alternando rápidamente entre ellos.

Si s'hagués de posar passos al igual que abans:

* 1: El SO carrega les dues aplicacions a memòria principal
* 2: El planificador decideix quan executar cada app
* 3: El procesador executa fragments de APP1, després d'APP2, després APP1 , ... fins a n
* 4 Canvi ràpid de context: El SO guarda l'estat d'una APP i carrega l'estat de l'altre.
* 5 L'usuari interactua amb les aplicacions.

### Monoprogramat vs Multiprogramació
![alt text](image-32.png)
Monoprogramat: Només un procés a la memòria. APP2 ha d'esperar que APP1 acabi.
![alt text](image-33.png)
Multiprogramat: Múltiples processos a la memòria. APP2 pot ser carregat i executat mentre APP1 està en espera o en execució.

#### Objectius del planificador
![alt text](image-34.png)
* Tenim múltiples processos carregats a memòria principal que competeixen per recursos. Després el planificador ha de seleccioanr quin d'aquests processos s'ha de seleccionar primer tal que cumpleixi aquests tres requeriments(IA):

* 1.Optimización de los recursos ⚙️:
    * El planificador debe maximizar el uso del procesador
    * Evitar que el CPU esté idle (sin hacer nada)
    * Gestionar eficientemente la memoria principal donde residen los procesos
* 2.Equidad entre procesos ⚖️
    * Dar tiempo de CPU a todos los procesos de manera justa
    * Evitar que un proceso monopolice el procesador
    * Balancear la atención entre APP1, APP2, etc.
* 3.Garantizar la ejecución de las tareas ✅
    * Asegurar que todos los procesos avancen
    * Cumplir con los requisitos de cada aplicación
    * Mantener el sistema responsive y funcional
#### Funcionament del planificador.
![alt text](image-36.png)


* Process: representación lógica del programa en ejecución. Tiene pid, priority, state (Ready, Running, Waiting, Terminated), y un puntero al PCB.

* PCB (Process Control Block): estructura que almacena el contexto del proceso (registros, puntero de pila, info de memoria, etc.). Tiene saveContext() y loadContext().

* ReadyQueue: cola de procesos listos para ejecutarse. Operaciones típicas: enqueue, dequeue, sortBy (p. ej. prioridad). Tenim diferents processos que esperen a la cua de preparats.(La cua no és res més que un array de processos LIFO)


* Scheduler (Planificador): lógica que selecciona qué proceso ejecutar (selectProcess()), decide preempción, gestiona interrupciones (handleInterrupt()).

* Dispatcher: módulo que toma la decisión del scheduler y realiza el context switch (usa PCB para loadContext() / saveContext()).

* CPU: ejecuta el proceso actual (executeCycle()), puede generar interrupciones o ser interrumpida.

* IODevice: periférico que atiende peticiones I/O (startIO(process)), devuelve completeIO(eventId) cuando termina.

* Interrupción: eventos (TIMER, IO_COMPLETION, SYSCALL, ERROR) que despiertan al scheduler o provocan acciones inmediatas.
Planificació: algorisme que selecciona una d'entre un conjunt de tasques d'una llista. Poden haver-hi diferents planificadors en un sistema, planificador de la CPU ( més important) i dels diferents dispositius d'E/S.

##### Quan s’ha de planificar (Estats dels processos) ?
![](image-37.png)

* Paso 1: Proceso en Ejecución → Evento Ocurre:El proceso running encuentra un evento:
```c
if evento == "Petició E/S":
    va_a_estado_waiting()
elif evento == "Expiració del temps":
    va_a_estado_ready()
elif evento == "Finalització":
    proceso_termina()
```
* Paso 2: El Planificador Decide:
CPU queda libre → Planificador elige próximo proceso de "Cua de Preparats"
* Paso 3: Despacho (Dispatch)
"Procés Despatxat" = Proceso seleccionado pasa de Ready → Running
* Paso 4: Nueva Ejecución
text: Proceso elegido ocupa el CPU y ejecuta

### Apropació.

![alt text](image-38.png)

El SO decideix cuantes unitats de temps ha d'estar cada procés al planificador. Com a consqüencia hi ha més canvis de context. Si tenim major cost d'apropiació, impliquen més interrupcions periodiques. Afavorim a que els procés amb més prioritat tinguin més justicía i equitat.

### Criteri / Algorismes de planificació (Generals)

* Justícia: Accés equitatiu als recursos per a tots els processos.
* Equilibri: Totes les parts del sistema estiguin utilitzades.
* Priorització: Preferència a processos amb més urgència.

És impossible tenir els tres a la vegada, ho associo amb aquesta imatge:
![alt text](image-39.png)

### Criteris a l'hora d'escoliir un algorisme

* Utilització de la CPU: % de temps d’ocupació.
* Productivitat: Nº de processos completats per unitat de temps.
* Temps de retorn: Temps total des que un procés s’envia fins que es completa, incloent temps d’espera i execució.
![alt text](image-40.png)
* Temps d’espera: Temps que un procés roman a la cua de preparats.
* Temps de resposta: Temps entre una sol·licitud de l’usuari i la primera resposta

### Criteris de planificació (Temps real)
* Predictibilitat: Capacitat del sistema per complir els requisits temporals de manera sistemàtica.
* Deadline: Capacitat de garantir que els processos finalitzin abans d’un temps límit establert.

### Objectius dels criteris de planificació

* Minimitzar el temps de resposta 
* Maximitzar el rendiment
* Justícia ( Compartir la CPU entre els usuaris de manera equitativa)
* Planificació òptima

### Algorismes de planificaió. Definicions

* FIFO (First In First Out): el primer procés en entrar (en la cua de preparats) serà també el primer procés en ser despatxat. Sol utilitzar-se en sistemes tipus batch. 

* SJF (Shortest Job First): el procés més curt (en temps de CPU) primer. Algorisme òptim. No es pot implementar perquè a priori no es sap el temps de CPU que requerirà un procés. Suposeu per exemple que prenem com índex de rendiment el Temps mig de Retorn d’un conjunt de processos. El temps de retorn total (suma dels temps de retorn de cada procés) és el més petit possible (òptim). Això és així perquè l’ordre d’execució dels processos es realitza segons el temps d’execució que necessiten (com més/menys temps requereixi un procés, més tard/aviat s’executarà). Com que el temps de retorn de cada procés és l’òptim, també ho serà la seva mitja. 

* SRTF: Versió apropiativa de SJF.

* Prioritats: el procés amb més prioritat primer.

* Round-Robin: els processos s’executen durant un Quàntum: temps màxim d’execu- ció ininterrompuda dins de la CPU. Després abandonen la CPU i s’insereixen al ﬁnal de la cua de preparats (que suposarem FIFO). Serveix per implementar sistemes de temps compartit 

* Cues Multinivell sense retroalimentació: 

![alt text](image.png)
La cua de preparats es composa de diferents cues, on cadascuna de les quals pot implementar un algorisme de planiﬁcació independent de la resta. Cada procés està assignat a una cua segons la seva prioritat. Primer es tria un procés (si és que n’hi ha algun) de la cua més prioritària (segons l’algoris- me de planiﬁcació associat), a continuació es continua per la cua amb prioritat immediatament inferior, i així successivament ﬁns la cua menys prioritària.

* Cues Multinivell amb retroalimentació:  cues multinivell on els processos poden moure’s entre cues. Estan pensades per evitar que els processos (de les cues menys prioritàries) entrin en inanició segons els criteris següents:   
    
    • Quan un procés ha estat despatxat un determinat nombre de cops dins de la CPU, es mou a una cua menys prioritària.

    • Quan un procés ha estat en inanició un determinat temps, es mou a una cua més prioritària.

### Caracteristiques dels algorismes de Planifiació

* FIFO (First In First Out):

    * Simplicitat: Algorisme senzill d’implementar i comprendre.

    * No apropiatiu: Un procés s’executa fins a la seva finalització o bloqueig.

    * Garantia de no inanició: Tots els processos eventualment s’executen (sota la suposició que acaben).

    * Efecte Convoy: Processos curts poden quedar bloquejats per processos llargs, incrementant el temps d’espera mitjà.
* SJF (Shortest Job First)
    * Pot provocar inanició? Sí, qualsevol política que prioritzi una propietat pot provocar inanició.
    * Pot provocar convoy? Sí, qualsevol política no apropiativa pot provocar convoy.
    * Redueix el temps de retorn? Sí, redueix el temps mitjà de finalització si i només si tots els processos arriben alhora.
    * Requereix coneixement previ del temps de burst? Sí, és un dels seus inconvenients principals.

* SRTF
    * SRTF (Shortest Remaining Time First) és una política òptima pel temps de resposta mitjà.
    * Cap altra política pot superar SRTF en aquest criteri.    
    * Es fa servir sovint com a referència de comparació amb altres algorismes.

* Prioritats
    * En cas d’empat, es pot aplicar un altre algorisme (habitualment FIFO).
    * Les prioritats poden ser estàtiques o dinàmiques.
    * L’envelliment és una estratègia utilitzada per abordar el problema d’inanició que pot sorgir en els algorismes de planificació basats en prioritats.

* Round-Robin

    * Cada procés rep un quantum de temps per executar-se.
    * Quan el quantum expira, el procés és interromput i col·locat al final de la cua de preparats.
    * Cap procés pot monopolitzar la CPU durant un temps determinant (q).
    * Utilitza una cua FIFO per gestionar els processos preparats.
    * Utilitza una interrupció de rellotge per implementar el quantum de temps.
    * És un algorisme apropiatiu.
    * A UNIX, per exemple, s’utilitzen diferents quantums per a processos d’usuari i del sistema per equilibrar la resposta i l’eficiència 
    q=100ms per a processos d’usuari.
    q=10ms  per a processos del sistema.
    El overhead del canvi de context és d’aproximadament 0.1ms−1ms
    Aquest valor és petit comparat amb la durada del quantum, però rellevant si els quantum són molt petits.

* Cues Multinivell sense retroalimentació

* Cues Multinivell amb retroalimentació
    * Quantum de Temps Variable: Cada cua de prioritat té un quantum de temps específic i progressivament més llarg en cues de menor prioritat, optimitzant així la gestió de processos de llarga durada.

    * Exemple: Cues Round Robin amb quantums exponencials (1ms, 2ms, 4ms, etc.) per a processos de llarga durada.

    * Moviment Dinàmic entre Cues: Si un procés no finalitza dins del seu quantum assignat, es mou a una cua amb menor prioritat, on rebrà un quantum més llarg però menor prioritat d’execució.

    * Exemple: Els processos amb alta demanda de CPU descendeixen ràpidament de prioritat, evitant que monopolitzin la CPU. Els processos de curta durada i/o intensius en E/S mantenen la prioritat alta, maximitzant el seu accés a la CPU i reduint la latència.

    * Estructura Flexible de Cues: Les cues amb retroalimentació permeten que els processos amb canvis de comportament puguin ajustar la seva posició.

    * Temps de CPU per Cua: Cada cua rep un percentatge del temps de CPU: P. ex., cues interactives reben un percentatge més alt per a reduir el temps de resposta.

    * Inversió de prioritats: Mantenir el programa en una cua de major prioritat per garantir temps de CPU preferent i una resposta ràpida en les decisions del joc.

### Predir el futur?
Sabem que el SRTF seria el millor algorisme de planificació si poguessim conéixer el futur. Però com el pordem predir? I seria de manera exacta?

La resposta es que sí, i es que podem mirar el comportament que ha tingut un procés en el passar per poder predir com es comptará en el futur, per exemple, un editor de text pasa molt de temps esperant a que es premi una tecla E/S, i només utilitza la CPU si s'escriu.

Una estratègia comuna és utilitzar estimacions basades en l'historial de comportament dels processos. Molts programes mostren patrons repetitius en la seva utilització de la CPU i I/O. Si els processos tenen un comportament aleatori, aquesta estratègia no seria útil.
Així podem introduir la següent fórmula:

$t_n = f(t_{n-1}, t_{n-2}, t_{n-3}, \ldots)$

* On: $t_n$ és la durada estimada del següent burst de CPU. $f$ és una funció que utilitza els bursts anteriors per fer la predicció.
* $t_{n-1}, t_{n-2}$ son les duracions reals dels bursts anteriors
* $f$ es una funció de predicció









## Exemples pràctics.

### Analisi d'exerici de FIFO (CLASSE)
|  proc  | $t_a$ | $t_{cpu}$ |
|:---------:|:---------:|:-------------:|
| 🟢 **P1** |     0     |      20       |
| 🔵 **P2** |     5     |       5       |
| 🟣 **P3** |     6     |       5       |

1.  **Efecte Convoy:** El procés P1 (llarg) bloqueja els processos P2 i P3 (curts), incrementant el temps d'espera.
2.  **Sensible a l'ordre arribada:** Si P2 o P3 hagués arribat abans que P1, el temps d'espera de P2 hauria estat menor.
3.  **No apropiatiu:** P1 ocupa la CPU fins a la seva finalització, sense donar oportunitat a P2 i P3.
4.  **No és adequat per a sistemes interactius o en temps real:** Els usuaris poden experimentar retards significatius en la resposta del sistema, ja que els processos curts poden quedar bloquejats darrere de processos llargs.

## RR - Diagrama de flux

(Exercicis Resolts del llibre de Lleida)
Enunciat: Donats els processos amb les característiques de la taula 3.1 .
Doneu el diagrama de gantt i el temps mig de retorn i d’espera pels algorismes a curt plaç següents: 
* 1.FIFO
* 2.SJF 
* 3.Prioritats. Valors més alts indiquen prioritats també més altes.
* 4.Round-Robin. Quàntum = 3.


## Dubtes i Preguntes

## Reflexions personals