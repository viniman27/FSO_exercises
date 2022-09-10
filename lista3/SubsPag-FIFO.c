#include <stdio.h>
#include <stdlib.h>

//funcoes assinadas

int busca(int r, int l, int n, int *v, int k);

//main

int main(void){

    int n, v[10001],i;

    scanf(" %d", &n);//numero de paginas

    for ( i = 0; i < n; i++){//paginas acessadas pelo sistema
        scanf(" %d", &v[i]);
    }

    int q, maxpag = -1, maxq = 0, flag = 0, flagb = 0;

    while(scanf(" %d", &q) == 1){//numero de paginas que deve ser testada

        int *f, pg = 0, u = 0, p = 0;

        f = malloc(sizeof(int)*q);

        for(i = 0; i < n; i++){

            if((u+1)%q != p){

                if(u != p &&  busca(p, u, q, f, v[i]))

                    continue;

                else{

                    f[u++] = v[i];
                    u = u == q ? 0 : u;
                    pg++;

                }
            }else{

                if(busca(p, u, q, f, v[i]))
                    continue;
                else{
                    p++;
                    p = p == q ? 0 : p;
                    f[u++] = v[i];
                    u = u == q ? 0 : u;
                    pg++;
                }
            }
        }

        printf("%d %d\n", q, pg);

        if(flag == 0){
            flag = 1;
            maxpag = pg;
            maxq = q;
        }else if(pg > maxpag && q > maxq){
            maxpag = pg;
            maxq = q;
            flagb = 1;
        }
    }
    if(flagb){
        printf("Belady detectado\n");
    }else {
        printf("Sem anomalia\n");
    }
    return 0;
}

//funcoes

int busca(int r, int l, int n, int *v, int k){

    int i;

    for ( i = r; ; i = (i+1)%n){
        if(v[i] == k)
            return 1;
        if(i == l)
            break;
    }
    
    return 0;
}
