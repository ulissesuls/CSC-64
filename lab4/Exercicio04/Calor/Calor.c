#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // memcpy
#define max(a,b) ((a)<(b))?(b):(a)
#define min(a,b) ((a)<(b))?(a):(b)

double wall_time(void);

// inicializa malha

void Init(const int n, float b[n+2][n+2]) {
  for (int i=0; i<n+2; i++)
    for (int j=0; j<n+2; j++)
      b[i][j]=0.0f;
  for (int j=0; j<n+2; j++)
    b[0][j]=10.0f;
}

// resolve a equacao de calor com codigo escalar

void CalorEscalar(const int nIter, const int n, float b[n+2][n+2]) {
  for (int iIter=0; iIter<nIter; iIter++) 
    for (int i=1; i<=n; i++) 
      for (int j=1; j<=n; j++) 
	b[i][j]=0.25*(b[i-1][j] + b[i][j-1]+
		      b[i][j+1] + b[i+1][j]);
}


void CalorVetorial(const int nIter, const int n, float b[n+2][n+2]) {
//   for (int iIter=0; iIter<nIter; iIter++) 
//     for (int i=1; i<=n; i++) 
//       for (int j=1; j<=n; j++) 
// 	      b[i][j] = 0.25 * (b[i-1][j] + b[i][j-1] + b[i][j+1] + b[i+1][j]);

/*================================================================================================================*/
  // O objetivo é percorrer as diagonais, que são independentes entre si, e cujos cálculos podem ser vetorizados.
  // Diagonais somam k = i + j (com i,j em [1...n])
  // k varia de 2 até 2n; em cada k, os pontos (i, j=k-i) são independentes.
  for (int iter = 0; iter < nIter; ++iter) {
    for (int k = 2; k <= 2*n; ++k) {
      int i_ini = max(1, k - n);
      int i_fim = min(n, k - 1);

      // Cada iteração do laço abaixo é independente e pode ser vetorizado
      // Usa Norte e Oeste já atualizados (k-1),
      // e Leste e Sul ainda "antigos" (k+1).
      // #pragma omp simd  // Orienta o compilador, mas pode ser dispensado
      for (int i = i_ini; i <= i_fim; ++i) {
        int j = k - i; // recupera a coluna correspondente ao ponto da diagonal atual (1...n)
        b[i][j] = 0.25f * (b[i-1][j]    //vizinho Norte (já atualizado em k-1)
                         + b[i][j-1]    //vizinho Oeste (já atualizado em k-1)
                         + b[i][j+1]    //vizinho Leste (será atualizado em k+1)
                         + b[i+1][j]);  //vizinho Sul (será atualizado em k+1)
      }
    }
  }
}

// imprime a malha (para debug)

void Dump(const int n, float b[n+2][n+2]) {
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=n; j++)
      printf("%6.2f ",b[i][j]);
    printf("\n");
  }
}

// maior diferenca relativa entre duas malhas

float MaxDif(const int n, float a[n+2][n+2],  float b[n+2][n+2]){
  float res=0.0;
  for (int i=1; i<=n; i++)
    for (int j=1; j<=n; j++)
      res=fmaxf(res,fabsf(a[i][j]-b[i][j])/fabsf(a[i][j]));
  return (res);
}

void main(){
  //const int n=500;
  const int n=10000;
  const int nIter=100;
  float a[n+2][n+2];
  float b[n+2][n+2];

  // inicializa a malha para solucao escalar

  Init(n,a);

  // resolve a equacao de calor com codigo escalar

  double tEscalar=-wall_time();
  CalorEscalar(nIter, n,a);
  tEscalar+=wall_time();

  // inicializa a malha para solucao vetorial

  Init(n,b);

  // resolve a equacao de calor com codigo vetorial

  double tVetorial=-wall_time();
  CalorVetorial(nIter, n, b);
  tVetorial+=wall_time();

  // diferenca maxima e tempos de execucao

  printf("MaxDif=%e para n=%d\n", MaxDif(n, a, b), n);
  printf("tempo escalar =%lf\n",tEscalar);
  printf("tempo vetorial=%lf\n",tVetorial);

  // escreve o resultado (para debug)

  //  Dump(n,a);
  //  Dump(n,b);
  exit(0);
}

// GEP.c
