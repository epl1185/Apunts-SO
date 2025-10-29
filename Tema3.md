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

### Estats dels processos
<img width="626" height="362" alt="image" src="https://github.com/user-attachments/assets/8a28bf06-a59e-4420-be50-b3f7120bd9c6" />

* NOU: En aquest estat, els processos no tenen PCB. Quan el SO crea un nou procés, li assigna Memòria i un nou PCB, emmagatzemant-hi la informació com podrien ser punters, registres , pids...
El PCB s'insereix en la cua de preparats.
* PREPARAT: els processos en aquest estat tenen tos els recursos que necessiten per la seva execució expecte la CPU.Normalemnt, tots els processos que acaben de ser creats passen per aquest estat.
* INACTIU:
* EXECUCIÓ:
* ESPERA:




