#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//variaveis globais
int matriz1[2000][2000], matriz2[2000][2000], matriz3[2000][2000];
int sinalfilho1 = 0, sinalfilho2 = 0;// Sinais dos filhos

//funcoes assinadas
void filho1(int s);
void filho2(int s);
void multiplicaMatrizes(int n, int l, int r, int sinal);

//main
int main(void){

    int n;//dimensao das matrizes quadradas
    int i,j;
    signal(SIGUSR1, filho1);
    signal(SIGUSR2, filho2);

    scanf(" %d", &n);

    int metadematriz = n/2, resto = n%2;//variaveis para contronar problemasd de matrizes quadradas geradas com n impar
    pid_t filhos[2];
    int sinais[2];
    sinais[0] = SIGUSR1;
    sinais[1] = SIGUSR2;

    // Composicao matriz 1
    for( i = 0; i < n; i++){
        for ( j = 0; j < n; j ++){

            scanf(" %d", &matriz1[i][j]);
            matriz3[i][j]=0; // Garante que a matriz comeca zerada

        }
    }

    // Composicao matriz 2
    for( i = 0; i < n; i++){
        for ( j = 0; j < n; j ++){

            scanf(" %d", &matriz2[i][j]);

        }
    }
    
    for ( i = 0; i < 2; i++){

        int l = i*metadematriz, sinal = sinais[i], r;

        if(i == 1){

            r = resto + i*metadematriz+metadematriz; // Caso seja ímpar, o resto  afeta os resultados

        }else{

            r = i*metadematriz+metadematriz;

        }

        filhos[i] = fork(); // cria processo filho

        if(filhos[i]==0){

            multiplicaMatrizes(n, l, r, sinais[i]);

        }
    }

    pause(); // Espera o proximo evento, no caso o calculo do produto

    // Um dos dois processos filhos envia o sinal que acabou de calcular, entao espera o proximo evento
    while(sinalfilho1 == 0 || sinalfilho2 == 0){
        pause();
    }

    kill(filhos[0], SIGUSR1);
    wait(NULL);
    kill(filhos[1], SIGUSR1);
    wait(NULL);
}

//funcoes 

void filho1(int s){
    sinalfilho1++;
}

void filho2(int s){
    sinalfilho2++;
}

void multiplicaMatrizes(int n, int l, int r, int sinal){
    // Calcula a multiplicação 
    for(int i = l; i < r; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                matriz3[i][j] += matriz1[i][k]*matriz2[k][j];
            }
        }
    }

    kill(getppid(), sinal);// Avisa que acabou e espera
    pause();

    // metadematrizu de volta, imprime
    for(int i = l; i < r; i++){

        printf("%d", matriz3[i][0]);

            for(int j=1; j< n; j++){

                printf("%d", matriz3[i][j]);
                
        }
        printf("\n");
    }

    kill(getppid(), sinal); // Avisa que acabou e espera

    exit(0);
}