#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Manipulação dos sinais
int sig = 0;

//funcoes assinadas
void tratasinais(int s);

//main
int main(void){

    signal(SIGUSR1, tratasinais);
    signal(SIGUSR2, tratasinais);

    
    while (1){//roda ate o proximo evento, no caso o ultimo sinal apos a `morte` do processo zumbi
        pause();
    } 
}

//funcoes
void tratasinais(int s){

    if(sig == 0){

        sig++;

        if(fork() == 0){

            exit(0); // processo filho `morto` sem o processo pai receber o sinal
        }

    } else if(sig == 1){

        sig++;
        wait(NULL); // Mata o processo zumbi

    } else{
        exit(0);
    }
}