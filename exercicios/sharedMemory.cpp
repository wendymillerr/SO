#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
using namespace std;


void implementacao_filho1(int *a){
  *a = *a + 1;
  cout << "Executando filho 1: " << getpid() << endl;

}

void implementacao_filho2(int *a){
  *a = *a * 2;
  cout << "Executando filho 2: " << getpid() << endl;
}


int main() {

  int filho1, filho2, pid, status, i;
  int *mem;
  //criando espaço de mem. compartilhado do tamanho de um inteiro
  int valor = shmget(IPC_PRIVATE, sizeof(int) , IPC_CREAT | 0666);

  mem = (int*)shmat(valor, NULL, 0);//ponteiro para região de memoria compartilhada
  if(*mem < 0){//ele colocou sem asterisco
    cout << "Erro na alocação.\n";
    return 0;
  }

  *mem = 5;//escreveu 5 no espaço de memória compartilhado
  cout << "Pai começou (PID:"<< getpid() <<") e o valor do inteiro é: " << *mem << endl;

  filho1 = fork();// vai ter acesso ao espaço de memoria compartilhada cujo o valor é 5
  if(filho1 > 0){
    filho2 = fork();
  }if(filho1 == 0){
    mem = (int *)shmat(valor, NULL, 0);
    sleep(1);
    implementacao_filho1(mem);//passando ponteiro de inteiro para a memoria compartilhada
    cout << "Filho 1 finalizou (PID: " << getpid() << ") e o valor do inteiro é: " << *mem << endl;
    
    if(shmdt(mem) == -1){
      cout << "erro ao liberar espaço\n";
    }else{
      cout << "deu tudo certo\n";
    }
    exit(0);
  }

  if(filho2 > 0){
    cout << "Processo filho de filho 1 rodando..." << endl;
  }if(filho2 == 0){
    mem = (int *)shmat(valor, NULL, 0);
    implementacao_filho2(mem);
    cout << "Filho 2 finalizou (PID=" << getpid() << ") e o valor inteiro é: " << *mem << endl;
    shmdt(mem);
    exit(0);
  }

  for(i =0; i < 2; i++){
    wait(NULL);//esperando que os dois filhos terminem a execução antes do pai
  }

  shmctl(valor, IPC_RMID, NULL);
  cout << "Valor = " << *mem << endl;
  cout << "Pai terminou\n";
  exit(0);
  return 0;
  

}