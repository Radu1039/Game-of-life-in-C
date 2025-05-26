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
        
        if(mati>=0 && mati<linii && matj>=0 && matj<coloane )
        {
            char celulavecinacurenta=mat[mati][matj];
            if(celulavecinacurenta=='X')
                nrX++;
        }
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

void DFS_scan(Graph *g, int visited[], int i,int conexa[], int* conexedim) {
    int j;
    visited[i] = 1;
    conexa[(*conexedim)++]=i;       ///adauga nodul in comp conexa curenta
    for (j = 0; j < g->V; j++) 
        if (g->a[i][j] == 1 && visited[j] == 0)
            DFS_scan(g, visited, j,conexa,conexedim);
}

void DFS(Graph *g,int conexe[][DIMMAX], int conexedim[], int *comp_conexe) {
    int i, visited[DIMMAX];
    *comp_conexe=0;
    for (i = 0; i < g->V; i++)
        visited[i] = 0;
    for (i = 0; i < g->V; i++) 
        if (visited[i] == 0) {
            conexedim[*comp_conexe]=0;   ///reset la dim componentei curente
            DFS_scan(g, visited, i,conexe[*comp_conexe],&conexedim[*comp_conexe]);
            (*comp_conexe)++;
        }
}

int existaNod(Graph *g, int curent, int urm, int cale[], int lungcale)      ///verifica daca se poate merge de la nodul curent la nodul urmator
{
    if(g->a[curent][urm]==0) return 0;

    for(int i=0;i<lungcale;i++)         ///evitam ciclurile
        if(cale[i]==urm)            
            return 0;

    return 1;
}

void backtrackLant(Graph* g, int conexa[], int conexedim, int curent, int cale[], int lungcale,         ///nu am reusit sa gasesc problema, banuiesc ca e pe aici sau in celmailunglanthamil 
                    int vizitat[], int* lungmax, int caleok[])                                          ///sunt cateva grafuri la care nu gaseste corect lantul si gaseste unul mai mare chiar daca de fapt nu ar trebui sa existe
{
    if(*lungmax==conexedim) return;     ///return case

    if(lungcale>*lungmax){              ///daca calea curenta este mai lunga decat cea ok actualizam
        *lungmax = lungcale;
        for(int i=0;i<lungcale;i++)
            caleok[i]=cale[i];
    }

    for(int i=0;i<conexedim;i++)            ///incercam sa extindem prin fiecare nod nevizitat
    {
        int urmconex = conexa[i];
        if(vizitat[urmconex]==0 && existaNod(g,curent, urmconex,cale,lungcale))
        {
            vizitat[urmconex]=1;
            cale[lungcale]=urmconex;
            backtrackLant(g,conexa,conexedim,urmconex,cale,lungcale+1,vizitat,lungmax,caleok);
            vizitat[urmconex]=0;        ///backtrack
        }
    }
}

void swap(int *a,int *b)
{
    int aux=*a;
    *a=*b;
    *b=aux;
}

// Dacă în graf sau într-una din componentele sale conexe există mai multe lant,uri
// cu aceeas,i dimensiune (maximă), se va alege lant,ul care pornes,te dintr-un nod de
// pe linia cu indicele cel mai mic. Dacă există mai multe lant,uri care pleacă din
// această linie, se va alege lant,ul în care vârful are indicele de coloană cel mai mic.
// Acelas,i principiu se aplică pentru întreaga succesiune de vârfuri din lant,.
// •În cazul în care într-un graf există mai multe componente conexe ce cont,in lant,uri
// Hamiltoniene, se va lua în considerare componenta cu lant,ul cel mai lung.
// •Dacă în graf sau în componentele sale conexe nu există niciun lant,Hamiltonian,
// afis,at,i lungimea -1

void sortareDupaCriterii(int conexa[], int conexedim, int coord[][2])
{
    for(int i=0;i<conexedim-1;i++)
        for(int j=0;j<conexedim-i-1;j++)
        {
            int nod1 = conexa[j],nod2 = conexa[j+1];

            if(coord[nod1][0]>coord[nod2][0] || (coord[nod1][0]==coord[nod2][0] && coord[nod1][1]>coord[nod2][1]))
                swap(&conexa[j],&conexa[j+1]);
        }       

}

int celMaiLungLantHamil(Graph *g, int coord[][2], int calebuna[])
{
    if(g->V==0) return -1; ///graf gol

    int conexe[DIMMAX][DIMMAX],conexedim[DIMMAX],nrconexe=0,lungmax=-1,caleok[DIMMAX*DIMMAX]={0};

    DFS(g,conexe,conexedim,&nrconexe);    ///gaseste toate comp conexe

    for(int i=0;i<nrconexe;i++){        ///le luam pe fiecare in parte

        int conexadim=conexedim[i];
        int* conexa=conexe[i];

        sortareDupaCriterii(conexa,conexadim,coord);        ///sortam

        int lungmaxinconex = -1;
        int caleokinconex[DIMMAX*DIMMAX]={0};

        for(int j=0;j<conexadim;j++)
        {
            int nodstart=conexa[j],cale[DIMMAX*DIMMAX],caleokcurenta[DIMMAX*DIMMAX],vizitat[DIMMAX]={0},lungmaxcurenta=1;

            for(int l=0;l<g->V;l++)     ///pregatim backtrackingul
                vizitat[l]=0;

            vizitat[nodstart]=1;        ///marcam nodul de start
            cale[0]=nodstart;
            caleokcurenta[0]=nodstart;

            backtrackLant(g,conexa,conexadim,nodstart,cale,1,vizitat,&lungmaxcurenta,caleokcurenta);

            if(lungmaxcurenta>lungmaxinconex)       ///actualizam cea mai buna cale din aceasta componenta
            {
                lungmaxinconex=lungmaxcurenta;
                for(int k=0;k<lungmaxcurenta;k++)
                    caleokinconex[k]=caleokcurenta[k];
            }

            if(lungmaxcurenta==conexadim)       ///pt lant hamiltonian
                break;
        }

        if(lungmaxinconex>lungmax)      ///pentru intregul graf
        {
            lungmax=lungmaxinconex;
            for(int j=0;j<lungmaxinconex;j++)
                caleok[j]=caleokinconex[j];
        }
    }

    if(lungmax>0)                   ///pentru lungime maxima
        for(int i=0;i<lungmax;i++)
            calebuna[i]=caleok[i];

    return lungmax;

}

