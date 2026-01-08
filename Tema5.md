# 🖥️ Apunts de Sistemes Operatius - TEMA 5

## 📋 Índex
- [Tema5 - Introducció](#setmana-5---introducció)
- [Exemples Pràctics](#exemples-pràctics)
- [Dubtes i Preguntes](#dubtes-i-preguntes)
- [Reflexions Personals](#reflexions-personals)

---

## 🎯 TEMA 5 - Interbloqueig

### Introducció

* Per començar, hem de saber que en qualsevol sistema real hi ha recursos que:
    * No poden ser utilitzats simultaniament
    * No es poden duplicar fàcilment
* Situació 1: escrivint a la impressora → El resultat seria un text sense sentit.
* Com a SO hem d'encarregar-nos de gestionar aquests recursos i garantir que no hi hagi conflictes entre els procs.
* Exemple: Creació d'un fitxer:
    * El procés A necessita accedir a la taula del sistema de fitxers per crear una nova entrada per al nou fitxer. Aquesta entrada conté informació sobre el fitxer, com ara el seu nom, la seva mida i els permisos d’accés.
    * El procés A necessita accés exclusiu a la ranura per al nou fitxer per poder crear l’entrada correcta.
    * Si un procés B intentés crear un fitxer amb el mateix nom al mateix temps, el sistema operatiu bloquejaria el procés B fins que el procés A finalitzi la creació del nou fitxer.
* No obstant, ens podem trobar amb la següent situació:
    * El procés A demana permís per utilitzar l’escaner i se li concedeix.
    * El procés B demana permís per utilitzar la memòria USB i se li concedeix.
    * El procés A demana permís per utilitzar la memòria USB, però la petició queda suspesa fins que el procés B alliberi la memòria USB.
    * Desafortunadament,en lloc d’alliberar la memòria USB, el procés B demana permís per utilitzar l’escàner.
    * En aquest punt, els dos processos estan bloquejats i ho seguiran per sempre.
### Interbloqueig
* Hem arribat a la definició de deadlock per definició.
### Problema dels filosofs menjant
* Siguin 5 fílosofs menjant al voltant d'una taula circular. Tenim que si el fílosof vol menjar, llavors ha d'agafar els dos coberts que té al costat.
* Si tots els filòsofs agafen el cobert de la dreta alhora, es produeix un interbloqueig.
![alt text](image-14.png)
### Apropiativitat
* Apropiatiu: el SO pot retirar-lo temporalment d’un procés sense comprometre’n la coherència.
* No apropiatiu: un cop el procés l’ha adquirit, no es pot retirar fins que l’allibera.

* Memòria:
    * Apropiativa en sistemes amb swapping o paginació → el SO pot copiar pàgines al disc i recuperar-les després.
    * No apropiativa en sistemes sense swapping(android) → no es pot retirar memòria d’un procés de manera segura → pot causar pèrdua d’estat.
* Dispositius d’E/S:
    * No apropiatius: Impressores, discos durs → no es pot interrompre una operació d’escriptura sense perdre dades.
    * Apropiatius: Dispositius amb búfers → el SO pot desar dades en un búfer i continuar més tard.

* Polling: Tècnica que consisteix en un bucle de petició de recurs, dormir, nova petició de recurs, dormir, etc.

* Cada SO controla de manera diferent la solicitud de recursos:
    * Crida a sistema de petició
    * Crida open.
### Condicions de CoffMan
Si es compleixen totes les condicions -> Interbloqueig. Altrament no.
* 1 Condició d'exclusió mútua: Almenys un procés no pot ser compartit simultàniament. (Problema dels 5 filòsofs)
* 2 Hold and wait: Un procés reté almeny un recurs mentre espera un altre que esta en mans d'un altre procés. (Exemple: Escàner).
* IMPORTANT: Perquè el conjunt D estigui bloquejat, cada procés Pi reté almenys un recurs i espera al menys un recurs addicional; així s’està complint mantenir i esperar.
* 3 No apropiació: Un recurs no pot ser retirar a la força d'un procés. Han de ser alliberats pel procés que els té. (SO no pot dir et trec l'esáner encara que no haguis terminat)
* 4 Cadena Circular: Basicament veure si hi ha transitivitat en els processos
    * A espera B
    * B espera C
    * C espera A

### Estratègies per prevenir interbloquejos
* Ignorar el problema: Aquesta és una opció que generalment no es recomana, ja que pot conduir a conseqüències negatives. No prendre accions pot resultar en un estancament permanent del sistema.

* Algorisme de detecció: Utilitzar un algorisme de detecció de bloqueig: Implementar un sistema que monitoritzi l’ús dels recursos i detecti quan hi ha un potencial bloqueig.
* Algorisme de recuperació: Desenvolupar un procediment per alliberar els recursos del bloqueig i permetre la continuació del sistema. Això podria incloure la revocació de recursos o la reorganització de les prioritats.
* Evitar el Bloqueig de Forma Dinàmica: Implementar un algorisme predictiu: Desenvolupar un sistema que pugui preveure si l’assignació de recursos sol·licitada podria conduir a un bloqueig. Això permetrà prendre mesures abans que el problema esdevingui crític.
* Evitar les condicions de Coffman: Analitzar les condicions de Coffman, com l’exclusió mútua, la posada en espera circular i l’espera indefinida, i prendre mesures per assegurar que aquestes condicions (o alguna) mai es compleixin.

### Algorismes per evitar interbloquejos
* Ignorar el problema Ostrich: Posar el cap sota la sorra i fingir que no hi ha cap problema.
* Exemple: Imagina un sistema operatiu que no detecta els interbloquejos. Si un interbloqueig es produeix una vegada cada 10 anys, el sistema operatiu no hauria de preocupar-se per aquest problema. Si un interbloqueig es produeix una vegada cada 10 minuts, el sistema operatiu hauria de prendre mesures per evitar-lo.

* Algorisme de detecció:
* Prevenir (trencar les condicions de CoffMan). Disssenyem el sistema per tal que el deadlock sigui impossible.
* Exclusió mútua: Fer **spooling**, és a dir, fer una cua de peticions de recursos per tal que cada procés pugui executar-se en un temps determinat
* Mantenir i Esperar: Els processos demanen tots els recursos que necessiten al principi. Com que no es pot predir quants recursos necessitarà un porcés, ajustem dinàmicament les peticions segons les necessitats.
* No apropiació: Recursos apropiatius. No es pot aplicar a tots els recursos.
* Espera circular: Ordenar les peticions de recursos. Molt dificil de fer.
    * Implementar algorismes de gestió de recursos per minimizar les esperes circulars.

* Graf d'assignació de recursos:
Graf dirigit G = (V,E) on:   
    • V ≡ conjunt de vèrtex. V = P ∪ R, on P = {p1, . . . , pn} és un conjunt de processos, i R = {r1, . . . ,rn} és un conjunt de recursos
    • E ≡ conjunt d’arcs. E = { (pi,r j) ,(r j, pi) } , on (pi,r j) representa un arc de sol·licitud (el procés pi sol·licita un recurs r j) i (r j, pi) representa un arc d’assig- nació (el recurs r j està assignat al procés pi). Exemple: en la Figura 4.1 es mostra un exemple d’un graf d’assignació de recursos.

(Solsona, F. (2015). Sistemes operatius: teoria aplicada: ( ed.). Lérida, Spain: Edicions de la Universitat de Lleida. Recuperado de https://elibro.net/es/ereader/udl/54740?page=124.)
![alt text](image-15.png).

Si trobem un cicle, llavors hi ha interbloqueig. En aquest cas, es compleix.
```c
def detectar_cicle(NodeActual, LlistaArcs, L):
    Afegir NodeActual al final de L
    # Si el NodeActual ja era al camí → hem format un cicle
    si L.count(NodeActual) > 1:
        Imprimir "El graf conté un cicle: ", L
        Finalitzar l'algorisme
    # Obtenir arcs de sortida no marcats
    ArcsNoMarcats = [arc per arc en LlistaArcs
        si arc.origen == NodeActual i no arc.marcat]
    si ArcsNoMarcats != []:
        # Seleccionar un arc i baixar al node destí
        arc = Seleccionar_Arc_Atzar(ArcsNoMarcats)
        arc.marcat = True
        NodeSeguent = arc.desti
        detectar_cicle(NodeSeguent, LlistaArcs, L)
    sinó:  
        # No hi ha més arcs: cal retrocedir
        # Retirem el NodeActual del camí i tornem enrere
        L.pop()
        si L == []:
            Imprimir "El subgraf explorat no conté cicles"
            retornar
        NodeAnterior = L[-1]
        detectar_cicle(NodeAnterior, LlistaArcs, L)
```
```c
per cada Node N en LlistaNodes:
  Inicialitzar L a la llista buida  
  Marcar tots els arcs com a no marcats
  detectar_cicle(N, LlistaArcs, L)
```

* Exemple d'execució:

## Exemple d'execució de l'algorisme (I) {.smaller}

Assumeix que tenim un graf dirigit amb 4 nodes (A,B,C,D) i 4 arestes (A→B, B→C, C→D, D→A). Si començem amb el **Node A** com a node inicial:

-   Inicialitzem L a \[\].
-   Marquem tots els arcs com a no marcats.
-   Executem detectar_cicle(A, LlistaArcs, \[A\]).
-   Dins de detectar_cicle amb NodeActual = A:
    -   No hi ha cicles ja que A no apareix dues vegades a L.
    -   Seleccionem l'arc (A, B) i el marquem.
    -   Anem al node B, i tornem a executar detectar_cicle(B, LlistaArcs, \[A, B\]).
-   Dins de detectar_cicle amb NodeActual = B:
    -   No hi ha cicles ja que B no apareix dues vegades a L.
    -   Seleccionem l'arc (B, C) i el marquem.
    -   Anem al node C, i tornem a executar detectar_cicle(C, LlistaArcs, \[A, B, C\]).

Exemple d'execució de l'algorisme (II) 

-   Dins de detectar_cicle amb NodeActual = C:
    -   No hi ha cicles ja que C no apareix dues vegades a L.
    -   Seleccionem l'arc (C, D) i el marquem.
    -   Anem al node D, i tornem a executar detectar_cicle(D, LlistaArcs, \[A, B, C, D\]).
-   Dins de detectar_cicle amb NodeActual = D:
    -   No hi ha cicles ja que D no apareix dues vegades a L.
    -   Seleccionem l'arc (D, A) i el marquem.
    -   Anem al node A, i tornem a executar detectar_cicle(A, LlistaArcs, \[A, B, C, D, A\]).
-   Dins de detectar_cicle amb NodeActual = A:
    -   Afegim A a L, ara L és \[A, B, C, D, A\].
    -   Aquesta vegada A apareix dues vegades a L, indicant que hi ha un cicle.
    -   Imprimim *El graf conté un cicle: \[A, B, C, D, A\]* i finalitzem l'algorisme.

Consideracions sobre l'algorisme

-   Aquest algorisme no és eficient, ja que pot haver-hi molts camins per explorar.
-   Aquest algorisme només funciona per sistemes amb un únic recurs de cada tipus. Per sistemes amb múltiples instàncies de cada recurs, caldria utilitzar un altre algorisme.

### Graf d'espera

Graf dirigit que mostra les dependències entre els processos. Es construeix a partir del graf d’espera.
Construcció:

    1.Eliminar tots els nodes corresponents als recursos.

    2.Ajustar els arcs perquè apuntin als processos en lloc dels recursos.

* Si el graf d’espera conté un cicle, hi ha un interbloqueig.

Quan hi ha **múltiples instàncies de cada recurs**, els **cicles en el graf ja no són suficients** per detectar interbloquejos.  
Ara el problema no és només *qui espera a qui*, sinó **si hi ha prou quantitat de recursos** perquè algun procés pugui acabar.

L’objectiu de l’algorisme és respondre a la pregunta:

> Existeix algun ordre possible d’execució en què tots els processos puguin acabar?

Si la resposta és **no**, hi ha **interbloqueig**.

---

* Idea intuïtiva

- Processos = persones
- Recursos = monedes de diferents tipus
- Cada procés:
  - té alguns recursos
  - en necessita alguns més per acabar
- El sistema:
  - té un nombre limitat de recursos

L’algorisme **simula mentalment** si els processos podrien acabar **en el millor dels casos**.

---

### Estructures de dades

#### Vector **E** — Recursos totals

Indica el nombre total d’instàncies de cada recurs.

$\mathbf{E} = (E_1, E_2, \ldots, E_m)$


---

#### Matriu **C** — Recursos assignats

$C_{ij} = \text{nombre d’instàncies del recurs } R_j \text{ assignades al procés } P_i$

Indica **qui té què actualment**.

---

#### Matriu **R** — Recursos sol·licitats

$R_{ij} = \text{nombre d’instàncies del recurs } R_j \text{ que el procés } P_i \text{ encara necessita}$

No és el màxim, sinó **el que li falta ara mateix** per acabar.

---

### Vector **A** — Recursos disponibles

$A_j = E_j - \sum_i C_{ij}$

Indica quants recursos **estan lliures** en cada moment.

---

## Condició bàsica de bloqueig

Si un procés demana més recursos dels disponibles:

$R_{ij} > A_j \Rightarrow P_i \text{ es bloqueja}$

És una condició necessària però no suficient per detectar interbloqueig.

---

## Algorisme de detecció (explicat pas a pas)

### Pas 1 — Inicialització
- Tots els processos es consideren **no marcats**.

---

### Pas 2 — Cerca d’un procés executable
- Busquem un procés no marcat \(P_i\) tal que:
$\mathbf{R}_i \le \mathbf{A}$

És a dir:
> Tot el que necessita està disponible ara mateix.

Aquest procés **podria acabar**.

---

### Pas 3 — Simulació d’execució
Si trobem un procés executable:
- L’assumim acabat
- Allibera tots els seus recursos
- Actualitzem:
$\mathbf{A} = \mathbf{A} + \mathbf{C}_i$
- Marquem el procés com a segur
- Tornem al pas 2

---

### Pas 4 — Finalització
Si no existeix cap procés que compleixi¡$\mathbf{R}_i \le \mathbf{A}$
- L’algorisme s’atura

---

### Pas 5 — Detecció d’interbloqueig
- **Tots els processos no marcats** estan en interbloqueig

No existeix cap ordre d’execució que els permeti acabar.

---

## Assumpció important

L’algorisme assumeix el **pitjor cas**:
- Els processos **no alliberen recursos fins que acaben**
- No hi ha cooperació

Això el fa **conservador**:
- Si detecta interbloqueig → segur que n’hi ha

---

## Comparació amb el cas d’una sola instància

| Cas | Criteri de detecció |
|----|---------------------|
| 1 instància per recurs | Cicle en el graf |
| M instàncies | Cap procés compleix $\mathbf{R}_i \le \mathbf{A}$ |





* Algorisme d'evitació:
### Algorsime del Banquer
* El SO només concendirà un recurs si està segur que, pasi el que pasi , després ningú es quedi bloquejat.
* Metàfora del banc:
    * El banc té diners limitats (recursos).

    * Cada client (proceso):

        * ja té algo de calers

        * podria demanar més en el futur

    * El banc vol evitar bancarrota (deadlock).

* Estat segur: Un estat és segur si existeix almenys un ordre en què tots els processos poden:
    * obtenir els recursos que falten,
    * acabar,
    * i alliberar els recursos per als següents
* Seqüencia segura (P1,P2,...,Pn) és segura si:
    * P1 pot acabar amb els recursos disponibles,
    * P2 pot acabar amb els recursos dipsonibles + els que allibera p1.
    * Seguim així fins a n.
* Estat insegur: Si no existeix cap seqüencia segura.

### Aplicació del Algorisme per a 1 ssol recurs.
* Només hi ha:
    * Un tipus de recurs
    * diverses unitats indèntique
* Per a cada procés coneixem:
    * Assignat: quants recursos té ara
    * Max: quants en podria necesssitar com a màxim
* Es defineix $Necessita​= Max − Assignat​$
* Procés pot acabar si: $Necessita <= Disponibles$

---


### Exemple 1 — Estat segur trivial

#### Dades

| Procés | Assignat | Max | Necessita |
|------|----------|-----|-----------|
| A | 0 | 6 | 6 |
| B | 0 | 5 | 5 |
| C | 0 | 4 | 4 |
| D | 0 | 7 | 7 |

Recursos disponibles: **10**

#### Anàlisi

- Tots els processos tenen Necessita ≤ 10.
- Qualsevol procés pot acabar primer.
- En acabar, no bloqueja la resta.

#### Conclusió

✅ **Estat segur**  
Existeixen múltiples seqüències segures.

---

### Exemple 2 — Estat segur (no trivial)

#### Dades

| Procés | Assignat | Max | Necessita |
|------|----------|-----|-----------|
| A | 1 | 6 | 5 |
| B | 1 | 5 | 4 |
| C | 2 | 4 | 2 |
| D | 4 | 7 | 3 |

Recursos disponibles: **2**

---

#### Pas 1 — Processos que poden acabar

- A: necessita 5 → ❌
- B: necessita 4 → ❌
- C: necessita 2 → ✅
- D: necessita 3 → ❌

👉 **C pot acabar**

---

#### Pas 2 — Simulem que C acaba

- C allibera 2 recursos  
- Recursos disponibles = 2 + 2 = **4**

---

#### Pas 3 — Amb 4 recursos disponibles

- B: necessita 4 → ✅
- D: necessita 3 → ✅
- A: necessita 5 → ❌

Triem, per exemple, **B**.

---

#### Pas 4 — Simulem que B acaba

- B allibera 1 recurs  
- Recursos disponibles = 4 + 1 = **5**

---

#### Pas 5 — Amb 5 recursos disponibles

- A: necessita 5 → ✅
- D: necessita 3 → ✅

Tots els processos poden acabar.

#### Seqüència segura possible

C → B → A → D

#### Conclusió

✅ **Estat segur**

---

### Exemple 3 — Estat insegur

#### Dades

| Procés | Assignat | Max | Necessita |
|------|----------|-----|-----------|
| A | 1 | 6 | 5 |
| B | 2 | 5 | 3 |
| C | 2 | 4 | 2 |
| D | 4 | 7 | 3 |

Recursos disponibles: **1**

---

#### Anàlisi

- A: necessita 5 → ❌
- B: necessita 3 → ❌
- C: necessita 2 → ❌
- D: necessita 3 → ❌

👉 **Cap procés pot acabar inicialment**

---

#### Conclusió

❌ **Estat insegur**

No existeix cap seqüència segura.  
Si el sistema entra en aquest estat, el deadlock és possible.

---





## Exemples pràctics

## Dubtes i preguntes

## Reflexions personals
-Estic aprenent molt