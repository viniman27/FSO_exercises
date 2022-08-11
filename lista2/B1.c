#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//globais

int resultadosEncontrados[10000000];

//struct para manipulação dos valores

struct valores{
    int Mi;
    int Mf;
    int qual;
    int tamanho;
};


//funcoes assinadas

int numerosAleatoriosMudou();
void *sementeGerada(void *arg);

//main

int main(void){

    int Mi, Mf;
    
    scanf(" %d %d", &Mi, &Mf);//menor e maior valor da semente

    int a = 0, b = 1;

    int tamanho = numerosAleatoriosMudou();

    struct valores val1, val2;

    val1.Mi = Mi;
    val1.Mf = (Mi+Mf)/2;
    val1.qual = 0;
    val1.tamanho = tamanho;

    val2.Mi = (Mi+Mf)/2 + 1;
    val2.Mf = Mf;
    val2.qual = 1;
    val2.tamanho = tamanho;

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, sementeGerada, (void *)&val1);
    pthread_create(&thread2, NULL, sementeGerada, (void *)&val2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

//funcoes

int numerosAleatoriosMudou(){
    int num, i = 0;

    while(scanf(" %d", &num) != EOF){
        resultadosEncontrados[i++] = num;
    }

    return i;
}

void *sementeGerada(void *arg){

    int atual, auxiliar, final, auxiliarPAleatorio,i,l,j;

    struct valores *temporario = (struct valores*)arg;

    for(i = temporario->Mi; i <= temporario->Mf; i++){
        auxiliarPAleatorio = i;
        auxiliar = 0;

        for(l = 0; l < temporario->tamanho; l++){

            for(j=1; j<10000;j++){

                rand_r(&auxiliarPAleatorio);
            }

            final = (rand_r(&auxiliarPAleatorio) % 256); 

            if(final != resultadosEncontrados[auxiliar]){
                break;
            }  

            if(auxiliar == temporario->tamanho-1 && final == resultadosEncontrados[auxiliar]){
                printf("%d\n", i);
                return i;
            } 

            auxiliar++;
        }
    }
}