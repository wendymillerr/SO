#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;
#define NTHREADS 5
//Exercício que mostra como fazer com que a thread posterior funcione após a outra 

pthread_t threads[NTHREADS];
int status, i;
void *thread_return;

int soma = 0; //Como é uma variável global, todas as threads tem acesso, não é copiado

void* hello_world(void *tid){
  if(((int)(size_t)tid) > 0){
    pthread_join(threads[(size_t)tid-1], &thread_return );
    cout << "Esta é a thread[" << (int)(size_t)tid << "]. A thread [" << (int)(size_t)tid-1<<"] terminou \n";
  }else{
    cout << "Esta é a primeira thread.\n";
  }

  soma = soma +1;
  cout << "O valor da soma é: " << soma << endl;
  sleep(1);
  pthread_exit(NULL);
}


int main() {

  for(i = 0; i < NTHREADS; i++){
    cout << "Criando a thread  " <<  i << endl;
    status = pthread_create(&threads[i], NULL, hello_world, (void*) (size_t)i);
    if(status != 0){
      cout << "Erro na criação da thread " <<  i << endl;
      return 1;
    }
  }

  cout <<"Esperando Thread [" << i-1 << "] finalizar\n\n";
  pthread_join(threads[i-1], &thread_return);
  cout<<"Thread [" << i-1 << "] finalizou\n";

  cout << "Processo pai vai finalizar a soma = " << soma<<endl;


}