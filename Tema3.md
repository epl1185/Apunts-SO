# 🖥️ Apunts de Sistemes Operatius - TEMA 3

## 📋 Índex
- [Setmana 2 - Kernel de Linux i Crides a Sistema](#setmana-2---Kernel de Linux i Crides a Sistema)
- [Exemples Pràctics](#exemples-pràctics)
- [Dubtes i Preguntes](#dubtes-i-preguntes)
- [Reflexions Personals](#reflexions-personals)

---

## 🎯 TEMA 3 - Processos / Creació de Processos / Senyals / Comunicació entre Processos / Pipes

### 🔍 Processos
Concepte:
És un progama que s'està executant.

Exemple:

Fem $ gedit &$ a la terminal de Linux, el So crea un nou procés per l'usuari que ha executat la comanda. El SO li assigna la mem`roia al procés on hi copia la imatge del programa executable (en /bin/gedit), i una nova estructura de dades, el PCB.

#### Comanda: Ps 
Ens permet veure tots els processos de l'usuari en la terminal actual.

Ps -e per veure tots els del sistema. El procés ps en si també és un procés.

Tots els processos tenen un PID, cada PID és unic, poden estar assignats o no a la terminal, i tenen temps de procediment.El kernel s'encarrega de comprovar si el pid ja pertany a una tasca.

Ps -l mostra més informació sobre la llista de procesos.

### Estats dels processos
<img width="626" height="362" alt="image" src="https://github.com/user-attachments/assets/8a28bf06-a59e-4420-be50-b3f7120bd9c6" />

* NOU: En aquest estat, els processos no tenen PCB. Quan el SO crea un nou procés, li assigna Memòria i un nou PCB, emmagatzemant-hi la informació com podrien ser punters, registres , pids...
El PCB s'insereix en la cua de preparats.
* PREPARAT: els processos en aquest estat tenen tos els recursos que necessiten per la seva execució expecte la CPU.Normalemnt, tots els processos que acaben de ser creats passen per aquest estat.
* INACTIU: Quan un procés acaba l'execució, s'allibera la Memòria i els recursos que tenia assignats. Després s'esborra el seu PCB.
* EXECUCIÓ: El procés té tots els recursos necessaris per la seva execució incloent-hi la CPU. 
* ESPERA: En aquests estat, als processos els hi manca algun recurs a més de la CPU, com pot ser una senyal de sincronització o una operació d'E/S.

PROCESS STATE CODES:
* S (Sleeping) Espera
* R (Runnable) Execució o preparat
* Z (Zombi). Procés que no ha acabat bé. Ha acabat però no s'ha acabat d'esborrar la seva imatge de memòria.(el pare acaba abans que el fill)
* T (sTopped) Parat, per un senyal o perquè està sent tracejat.

### Arbre de processos

* Tots els processos tenen un procés pare, excepte el procés inicial (PID = 1).
* En l’exemple anterior, podeu veure que el procés bash és el pare dels processos sleep i ps. Si esteu connectats per ssh al servidor, el procés bash és fill del procés sshd. I el procés sshd és fill del procés init (PID = 1).
* El kernel és responsable de carregar i iniciar el sistema operatiu.

### Diagrama de transició d'estats

<img width="802" height="611" alt="image" src="https://github.com/user-attachments/assets/0983924b-900a-47e6-a782-c5e7e1ae6dca" />





## Exemples pràctics

### P1 Expliques que fa la següent imatge en relació als estats dels processos

<img width="563" height="137" alt="image" src="https://github.com/user-attachments/assets/41ae497e-64b9-4375-aad5-02b4d8eacacc" />





