#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DIMMAX 101   ///dimensiune maxima pentru matrice

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