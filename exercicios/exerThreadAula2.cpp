#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;
 
#define NTHREADS 5

void* hello_world(void *tid){
  cout << "Hell world. esta é a thread " << (int)(ssize_t)tid << endl<<endl;
  sleep(((int)(size_t)tid+1)*2);//proporcional ao numero da thread
  pthread_exit(NULL);
}

int main() {

  pthread_t threads[NTHREADS];
  int status, i;
  void *thread_return;//guardar valor de retorno das threads

  for(i =0; i < NTHREADS ; i++){
    cout << "Processo principal criando thread #" << i << endl;
  status = pthread_create(&threads[i], NULL, hello_world, (void*) (size_t)i);

    if(status != 0){
      cout << "Erro na criação de thread. Codigo de Erro: " << status << endl;
    return 1;
    }
  
  }

  for(i=0; i < NTHREADS; i++){
    cout << "esperando Thread["<<i<<"] terminar\n";
    pthread_join(threads[i], &thread_return);
    cout<< "Thread["<<i<<"] finalizada\n";
  }

cout << "Processo vai finalizar.\n";

  
}