#include "GameofLife.h"

int main(int argc, const char* argv[])
{
    for(int t = 1; t < argc; t+=2)
    {
        FILE *input_file = fopen(argv[t], "r");
        FILE *output_file = fopen(argv[t+1], "w");

        verifis(input_file);
        verifis(output_file);

        char GoF[101][101];
        int T,N,M,K;
        nodstack* stiva=NULL;

        fscanf(input_file,"%d",&T);     ///citire numar task

        fscanf(input_file, "%d %d %d", &N, &M, &K);  

        for(int i=0;i<N;i++)                                    ///citire data*.in unde * numar de la 1 la 5
            for(int j=0;j<M;j++)                            
                fscanf(input_file, " %c", &GoF[i][j]);
        
        if(T==1)  ///task 1
            task1(N,M,K,GoF,output_file);
        else if(T==2)  ///task 2
            task2(N,M,K,GoF,output_file, &stiva);
        fclose(input_file);
        fclose(output_file);
    }
    
    return 0;
}