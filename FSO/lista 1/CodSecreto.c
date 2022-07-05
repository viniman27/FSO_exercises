#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Variável que verifica se a senha for recebida
int senha = 0;

//funcoes assinadas
void tratasinais(int s);

//main
int main(void){

    //sinal para interromper o processo(^c)
    signal(SIGINT, tratasinais);

    //sinais definidos pelo user,uteis para comunicacao entre processos
    signal(SIGUSR1, tratasinais);
    signal(SIGUSR2, tratasinais);

    //sinal para terminar processo
    signal(SIGTERM, tratasinais);

    
    while (1){//roda ate que seja interrompido por um evento, no caso sinais na ordem SIGINT SIGUSR2 SIGTERM SIGUSR1
        pause();
    }
}

//funcoes 

void tratasinais(int s){

    printf("Recebi %d\n", s);

    if(s == SIGINT){//if trabalha os sinais e incrementa senha de acordo com a ordem de insercao

        senha = 1;

    } else if(senha == 1 && s == SIGUSR2){

        senha++;

    } else if(senha == 2 && s == SIGTERM){

        printf("Senha acionada\n");
        senha++;

    } else if(senha == 3 && s == SIGUSR1){

        printf("Tchau\n");
        exit(0);

    } else{

        senha = 0; // Reinicia a senha caso não tenha a sequência completa.

    }
}