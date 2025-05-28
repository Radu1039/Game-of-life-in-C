# Game Of Life in C       

https://site-pa.netlify.app/proiecte/game_of_life/

Game of Life sau Conway's Game of Life este un joc care simuleaza evolutia sau moartea celuleor intr o matrice dupa niste 
reguli bine definite. 
In acest proiect, folosim diferite structuri de date pentru a efectua diferite taskuri, cum ar fi: 
stive, liste, arbori binari, grafuri. 

Game of Life ne demonstreaza cum se pot crea comportamente complexe din reguli simple. Ne folosim de stive pentru a stoca eficient generatiile unei matrici, arbore binar pentru a simula simultan doua instante de game of life, fiecare cu regulile lor si grafuri pentru a gasi un lant hamiltonian in grafurile formate de celule vii.

## Taskuri:

- Task 1: 
Simulare Game of Life normala
Ne folosim de matrice pentru a stoca gridul cu celule si generam K generatiile dupa regulile impuse.
1. Orice celulă vie cu mai putin de doi vecini în viată moare (subpopulare).
2. Orice celulă vie cu doi sau trei vecini vii trăieste în continuare.
3. Orice celulă vie cu mai mult de trei vecini vii moare (suprapopulare).
4. Orice celulă moartă cu exact trei vecini devine o celulă vie (reproducere)

- Task 2:
Folosim o stiva de liste pentru a stoca eficient din punctul de vedere al memoriei diferentele de stare. Incep cu o lista de 
coordonate ale celulelor vii, calculez celulele vii din generatia urmatoarea si apoi construiesc lista de diferente de stare 
ale celulelor pe care o pushez in stiva.

- Task 2 bonus:
Avem matricea generatiei K si stiva de liste. Parcurg stiva si schimb celulele din moarte in vii si din vii in moarte dupa lista.

- Task 3:
Acum vom folosi un arbore binar pentru a calcula generatiile pentru 2 seturi de reguli diferite: in stanga vor fi matricele standard si in dreapta vor fi dupa urmatoare regula: Orice celulă cu exact doi vecini vii devine celulă vie. Dar le vom stoca
eficient, ca liste, la fel ca in taskul 2.

- Task 4:
In final, reprezentam matricele pentru fiecare generatie a arborelui printr un graf pentru care trebuie sa gasim cel mai lung lant hamiltonian. Incepem cu DFS pentru a determina componentele conexe, facem backtrack pentru a lua in considerare toate posibilitatile si gasim lungimea dar si calea. Aici nu am reusit sa l fac perfect deoarece sunt cateva grafuri care imi returneza un lant mai mare decat ce ar trebui sa mi afiseze. Suspectez ca nu mi face bine lantul in unele situatii si imi returneaza un lant care nu e Hamiltonian

## Ce trebuie sa fie instalat:
- GCC compiler
- Make utility

## Cum se executa:
- Build: make
- Clean: make clean
- Run: make run

## Cum arata inputul:
T          # Numarul taskului (1-4)  
N M        # Dimensiunile matricei (N - linii, M - coloane)  
K          # Numarul de generatii  
Matricea

## Structura proiectului:
├── GameofLife.c      # main  
├── GameofLife.h      # header cu functiile si structurile declarate  
├── functii.c         # toate functiile implementate  
├── Makefile          # pentru rulare simpla  
├── InputData/        # folder cu inputuri  
└── OutputData/       # folder cu outputuri

## Test Data:
Cateva exemple de inputuri se pot gasi la: https://gitlab.cs.pub.ro/paaa/project-data

## Detalli despre structura folositoare pentru alti dezvoltatori:
Functiile sunt numite dupa fiecare task si sunt destul de explicite.Cateva exemple:
int neighbours(const char mat[][DIMMAX], int i, int j, int linii, int coloane) gaseste vecini folosind offseturi folosit in task 1

int neighboursCuListe(int i, int j, int linii, int coloane, nodlista *head) gaseste vecinii fara ajutorul unei matrice folosit in task 2

void printStivaDeJosInSus(nodstack* top, FILE *output, int *gen) afiseaza lista in ordine inversa

nodlista* generatiaUrmatoareStd(int n, int m, nodlista* celulevii) genereaza lista de celule vii din gen urmatoare + varianta pentru regula B (se poate modifica pentru a respecta alte reguli)

nodlista* difGen(int n, int m, nodlista* celulevii, nodlista* celuleviiurmatoare) genereaza lista de schimbari de stare pentru a o stoca in stiva

void DFS_scan(Graph *g, int visited[], int i,int conexa[], int* conexedim) stocheaza componenta conexa

void DFS(Graph *g,int conexe[][DIMMAX], int conexedim[], int *comp_conexe) stocheaza toate componentele conexe dintr un graf si le numara

void backtrackLant(Graph* g, int conexa[], int conexedim, int curent, int cale[], int lungcale,       
                    int vizitat[], int* lungmax, int caleok[]) face backtrack pentru a cauta print toate lanturile              

int celMaiLungLantHamil(Graph *g, int coord[][2], int calebuna[]) tine minte cel mai lung lant si calea respectiva                            
