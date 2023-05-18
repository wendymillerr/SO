#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

#define NTHREADS 2
pid_t pid;


void* hello_world(void* tid){
  pid_t pid;
  pid = fork();//Aqui está sendo criado um processo que copia APENAS o código da thread em questão: thread[tid]. NÃO É COPIADO O PROCESSO PRINCIPAL
  cout << "Processo[" << getpid() << "] Hello world. esta é a thread[" << (int)(size_t)tid <<"]\n";

  sleep(((int)(size_t)tid+1)*2);
  pthread_exit(NULL);
  
}

int main() {
  pthread_t threads[NTHREADS];
  void* thread_return;
  int status, i, retorno;
  
  for(i =0; i < NTHREADS; i++){
    cout << "Processo[" << getpid() << "] criando thread = "<<i<<endl;
    status = pthread_create(&threads[i], NULL, hello_world, (void*)(size_t)i);
    if(status!=0){
      cout << "Erro ao criar a thread[" << i << "] \n";
      return 1;
    }
    
  }

  for(i = 0; i < NTHREADS; i++){
    cout << "Processo[" << getpid() << "] Esperando thread[" << i << "] finalizar\n";
    pthread_join(threads[i], &thread_return);
    cout << "Thread " << i << " finalizada\n";
  }




}