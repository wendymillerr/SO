#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
  pid_t PID[5] = {-1, -1, -1, -1, -1};

  PID[0] = fork();
  if(PID[0] < 0){
    cout << "Erro ao gerar filho[0]\n";
    return 1;
  }
  
  if(PID[0] > 0){
    cout << "Processo pai rodando\n";
    PID[1] = fork();
      if(PID[1] < 0){
        cout << "Erro ao criar filho[1]\n";
        return 1;
      }else{
        cout << "Filho[1] criado com sucesso.\n";
      }
    
  }else if(PID[0] == 0){
    cout << "processo filho[0] rodando...\n";
    cout << "processo filho[0] criando filho[2]\n";
    PID[2] = fork();
    if(PID[2] < 0){
        cout << "Erro ao criar filho[2]\n";
        return 1;
  } else{
      cout << "filho[2] criado com sucesso.\n";
  }
}

}