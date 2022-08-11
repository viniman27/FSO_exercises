#include <stdio.h>
#include <stdlib.h>

//globais

int resultadosEncontrados[10000000];

//funcoes assinadas

int numerosAleatoriosMudou();
int sementeGerada(int Mi, int Mf, int tamanho);

//main

int main(void){

    int Mi, Mf;
    
    scanf(" %d %d", &Mi, &Mf);//menor e maior valor da semente

    int tamanho = numerosAleatoriosMudou();

    printf("%d\n", sementeGerada(Mi, Mf, tamanho));

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

int sementeGerada(int Mi, int Mf, int tamanho){

    int atual, auxiliar, final, auxiliarPAleatorio,i,l,j;

    for(i = Mi; i <= Mf; i++){
        auxiliarPAleatorio = i;
        auxiliar = 0;

        for(l = 0; l < tamanho; l++){

            for(j=1; j<10000;j++){

                rand_r(&auxiliarPAleatorio);
            }

            final = (rand_r(&auxiliarPAleatorio) % 256); 

            if(final != resultadosEncontrados[auxiliar]){
                break;
            }  

            if(auxiliar == tamanho-1 && final == resultadosEncontrados[auxiliar]){
                return i;
            } 

            auxiliar++;
        }
    }
}