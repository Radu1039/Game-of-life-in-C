#include "GameofLife.h"

void verifis(const FILE *f)   ///functie pentru verificarea deschiderii fiserului
{
    if(f==NULL)
    {
        puts("Fisierul nu s a deschis");
        exit(1);
    }
}

int neighbours(const char mat[][101], int i, int j, int linii, int coloane)  ///functie pentru numararea vecinilor ai fiecarui element din matrice
{
    int nrX=0;
    const int iorizontal[]={-1, -1, -1, 0, 0, 1, 1, 1}, 
                jvertical[]={-1, 0, 1, -1, 1, -1, 0, 1};  ///offseturi
    for (int k=0;k<8;k++)
    {
        int matx=i+iorizontal[k];
        int maty=j+jvertical[k];
        if(matx>=0 && matx<linii && maty>=0 && maty<coloane)
            if(mat[matx][maty]=='X')
                nrX++;
    }
    return nrX;
}

void task1(int n, int m, int k, char matrice[][101], FILE* output)
{
    for(int i=0;i<n;i++)  ///afisam matricea initiala
    {
        for(int j=0;j<m;j++)
            fprintf(output,"%c", matrice[i][j]);       ///in data*.out
        fprintf(output,"\n");
    }
    fprintf(output,"\n");

    while(k>0)
    {
        char newGoF[101][101];  ///aici o sa punem modificarile pentru a respecta exact regulile jocului
    
        for(int i=0;i<n;i++)
        {   
            for(int j=0;j<m;j++)
            {
                int vecini=neighbours(matrice, i,j, n,m);

                if(matrice[i][j]=='X')
                {
                    if(vecini<2 || vecini>3)  ///subpopulare && suprapopulare
                        newGoF[i][j]='+';
                    else
                        newGoF[i][j]='X';  ///supravietuire

                }
                else 
                {
                    if(vecini==3)
                        newGoF[i][j]='X';  ///reproducere
                    else
                        newGoF[i][j]='+';  ///not reproducere
                }
            }
        }

        for(int i=0;i<n;i++)  ///copiem matricea temporara in matricea noastra
            for(int j=0;j<m;j++)
                matrice[i][j]=newGoF[i][j];

        for(int i=0;i<n;i++)  ///afisam matricea de urmatoarea generatie
        {
            for(int j=0;j<m;j++)
                fprintf(output,"%c", matrice[i][j]);       ///in data*.out
            fprintf(output,"\n");
        }
        fprintf(output,"\n");

        k--;
    }
}

void addAtBeginning(nodlista** head, int linie, int coloana) {
    nodlista *newNode = (nodlista*)malloc(sizeof(nodlista));
	newNode->l = linie;
    newNode->c = coloana;
	newNode->next = *head;
	*head = newNode;
}

void addAtEnd(nodlista** head, int linie, int coloana) {
    
    // daca lista este vida, se modifica adresa de inceput
    if (*head == NULL) 
        addAtBeginning(&*head, linie, coloana);
    else {
        nodlista *aux = *head;
        nodlista *newNode = (nodlista*)malloc(sizeof(nodlista));
        newNode->l = linie; // se stocheaza informatia nodului nou
        newNode->c = coloana;
        // cat timp nu s-a ajuns la final, se parcurge
        while (aux->next != NULL) 
            aux = aux->next;
        // se adauga noul element in lista
        aux->next = newNode;
        newNode->next = NULL; // final lista
    }
}

void printLista(nodlista *head, FILE* output) { // lista nu se modifica
    while (head != NULL) {
        fprintf(output, " %d %d", head->l, head->c);
        head = head->next;
    }
    fprintf(output,"\n");
}

void push(nodstack** top, nodlista* list) {
    nodstack* newNode = (nodstack*)malloc(sizeof(nodstack));
    newNode->lista = list;
    newNode->next = *top;
    *top = newNode;
}

void deleteStack(nodstack** top) {
    nodstack* temp;
    while ((*top) != NULL) {  // echivalent cu !isEmpty(*top)
        temp = *top;
        *top = (*top)->next;
        deleteList(&temp->lista);
        free(temp);
    }
}

void deleteList (nodlista **head ) {
    nodlista *headcopy ;
    while (*head != NULL ) 
    {
        headcopy = (*head)->next ;
        free (*head);
        *head = headcopy ; 
    }
    *head = NULL ;
}

void task2(int n, int m, int k, char matrice[][101], FILE* output, nodstack** top)
{
    *top=NULL;
    for(int h=1;h<=k;h++)
    {
        nodlista* head=NULL;
        char newGoF[101][101];
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                int vecini=neighbours(matrice, i,j, n,m);

                if(matrice[i][j]=='X')
                {
                    if(vecini<2 || vecini>3)
                    {
                        newGoF[i][j]='+';
                        addAtEnd(&head, i, j);
                    }
                    else
                        newGoF[i][j]='X';
                }    
                else
                {
                    if(vecini==3)
                    {
                        addAtEnd(&head,i,j);
                        newGoF[i][j]='X';
                    }
                    else
                        newGoF[i][j]='+';
                }
            }
        }
        for(int i=0;i<n;i++)  ///copiem matricea temporara in matricea noastra
            for(int j=0;j<m;j++)
                matrice[i][j]=newGoF[i][j];

        fprintf(output, "%d", h);
        printLista(head, output);

        push(top, head);

    }
    deleteStack(top);
}
