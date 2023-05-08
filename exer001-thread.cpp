#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void* hello_world_thread(void * arg);
char * read_name();


int main(int argc, char *argv[]){
    char * name = read_name();
  
    if(name == NULL){
        return 1;
    }


    pthread_t t1;
    int status;
    void *thread_return;
    /* 
        1: Crie a thread que executa a função "hello_world_thread", passando o nome "name" como argumento.
    */
    /*   Trecho 1  */

    status = pthread_create(&t1, NULL, hello_world_thread, (void*)&name);

    if(status!=0){
        printf("Erro na criação da thread. Codigo de Erro:%d\n", status);
        return 2;
    }
    
    char *saida ;

   status = pthread_join(t1, (void**)&saida);
    /* 
        2: Espere pelo término da thread e receba o resultado.
    */
    /*   Trecho 2  */

    printf("Recebido: \"%s\"\n", saida);
    free(saida);
    free(name);

    printf("Fim.\n");

    return 0;
}



void* hello_world_thread(void * arg){
    printf("Thread iniciada\n");

    char * name = (char *)arg;
    const char * format = "Olá, %s!";

    //Aloca espaço para saída
    int outSize = strlen(name) + strlen(format);
    char * output = (char *)malloc(outSize);

    //Escreve na saída o resultado
    snprintf(output, outSize, format, name);

    //Imprime mensagem
    printf("Mensagem: \"%s\"\n", output);

    printf("Finalizando thread.\n");

    
    /* 
        3: retorne a variável "output" como resultado da thread.
    */
    /*   Trecho 3  */
  return output;
}


char * read_name(){
    char * name = NULL;
    size_t len = 0;

    printf("Informe o seu nome: ");
    ssize_t readed = getline(&name, &len, stdin);
    if(readed == -1){
        printf("Erro: nome não foi lido\n");
        return NULL;
    }
    // "remove" \n no final
    name[readed - 1] = '\0';

    return name;
}
