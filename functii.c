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
        int mati=i+iorizontal[k],matj=j+jvertical[k];
        char celulacurenta=mat[mati][matj];
        if(mati>=0 && mati<linii && matj>=0 && matj<coloane && celulacurenta=='X')
                nrX++;
    }
    return nrX;
}

int inViata(int i, int j, nodlista* head)   ///verifica daca o celula e inviata cu ajutorul unei liste
{
    while(head!=NULL)
    {
        if(head->l==i && head->c==j)
            return 1;
        head=head->next;
    }
    
    return 0;
}

int neighboursCuListe(int i, int j, int linii, int coloane, nodlista *head)         ///varianta fara matrice
{
    int nrX=0;
    const int iorizontal[]={-1, -1, -1, 0, 0, 1, 1, 1}, 
                jvertical[]={-1, 0, 1, -1, 1, -1, 0, 1};  ///offseturi
    for (int k=0;k<8;k++)
    {
        int mati=i+iorizontal[k],matj=j+jvertical[k];
        if(mati>=0 && mati<linii && matj>=0 && matj<coloane)
        {
            int inviata=inViata(mati,matj,head);

            if(inviata)
                nrX++;
        }
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
        addAtBeginning(head, linie, coloana);
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

void task2(int n, int m, int k, char matrice[][DIMMAX], nodstack** top,char bonus)       
{
    *top=NULL;                      ///stiva
    nodlista *gencurenta=NULL;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(matrice[i][j]=='X')
                addAtEnd(&gencurenta,i,j);          ///lista cu celule vii initiale
    for(int gen=1;gen<=k;gen++)
    {
        nodlista* genurm=generatiaUrmatoareStd(n,m,gencurenta);     ///lista cu celulele vii din generatia urmatoare
        nodlista* diferente=difGen(n,m,gencurenta,genurm);          ///lista cu modificarile de la o generatie la alta

        push(top, diferente);                ///stocam lista in stiva

        deleteList(&gencurenta);            ///eliberam
        gencurenta=genurm;              ///pentru urmatoarea iteratie
    }

    if(bonus=='d')
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)    
                matrice[i][j]='+';          ///matrice goala fara celule vii

        nodlista *aux=gencurenta;       ///construim ultima matrice
        while(aux!=NULL)
        {
            matrice[aux->l][aux->c]='X';        
            aux=aux->next;
        }
    }
    deleteList(&gencurenta);
}

void printStivaDeJosInSus(nodstack* top, FILE *output, int *gen)
{
    if(top==NULL) return;

    printStivaDeJosInSus(top->next,output,gen);     ///apelam recursiv ca sa inceapa afisarea de jos

    fprintf(output,"%d",*gen);              ///afisam nr generatiei
    (*gen)++;                               
    printLista(top->lista,output);          ///si lista
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
    while(k>0 && *top!=NULL)
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

/*1. Orice celulă vie cu mai putin de doi vecini în viat,ă moare (subpopulare).
2. Orice celulă vie cu doi sau trei vecini vii trăies,te în continuare.
3. Orice celulă vie cu mai mult de trei vecini vii moare (suprapopulare).
4. Orice celulă moartă cu exact trei vecini devine o celulă vie (reproducere)
*/

nodlista* generatiaUrmatoareStd(int n, int m, nodlista* celulevii)            ///returneaza lista cu celulele vii din generatia urmatoare dupa 
{                                                                                ///regulile de mai sus
    nodlista* celuleviiurmatoare=NULL;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            int vecini=neighboursCuListe(i,j, n, m,celulevii), inviata=inViata(i,j,celulevii);
            
            if(inviata)
            {
                if(vecini==2 || vecini==3)
                    addAtEnd(&celuleviiurmatoare,i,j);
            }
            else
                if(vecini==3)
                    addAtEnd(&celuleviiurmatoare,i,j);
        }
    return celuleviiurmatoare;
}

nodlista* difGen(int n, int m, nodlista* celulevii, nodlista* celuleviiurmatoare)       ///lista cu celulele care isi modifica starea
{
    nodlista* diferente=NULL;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            int inviata=inViata(i,j,celulevii), inviataurmatoare=inViata(i,j,celuleviiurmatoare);

            if(inviata!=inviataurmatoare)
                addAtEnd(&diferente,i,j);
        }
    return diferente;
}
/// Regula B : Orice celula moarta cu 2 vecinie invie
nodlista* generatiaUrmatoareRegulaB(int n, int m, nodlista *celulevii)          ///lista cu celulele vii din generatia urmatoare
{                                                                                   ///dupa regula B
    nodlista* celuleviiurmatoare=NULL;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            int vecini=neighboursCuListe(i,j, n, m,celulevii), inviata=inViata(i,j,celulevii);
            
            if(inviata)
                addAtEnd(&celuleviiurmatoare,i,j);
            else
                if(vecini==2)
                    addAtEnd(&celuleviiurmatoare,i,j);
        }
    return celuleviiurmatoare;
}

nodarbore* copacinit(int n, int m,const char matrice[][DIMMAX])   ///functia asta initializeaza radacina arborelui cu lista de celule vii
{
    nodarbore *root=(nodarbore*)malloc(sizeof(nodarbore));
    root->left=root->right=NULL;
    nodlista *head=NULL;
    for(int i=0;i<n;i++)            ///construim prima lista cu celule vii
        for(int j=0;j<m;j++)
        {   
            if(matrice[i][j]=='X')
                addAtEnd(&head,i,j);
        }   
    root->lista=head;       ///si o punem in radacina
    return root;

}

void creazaNodStg(nodarbore* root,nodlista* head)           ///creeaza copilul stang
{
    root->left=(nodarbore*)malloc(sizeof(nodarbore));    
    root->left->left=root->left->right=NULL;
    root->left->lista=head;
}

void creazaNodDr(nodarbore* root,nodlista* head)        ///creeaza copilul drept
{
    root->right=(nodarbore*)malloc(sizeof(nodarbore));    
    root->right->left=root->right->right=NULL;
    root->right->lista=head;
}

void task3(nodarbore **root,int n, int m, int k,const char matrice[][DIMMAX],nodlista* gencurenta)
{
    if(k<=0) return;   ///caz pentru a opri recursivitatea

    if(*root==NULL)
    {
        *root=copacinit(n,m, matrice);          ///initializam arborele
        gencurenta=(*root)->lista;          ///generatie cu celulele vii initiale
    }
    nodlista *genurm=generatiaUrmatoareStd(n,m,gencurenta);             ///celulele vii din generatia urm dupa standard
    nodlista *genurmB=generatiaUrmatoareRegulaB(n,m,gencurenta);            ///dupa regula B
    nodlista *diferente=difGen(n,m,gencurenta,genurm);              ///modificarile dupa standard
    nodlista *diferenteB=difGen(n,m,gencurenta,genurmB);            ///dupa regula B

    creazaNodStg(*root,diferenteB);             ///cream fiii
    creazaNodDr(*root,diferente);

    k--;                                            ///scadem o generatie
    task3(&((*root)->left), n, m, k, matrice,genurmB);       ///apelam recursiv functia pentru fii
    task3(&((*root)->right), n, m, k, matrice,genurm);

    deleteList(&genurm);            ///free dupa ce se termina recursivitatea
    deleteList(&genurmB);
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