#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
struct ElemLista {
    int l, c;            // info about the node
    struct ElemLista* next;  // adress of the next node
};

typedef struct ElemLista nodlista;

struct ElemStack {
    nodlista* lista;
    struct ElemStack* next;
};

typedef struct ElemStack nodstack;

void verifis(const FILE *f);
int neighbours(const char mat[][101], int i, int j, int linii, int coloane);
void task1(int n, int m, int k, char matrice[][101], FILE* output);
void addAtBeginning(nodlista** head, int linie, int coloana);
void addAtEnd(nodlista** head, int linie, int coloana);
void printLista(nodlista *head, FILE* output);
void push(nodstack** top, nodlista* list);
void deleteStack(nodstack** top);
void deleteList (nodlista **head);
void task2(int n, int m, int k, char matrice[][101], FILE* output, nodstack** top);
nodlista* pop(nodstack** top);
void task2bonus(nodstack** top, char matrice[][101], int n, int m, int k);