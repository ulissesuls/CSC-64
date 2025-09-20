#include <stdio.h>
#include <stdlib.h>

double wall_time(void);
void InitTabul(int*, int*, int);
void UmaVida(int*, int*, int);


int main() {
#define POWMIN 3
#define POWMAX 9
  int pow;
  int i;
  int tam;
  int* tabulIn;
  int* tabulOut;
  int numThreads, numProcs;
  char msg[9];
  double t1, t2;
  
  // para todos os tamanhos do tabuleiro

  for (pow=POWMIN; pow<=POWMAX; pow++){

    tam = 1 << pow;

    // aloca e inicializa tabuleiros
   
    tabulIn  = (int *) malloc ((tam+2)*(tam+2)*sizeof(int));
    tabulOut = (int *) malloc ((tam+2)*(tam+2)*sizeof(int));
    InitTabul(tabulIn, tabulOut, tam);
    
    // mede tempo das
    // iteracoes do Jogo da Vida

    t1 = wall_time();
    for (i=0; i<2*(tam-3); i++) {
      UmaVida(tabulIn, tabulOut, tam);
      UmaVida(tabulOut, tabulIn, tam);
    }
    t2 = wall_time();
    
    printf("tam=%d; tempo comp=%f \n", 
	   tam, t2-t1);
    free(tabulIn);
    free(tabulOut);
  }
  exit(0);    
}
