#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>//permite trabalhar com tempo
#include <string.h>
#include <errno.h>//permite reportar e retornar erros

//funcoes assinadas

float getTempo(struct timeval *ini, struct timeval *fim);//recupera o tempo de execução dos processos

//main

int main(void)
{
        struct timeval ini, fim, ini_t, fim_t;

        char path[50], args[75];

        gettimeofday(&ini_t, NULL);//recupera a hora atual com uma precisão de microssegundos

        while (scanf(" %s %s", path, args) == 2)
        {
                gettimeofday(&ini, NULL);
                pid_t pid = fork();
                if (pid == 0)
                {
                        fclose(stdin);//fecha arquivo
                        execl(path, path, args, NULL);//executa o arquivo
                        printf("> Erro: %s\n", strerror(errno));
                        fflush(stdout);//descarrega buffer de saida do fluxo de dados
                        _exit(errno);//funciona como exit
                }
                else
                {
                        int ret;
                        pid = wait(&ret);
                        gettimeofday(&fim, NULL);
                        printf("> Demorou %.1f segundos, retornou %d\n", getTempo(&ini, &fim), WEXITSTATUS(ret));
                }
                fflush(stdout);
        }
        gettimeofday(&fim_t, NULL);
        printf(">> O tempo total foi de %.1f segundos\n", getTempo(&ini_t, &fim_t));
        exit(0);
}

//funcoes

float getTempo(struct timeval *ini, struct timeval *fim)
{
        return (fim->tv_sec - ini->tv_sec) + (fim->tv_usec - ini->tv_usec) / 1000000.0;//sec = tempo em segundos e usec = tempo em microsegundos
}