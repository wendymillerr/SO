#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
using namespace std;

void fazerSoma(int A, int B, int mem_shared_id);
void fazerMultiplicacao(int a, int b, int mem_shared_id);
int calcularResultado(int mem_shared_id);


int main() {

  int filho1, filho2, pid, i;
  int *mem_shared;
  int a = 0, b = 0;
  cin >> a >> b;
  
  

  int mem_shared_id = shmget(IPC_PRIVATE, sizeof(int) * 2, IPC_CREAT | 0666);

  filho1 = fork();
  if(filho1 == 0){
    fazerSoma(a, b, mem_shared_id);
    return 0;
  }

   waitpid(filho1, NULL, 0);

  filho2 = fork();
  if(filho2 == 0){
    fazerMultiplicacao( a,  b, mem_shared_id);
    return 0;
  }

   waitpid(filho2, NULL, 0);

  int resultado = calcularResultado(mem_shared_id);
  printf("RESULTADO: %d\n", resultado);

  
  shmctl(mem_shared_id, IPC_RMID, NULL);
  return 0;
}

  void fazerSoma(int A, int B, int mem_shared_id){
    int* resultado_compartilhado = (int*)shmat(mem_shared_id, NULL, 0);
    int result = A + B;
    resultado_compartilhado[0] = result;
    
     printf("FILHO 1: %d + %d = %d\n", A, B, result);
    shmdt(resultado_compartilhado);
  }

  void fazerMultiplicacao(int a, int b, int mem_shared_id){
    int* resultado_compartilhado = (int*)shmat(mem_shared_id, NULL, 0);
    int resultado = a * b;
    resultado_compartilhado[1] = resultado;
    printf("FILHO 2: %d * %d = %d\n", a, b, resultado);
    shmdt(resultado_compartilhado);

  }

   int calcularResultado(int mem_shared_id){
    int* resultado_compartilhado = (int*)shmat(mem_shared_id, NULL, 0);
     
  	/** Receber resultados dos filhos*/  	
    int filho1 = resultado_compartilhado[0];
    int filho2 = resultado_compartilhado[1];

     
    int resultado = filho1 + filho2;
    printf("PAI: %d + %d = %d\n", filho1, filho2, resultado);

    shmdt(resultado_compartilhado);

    return resultado;
  }
  

  
