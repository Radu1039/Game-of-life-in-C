#include "GameofLife.h"

void verifis(const FILE *f)   ///functie pentru verificarea deschiderii fiserului
{
    if(f==NULL)
    {
        puts("Fisierul nu s a deschis");
        exit(1);
    }
}

int neighbours(const char mat[][DIMMAX], int i, int j, int linii, int coloane)  ///functie pentru numararea vecinilor ai fiecarui element din matrice
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

void task1(int n, int m, int k, char matrice[][DIMMAX], FILE* output)
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
        char newGoF[DIMMAX][DIMMAX];  ///aici o sa punem modificarile pentru a respecta exact regulile jocului
    
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

        for(int i=0;i<n;i++)  ///matricecopiem matricea temporara in matricea noastra
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
    
    if (*head == NULL) 
        addAtBeginning(&*head, linie, coloana);
    else {
        nodlista *aux = *head;
        nodlista *newNode = (nodlista*)malloc(sizeof(nodlista));   ///am schimbat aici fctia fata de cum era 
        newNode->l = linie;                                         ///deoarece rameneau aux si newnode initializate dar nefolosite
        newNode->c = coloana;
        while (aux->next != NULL) 
            aux = aux->next;
        aux->next = newNode;
        newNode->next = NULL;                                                            
    }
}

void printLista(nodlista *head, FILE* output) { 
    while (head != NULL) {
        fprintf(output, " %d %d", head->l, head->c);   ///modificata pentru a afisa linia si coloana
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
    while ((*top) != NULL) {  
        temp = *top;
        *top = (*top)->next;            
        deleteList(&temp->lista);       ///modificata pentru a sterge si lista informatie a nodului de stiva
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

void task2(int n, int m, int k, char matrice[][DIMMAX], FILE* output, nodstack** top)       ///aceeasi procedura ca la task 1 dar ...
{
    *top=NULL;                      ///stiva
    for(int gen=1;gen<=k;gen++)
    {
        nodlista* head=NULL;        ///lista pentru fiecare generatie
        standard(&head,n,m,matrice);
        fprintf(output, "%d", gen);         ///afisam numarul generatiei
        printLista(head, output);           ///si lista

        push(top, head);                ///stocam lista in stiva
    }
}

nodlista* pop(nodstack** top) {         ///modificata pentru a returna o lista
    
    if ((*top) == NULL) 
        return NULL;

    nodstack *temp = (*top);
    nodlista* aux = temp->lista;
    *top = (*top)->next;
    free(temp);

    return aux;
}

void task2bonus(nodstack** top, char matrice[][DIMMAX], int n, int m, int k, FILE* output)
{
    while(k>0)
    {
        nodlista* listagen=pop(top);        ///aici punem lista fiecarei generatie
        
        nodlista *iter=listagen;               ///o parcurgem
            while (iter != NULL  ) {   
                if(matrice[iter->l][iter->c]=='X')      ///fiecare element al listei gasit corespunde unui element al matricei care
                    matrice[iter->l][iter->c]='+';              ///va fi schimbat
                else if(matrice[iter->l][iter->c]=='+')
                    matrice[iter->l][iter->c]='X';
                iter = iter->next;         
	        }
        deleteList(&listagen);                  ///stergem lista pentru a scapa de memmory leaks
        k--;
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++)                    ///afisam in fisier
            fprintf(output,"%c",matrice[i][j]);
        fprintf(output,"\n");
    }
}

void regulaB(nodlista **head, int n, int m,char matrice[][DIMMAX])
{
    char newGoF[DIMMAX][DIMMAX];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            {
                int vecini = neighbours(matrice, i,j,n,m);
                if(matrice[i][j]=='+')
                {
                    if(vecini==2)
                    {
                        newGoF[i][j]='X';
                        addAtEnd(head,i,j);
                    }
                    else
                        newGoF[i][j]='+';
                }
                else 
                    newGoF[i][j]='X';                    
            }

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            matrice[i][j]=newGoF[i][j];
}

void standard(nodlista **head, int n, int m, char matrice[][DIMMAX])
{
    char newGoF[DIMMAX][DIMMAX];        

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int vecini=neighbours(matrice, i,j, n,m);

            if(matrice[i][j]=='X')
            {
                if(vecini<2 || vecini>3)
                {
                    newGoF[i][j]='+';           ///aici construim si matricea si adaugam in lista coordonatele i si j
                    addAtEnd(head, i, j);      
                }
                else
                    newGoF[i][j]='X';
            }    
            else
            {
                if(vecini==3)
                {
                    addAtEnd(head,i,j);
                    newGoF[i][j]='X';
                }
                else
                    newGoF[i][j]='+';
            }
        }
    }

    for(int i=0;i<n;i++)  
        for(int j=0;j<m;j++)
            matrice[i][j]=newGoF[i][j];
}


