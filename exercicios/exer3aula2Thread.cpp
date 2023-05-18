#include <iostream>
#include <unistd.h>
#include  <pthread.h>
#define NTHREADS 2
using namespace std;


pid_t pid;
void* hello_world(void *tid){
  cout<< "Hello world. Esta é a thread[" << (int)(size_t)tid <<"]\n";
  pthread_exit(NULL);
}



int main() {
  pthread_t threads[NTHREADS];
  int status, i, retorno;
  void *thread_return;

  pid = fork();//cópia da região de dados e de texto para o processo filho

  //filho criará suas próprias threads
  for(i =0; i < NTHREADS; i++){
    cout << "Processo [" << getpid() <<"] criando thread: "<<i<<endl;
    status = pthread_create(&threads[i], NULL, hello_world, (void*)(size_t)i);

    if(status != 0){
      cout << "Erro ao criar a thread: "<<i<<endl;
    }
    
  }

  for(i =0; i < NTHREADS; i++){
    cout << "Processo[" << getpid() << "] esperando thread " << i << " finalizar\n";
    pthread_join(threads[i], &thread_return);
    cout << "thread[" << i << "] finalizada\n";
  }


}
