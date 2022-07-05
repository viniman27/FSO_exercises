
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Conta SIGALRM recebidos
int sig = 0;

//funcoes assinadas
void tratasinais(int s);

//main
int main(void){

    signal(SIGUSR1, tratasinais);
    signal(SIGALRM, tratasinais);


    while (1){//continua ate o proximo evento, no caso
        pause();
    } 
}

//funcoes
void tratasinais(int s){

    if(s == SIGUSR1){

        printf("SIGUSR1 eh para aproveitar mais um pouco\n");

    } else if (s == SIGALRM && sig != 2){

        printf("Ai que sono, quero dormir mais um pouco\n");
        sig++;

    } else{//sig = 3

        printf("Os incomodados que se mudem, tchau\n");
        exit(0);
        
    }
    
}