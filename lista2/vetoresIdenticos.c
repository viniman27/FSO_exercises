#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// globais

int vetor1[10000000];
int vetor2[10000000];

// Struct Thread

struct thread_st{
    int *vetor;  // vetor da thread
    int tamanho; // tamanho do vetor 
    pthread_t tid; // id da thread 
};

//funcoes assinadas

int compara(const void *a, const void *b);
void *ordenathread(void *t);
void entradaVetores(int numeroAssociado, int tamanho);

//main

int main(void){

    int tamanho, vetorigual = 1,i;

    scanf(" %d", &tamanho);

    // Lê vetores

    entradaVetores(1, tamanho);
    entradaVetores(2, tamanho);

    struct thread_st t1, t2;

    t1.vetor = vetor1;
    t1.tamanho = tamanho;

    t2.vetor = vetor2;
    t2.tamanho = tamanho;

    //cria e ordena as threads
    pthread_create(&t1.tid, NULL, ordenathread, (void*)&t1);
    pthread_create(&t2.tid, NULL, ordenathread, (void*)&t2);

    //aguarda as threads encerrarem, mas sem anecessidade de receber o valor de retorno
    pthread_join(t1.tid, NULL);
    pthread_join(t2.tid, NULL);

    for( i = 0; i < tamanho; i++){

        if(vetor1[i] != vetor2[i]){
            vetorigual = 0;
        }
    }

    if(vetorigual == 1){
        printf("Mesmos elementos\n");
        return 0;
    } 
    
    printf("Diferentes\n");
    return 0;

}


//funcoes 


int compara(const void *a, const void *b){// Função para qsort fazer a comparação

    if(*(int *)a > *(int*)b) return 1;//iguais
    if(*(int *)a < *(int*)b) return -1;//diferentes
    return 0;

}


void *ordenathread(void *t){// Função que vai fazer o sort

    struct thread_st *a = (struct thread_st*)t; // Cria uma nova thread struct dependendo de "numeroAssociado"  passado como argumento
    qsort(a->vetor, a->tamanho, sizeof(int), compara);//ordena usando quicksort, já implementado na biblioteca
}


void entradaVetores(int numeroAssociado, int tamanho){// Função para ler vetores

    int i;

    if(numeroAssociado == 1){

        for(i = 0; i < tamanho; i++){
            scanf(" %d", &vetor1[i]);
        }
    } else{
        
        for(i = 0; i < tamanho; i++){
            scanf(" %d", &vetor2[i]);
        }
    }
    return;

}