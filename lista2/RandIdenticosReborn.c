#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//globais

int resultadosEncontrados[10000000];

//struct 

struct valores{
    int Mi;
    int Mf;
    int S;
};


//funcoes assinadas

void *sementeGerada(void *arg);

//main

int main(void){

    int Mi, Mf, S;
    struct valores val1;

    phtread_t thread1,thread2;

    scanf(" %d %d %d", &Mi, &Mf, &S);

   val1.Mi = Mi;
    val1.Mf = (Mi+Mf)/2;
    val1.S = S;

    val2.Mi = (Mi+Mf)/2 + 1;
    val2.Mf = Mf;
    val2.S= S;
    val2.tamanho = tamanho;

    pthread_create(&thread1, NULL, sementeGerada, (void *)&val1);
    pthread_create(&thread2, NULL, sementeGerada, (void *)&val2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

///funcoes

void *sementeGerada(void *arg){

    int atual, final, auxiliarPAleatorio,i,j;

    struct valores *temporario = (struct valores*)arg;

    for(i = temporario->Mi; i <= temporario->Mf; i++){
        auxiliarPAleatorio = i;

            for(j=1; j<10000;j++){
                rand_r(&auxiliarPAleatorio);
            }

            final = (rand_r(&auxiliarPAleatorio) % 8); //dessa vez modulo para 8 ao invez de 256

            if(final != temporario->S){
                continue;
            }  

            if( final == temporario->S){
                printf("%d\n", i);
            } 
    }
}






