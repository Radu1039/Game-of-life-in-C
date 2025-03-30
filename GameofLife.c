#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, const char* argv[])
{
    for(int t = 1; t < argc; t+=2)
    {
        FILE *input_file = fopen(argv[t], "r");
        FILE *output_file = fopen(argv[t+1], "w");

      
        char GoF[101][101];
        int T,N,M,K;

        if(t<=5)  ///task 1
        {
            fscanf(input_file, "%d %d %d %d", &T, &N, &M, &K);  

            for(int i=0;i<N;i++)                                    ///citire data*.in unde * numar de la 1 la 5
                for(int j=0;j<M;j++)                            
                    fscanf(input_file, " %c", &GoF[i][j]);
 
            for(int i=0;i<N;i++)  ///afisam matricea initiala
            {
                for(int j=0;j<M;j++)
                    fprintf(output_file,"%c", GoF[i][j]);       ///in data*.out
                fprintf(output_file,"\n");
            }
            fprintf(output_file,"\n");

            while(K>0)
            {
                char newGoF[101][101];  ///aici o sa punem modificarile pentru a respecta exact regulile jocului
            
                for(int i=0;i<N;i++)
                {   
                    for(int j=0;j<M;j++)
                    {
                        int vecini=neighbours(GoF, i,j, N,M);

                        if(GoF[i][j]=='X')
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

                for(int i=0;i<N;i++)  ///copiem matricea temporara in matricea noastra
                    for(int j=0;j<M;j++)
                        GoF[i][j]=newGoF[i][j];

                for(int i=0;i<N;i++)  ///afisam matricea de urmatoarea generatie
                {
                    for(int j=0;j<M;j++)
                        fprintf(output_file,"%c", GoF[i][j]);       ///in data*.out
                    fprintf(output_file,"\n");
                }
                fprintf(output_file,"\n");

                K--;
            }
        }
        fclose(input_file);
        fclose(output_file);
    }
    
    return 0;
}