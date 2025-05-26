#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DIMMAX 201   ///dimensiune maxima pentru matrice

struct ElemLista {
    int l, c;            ///nod lista care contine linia si coloana
    struct ElemLista* next;  
};

typedef struct ElemLista nodlista;

struct ElemStack {
    nodlista* lista;  ///nod stiva care contine o lista
    struct ElemStack* next;
};

typedef struct ElemStack nodstack;

struct ElemArbore {
    nodlista* lista;        ///nod arbore care contine o lista
    struct ElemArbore* left;
    struct ElemArbore* right;
};

typedef struct ElemArbore nodarbore;

typedef struct {
    int V, E;
    int **a;
} Graph;

void verifis(const FILE *f);

int inViata(int i, int j, nodlista* top);

int neighbours(const char mat[][DIMMAX], int i, int j, int linii, int coloane);

int neighboursCuListe(int i, int j, int linii, int coloane, nodlista *top);

void task1(int n, int m, int k, char matrice[][DIMMAX], FILE* output);

void addAtBeginning(nodlista** head, int linie, int coloana);

void addAtEnd(nodlista** head, int linie, int coloana);

void printLista(nodlista *head, FILE* output);

void push(nodstack** top, nodlista* list);

void deleteStack(nodstack** top);

void deleteList (nodlista **head);

void task2(int n, int m, int k, char matrice[][DIMMAX], nodstack** top,char bonus);

nodlista* pop(nodstack** top);

void task2bonus(nodstack** top, char matrice[][DIMMAX], int n, int m, int k, FILE* output);

nodlista* generatiaUrmatoareStd(int n, int m, nodlista* celulevii);

nodlista* difGen(int n, int m, nodlista* celulevii, nodlista* celuleviiurmatoare);

nodarbore* copacinit(int n, int m,const char matrice[][DIMMAX]);

void creazaNodStg(nodarbore* root,nodlista* head);

void creazaNodDr(nodarbore* root,nodlista* head);

void task3(nodarbore **root,int n, int m, int k,const char matrice[][DIMMAX],nodlista* gencurenta);

void preorder(nodarbore *root,int n, int m,FILE *output, char matriceCurenta[][DIMMAX]);

void freeArbore(nodarbore **root);

nodlista* generatiaUrmatoareRegulaB(int n, int m, nodlista *celulevii);

void printStivaDeJosInSus(nodstack* top,FILE* output, int *gen);

void task4(nodarbore* root, int n, int m, int k, int nivelcurent, char matriceCurenta[][DIMMAX], FILE *output);

void construiesteMatriceAdia(const char mat[][DIMMAX], int i, int j, int linii, int coloane, 
                           int **matriceAdiacenta, int *nrmuchii, int numerotare[DIMMAX][DIMMAX]);

Graph* construiesteGraf(int n, int m, char matrice[][DIMMAX], int coordinitiale[][2]);

void DFS_scan(Graph *g, int visited[], int i,int conexa[], int* conexedim);

void DFS(Graph *g,int conexe[][DIMMAX], int conexedim[], int *comp_conexe);

int existaNod(Graph *g, int curent, int urm, int cale[], int lungcale);

void backtrackLant(Graph* g, int conexa[], int conexedim, int curent, int cale[], int lungcale, int vizitat[], int* lungmax, int caleok[]);

void swap(int *a,int *b);

void sortareDupaCriterii(int conexa[], int conexedim, int coord[][2]);

int celMaiLungLantHamil(Graph *g, int coord[][2], int calebuna[]);

void freeGraf(Graph* g);
