#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>



//funcoes assinadas
void tratasinais(int s);

//main
int main(void){

    signal(SIGINT, tratasinais);
    signal(SIGUSR1, tratasinais);
    signal(SIGUSR2, tratasinais);
    signal(SIGTERM, tratasinais);

    //sinal que apos determinado tempo, termina o processo
    signal(SIGALRM, tratasinais);

    
    while (1){//roda ate um evento, no caso o EOF
        pause();
    } 
}

//funcoes
void tratasinais(int s){
    char voz[11];
    int acerto = 0;

    if(scanf(" %s", voz) != EOF){

        if(s == SIGUSR1 && strcmp(voz, "Igor3k") == 0){

            printf("Certo\n");
            acerto = 1;

        } else if(s == SIGUSR2 && strcmp(voz, "Monark") == 0){

            printf("Certo\n");
            acerto = 1;

        } else if(s == SIGINT && strcmp(voz, "Con1") == 0){

            printf("Certo\n");
            acerto = 1;

        } else if(s == SIGTERM && strcmp(voz, "Con2") == 0){

            printf("Certo\n");
            acerto = 1;

        } else if(s == SIGALRM && strcmp(voz, "Silencio") == 0){

            printf("Certo\n");
            acerto = 1;
        }
        if(acerto == 0){

            printf("Erro\n");
            kill(getppid(),SIGALRM);
            
        }
    } else{
        exit(0);
    }
}