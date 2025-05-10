#include "GameofLife.h"

int main(int argc, const char* argv[])
{
    int nrfisierbonus=1;   ///numar pentru numele fiserelor pentru task2 bonus
    char bonus='n';
    printf("\n");
    puts("Vrei sa vezi taskul bonus? (d/n)");  ///task 2 bonus
    scanf(" %c",&bonus);

    for(int t = 1; t < argc; t+=2)
    {
        FILE* input_file = fopen(argv[t], "r");
        FILE* output_file = fopen(argv[t+1], "w");

        verifis(input_file);
        verifis(output_file);

        char GoF[101][101];
        int T,N,M,K;
        
        fscanf(input_file,"%d",&T);     ///citire numar task

        fscanf(input_file, "%d %d %d", &N, &M, &K);  

        for(int i=0;i<N;i++)                                    ///citire data*.in unde * numar de la 1 la 5
            for(int j=0;j<M;j++)                            
                fscanf(input_file, " %c", &GoF[i][j]);
        
        if(T==1)  ///task 1
            task1(N,M,K,GoF,output_file);
        if(T==2)  ///task 2
        {
            int gen=1;
            nodstack* stiva=NULL;
            task2(N,M,K,GoF, &stiva);
            printStivaDeJosInSus(stiva,output_file,&gen);     ///afisam stiva de jos in sus
            
            if(bonus=='d')
            {
                char fisier[]="OutputData/task2bonus_.out";     
                fisier[21]=nrfisierbonus+'0';       ///transform cifra in litera si o pun in locul lui _
                FILE *output_task2bonus =fopen(fisier,"w");
                verifis(output_task2bonus);
                task2bonus(&stiva, GoF, N,M,K,output_task2bonus);
                fclose(output_task2bonus);
                nrfisierbonus++;
            }
            
            deleteStack(&stiva); ///eliberare memorie
        }
        if(T==3) ///task3
        {
            nodarbore *copac=NULL;
            char matriceInit[DIMMAX][DIMMAX];  ///matrice numai cu '+'
            for(int i=0;i<N;i++)
                for(int j=0;j<M;j++)
                    matriceInit[i][j]='+';
            task3(&copac,N,M,K, GoF);
            preorder(copac,N ,M,output_file ,matriceInit);  ///afisare
            freeArbore(&copac);   ///eliberare memorie
        }
        fclose(input_file);
        fclose(output_file);
    }
    
    return 0;
}