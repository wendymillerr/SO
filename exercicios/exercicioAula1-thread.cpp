#include <iostream>
#include <pthread.h>

#include <unistd.h>

using namespace std;

void *hello_world(void *tid){//recebe o valor id: 0
  cout << "Hello world. Esta é uma Thread. " << (int)(size_t)tid << endl; // imprime hello e o numero da thread

  pthread_exit(NULL);//finaliza a execução da thread
}

int main() {

  pthread_t thread;//inteiro
  int status;
  void *thread_return;//ponteiro para void para a função hello_world poder retorna-lo

  cout << "Processo principal criando thread\n\n";
  status = pthread_create(&thread, NULL, hello_world, 0);//ao final da execução, a variavel thread terá o numero da thread
//o verdadeiro id de thread está em &thread
  if(status !=0){
    cout << "Erro na criação. Código de Erro: " << status << endl;
    return 1;
  }
  
  cout << "Esperando thread finalizar....\n";
  pthread_join(thread, &thread_return);//função a qual voce diz qual a thread será esperado finalizar
  cout << "Thread finalizada.";

  return 0;

}