nodarbore* copacinit(int n, int m,const char matrice[][DIMMAX])   ///functia asta initializeaza radacina arborelui cu lista de celule vii
{
    nodarbore *root=(nodarbore*)malloc(sizeof(nodarbore));
    root->left=root->right=NULL;
    nodlista *head=NULL;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {   
            if(matrice[i][j]=='X')
                addAtEnd(&head,i,j);
        }   
    root->lista=head;
    return root;

}

void task3(nodarbore **root,int n, int m, int k, char matrice[][DIMMAX])
{
    if(k<=0) return;   ///caz pentru a opri recursia

    char matriceB[DIMMAX][DIMMAX];      ///matrice pentru nodul stang (regula B)
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            matriceB[i][j]=matrice[i][j];

    if(*root==NULL)
        *root=copacinit(n,m, matrice);   ///initializam arborele

    nodlista *head1=NULL,*head2=NULL;      ///construim listele dupa cele 2 reguli
    regulaB(&head1, n, m, matriceB);
    standard(&head2, n,m ,matrice);

    (*root)->left=(nodarbore*)malloc(sizeof(nodarbore));    ///dupa care le punem in nodurile corespunzatoare
    (*root)->left->left=(*root)->left->right=NULL;
    (*root)->left->lista=head1;

    (*root)->right=(nodarbore*)malloc(sizeof(nodarbore));
    (*root)->right->left=(*root)->right->right=NULL;
    (*root)->right->lista=head2;

    k--;                                            ///scadem o generatie
    task3(&(*root)->left, n, m, k, matriceB);       ///apelam recursiv functia pentru fii
    task3(&(*root)->right, n, m, k, matrice);
}

void preorder(nodarbore *root,int n, int m,FILE *output, char matriceCurenta[][DIMMAX])     ///parcurgere in preordine
{
    if(root)            
    {
        char matricecopie[DIMMAX][DIMMAX];          ///copie a matricei pentru a construi corect generatiile
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                matricecopie[i][j]=matriceCurenta[i][j];
        
        nodlista *listacurenta=root->lista;
        while(listacurenta!=NULL)                       ///parcurgem lista pentru a duce la capat game of life
            {
                if(matricecopie[listacurenta->l][listacurenta->c]=='+')
                    matricecopie[listacurenta->l][listacurenta->c]='X';
                else
                    matricecopie[listacurenta->l][listacurenta->c]='+';
                listacurenta=listacurenta->next;
            }

        for(int i=0;i<n;i++)                    ///afisam matricea
        {
            for(int j=0;j<m;j++)
                fprintf(output,"%c",matricecopie[i][j]);
            fprintf(output,"\n");
        }
        fprintf(output,"\n");

        preorder(root->left, n, m, output,matricecopie);            ///apelam recursiv pentru fii
        preorder(root->right, n, m, output,matricecopie);
    }
}

void freeArbore(nodarbore **root)       ///functie pentru eliberarea arborelui
{
    if(*root==NULL) return;

    freeArbore(&(*root)->left);
    freeArbore(&(*root)->right);

    deleteList(&(*root)->lista);        ///scapam si de lista

    free(*root);
    *root=NULL;
}