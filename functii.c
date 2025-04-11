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