void task4(nodarbore* root, int n, int m,int k, int nivelcurent,char matriceCurenta[][DIMMAX],FILE *output)
{
    if(root==NULL || nivelcurent>k) return;

    if(nivelcurent<0) return;

        char matrice[DIMMAX][DIMMAX];
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                matrice[i][j]=matriceCurenta[i][j];

        nodlista *listacurenta=root->lista;
        while(listacurenta!=NULL)                       ///parcurgem lista pentru a duce la capat game of life
        {
            if(matrice[listacurenta->l][listacurenta->c]=='+')
                matrice[listacurenta->l][listacurenta->c]='X';
            else
                matrice[listacurenta->l][listacurenta->c]='+';
            listacurenta=listacurenta->next;
        }
         /*for(int i=0;i<n;i++)                    ///afisam matricea
        {
            for(int j=0;j<m;j++)
                fprintf(output,"%c",matrice[i][j]);
            fprintf(output,"\n");
        }
        fprintf(output,"\n");*/
        int coord[DIMMAX*DIMMAX][2];
        Graph *g=construiesteGraf(n,m,matrice,coord);

        if(g){
            int cale[DIMMAX*DIMMAX]={0};
            int lungimelant = celMaiLungLantHamil(g,coord,cale);
            fprintf(output,"%d\n",lungimelant-1);

            if(lungimelant>0)
            {
                for(int i=0;i<lungimelant;i++)
                {
                    int nod = cale[i];
                    fprintf(output,"(%d,%d)",coord[nod][0],coord[nod][1]);
                    if(i<lungimelant-1)
                        fprintf(output," ");
                }
                fprintf(output,"\n");
            }


            freeGraf(g);
        }
        else
            fprintf(output, "-1\n");
        if(nivelcurent<k)
        {
            task4(root->left,n,m,k, nivelcurent+1,matrice,output);
            task4(root->right,n,m,k,nivelcurent+1,matrice,output);
        }
    
}

void construiesteMatriceAdia(const char mat[][DIMMAX], int i, int j, int linii, int coloane,int **matriceAdiacenta, int *nrmuchii, int numerotare[DIMMAX][DIMMAX])
{
    const int iorizontal[]={-1, -1, -1, 0, 0, 1, 1, 1}, 
                jvertical[]={-1, 0, 1, -1, 1, -1, 0, 1};  ///offseturi

    int indexcelulacurenta=numerotare[i][j];
    for (int k=0;k<8;k++)
    {
        int mati=i+iorizontal[k],matj=j+jvertical[k] ;
        
        if(mati>=0 && mati<linii && matj>=0 && matj<coloane)
        {
            char celulavecinacurenta=mat[mati][matj];
            int indexvecin=numerotare[mati][matj];
            if(celulavecinacurenta=='X' && matriceAdiacenta[indexcelulacurenta][indexvecin]==0)
            {
                matriceAdiacenta[indexcelulacurenta][indexvecin]=matriceAdiacenta[indexvecin][indexcelulacurenta]=1;
                (*nrmuchii)++;
            }
        }
                
    }
}

Graph* construiesteGraf(int n, int m, char matrice[][DIMMAX], int coordinitiale[][2])
{
    int i,j,numerotare[DIMMAX][DIMMAX];  ///numerotam de la 0...
   
    Graph *g=(Graph*)malloc(sizeof(Graph));

    if(g==NULL){
        printf("memerror"); return NULL;}

    g->V=0;
    
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(matrice[i][j]=='X')
            {
                coordinitiale[g->V][0]=i;       ///ca sa retinem coordonatele cand afisam caile
                coordinitiale[g->V][1]=j;
                numerotare[i][j]=g->V++;
            }
            else
                numerotare[i][j]=-1;

    g->a=(int**)malloc(g->V*sizeof(int*));

    for(i=0;i<g->V;i++)
        g->a[i]=(int*)calloc(g->V,sizeof(int));

    if(g->a==NULL){
        printf("memerror"); return NULL;
    }

    g->E=0;

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(matrice[i][j]=='X')
                construiesteMatriceAdia(matrice, i,j,n,m,g->a,&g->E,numerotare);
    return g;
}

void freeGraf(Graph* g)
{
    if(g==NULL) return;

    if(g->a!=NULL)
    {
        for(int i=0;i<g->V;i++)
        {
            if(g->a[i]!=NULL)
            {
                free(g->a[i]);
            }
        }
        free(g->a);
    }
    free(g);
}