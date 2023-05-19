
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>



typedef struct{

  int thread_id;
  int* vector;
  int size;

} ThreadArgs;

void* multiplica(void *arg){
    ThreadArgs *args = (ThreadArgs*) arg;
    int thread_id = args->thread_id;
    int* vector = args->vector;
    int size = args->size;


    int pair_id = thread_id * 2;
    int result = vector[pair_id] * vector[pair_id + 1];
    printf("Sou a thread %d e o resultado da multiplicação é %d\n", thread_id, result);
    pthread_exit(NULL);
    
}


int main(int argc, char* argv[]) {

  if(argc != 2){
    printf("Erro na quantidade de argumentos\n");
  }

  int n = atoi(argv[1]);
  if(n % 2 == 0){

  int *vector = (int*)malloc(n * sizeof(int));

    for(int i=0; i < n; i++){
      vector[i] = rand() % 100;
    }

  
  pthread_t* threads = (pthread_t*)malloc((n/2) * sizeof(pthread_t));
  ThreadArgs* thread_args = (ThreadArgs*)malloc((n/2 )* sizeof(ThreadArgs));
    
    
  for(int i =0; i < n/2; i ++){
    thread_args[i].size = n;
    thread_args[i].thread_id = i;
    thread_args[i].vector = vector;
    pthread_create(&threads[i], NULL, multiplica, (void*)&thread_args[i]);
  }

  for(int i=0; i < n/2; i++){
    pthread_join(threads[i], NULL);
  }

  
  free(vector);
  free(threads);
  free(thread_args);
  }
  
  else{
    return 1;
  }

  return 0;
}