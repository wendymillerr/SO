#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {

    int thread_id;
    int* vector_a;
    int* vector_b;
    int size;

}ThreadArgs;


void* sumVectors(void* arg){

    ThreadArgs *args = (ThreadArgs) arg;
    int thread_id = args->thread_id;
    int* vector_a = args-> vector_a;
    int* vector_b = args->vector_b;
    int size = args->size;

    int result = 0;
    for(int i = thread_id; i < size; i+=size){
        result += vector_a[i] + vector_b[i];
    }

    printf("Sou a thread %d e o resultado da soma é %d\n", thread_id, result);

    pthread_exit(NULL);
}


int main(int argc, char* argv[]){

    if(argc != 2){
        printf("Uso: %s <tamanho_vetor>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    
    int* vector_a = (int*)malloc(size * sizeof(int));
    int* vector_b = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i+=size){
        vector_a[i] = random (0, 99);
        vector_b[i] = random (0, 99)
    }

   pthread_t* threads = (pthread_t*)malloc(size * sizeof(pthread_t));
   ThreadArgs* thread_args = (ThreadArgs*)malloc(size * sizeof(ThreadArgs));

    for(int i=0; i < size; i++){

        thread_args[i].thread_id = i;
        thread_args[i].size = size;
        thread_args[i].vector_a = vector_a;
        thread_args[i].vector_b = vector_b;
        pthread_create(&thread_args[i], NULL, sumVectors, (void*)&thread_args[i]);

    }

    for(int i = 0; i < size; i++){
         pthread_join(threads[i], NULL);
    }

    free(vector_a);
    free(vector_b);
    free(threads);
    free(thread_args);
   
   return 0;

}


