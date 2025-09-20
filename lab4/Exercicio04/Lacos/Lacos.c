#include <stdio.h>
#include <stdlib.h>

void Init(float* restrict x, float* restrict y, float* restrict z, float* restrict d, int n) {
  for(int i=0; i<n; i+=2) {
    x[i]=(float)(i+1);
    x[i+1]=-(float)(i+1);
    y[i]=(float)(i-1);
    y[i+1]=-(float)(i-1);
    z[i]=-(float)(i+2);
    z[i+1]=(float)(i+2);
    d[i]=0.0f;
    d[i+1]=0.0f;
  }
  x[n]=(float)(n+100);
}

float Soma(const int iIni, const int iFim, float* restrict vet) {
  float s=0;
  for (int i=iIni; i<=iFim; i++) s += vet[i];
  return(s);
}

void Laco1(float* restrict x, float* restrict y, float* restrict z, float* restrict d, int n) {
  // Eliminamos as dependências entre iterações da função separando o laço em dois passos.
  // O primeiro passo calcula x e z, que são independentes entre si.
  // O segundo passo calcula d, que depende de x, mas agora a leitura de x[i+1] é de um vetor já pronto.
  // Assim, cada passo pode ser vetorizado.
  
  for(int i=1; i<n; ++i) {    // Passo 1: independente
    x[i]=y[i]+z[i];
    // d[i]=x[i+1]+1;
    // z[i]=d[i];
  }

  for(int i=1; i<n; ++i) {    // Passo 2: independente
    float di = x[i+1] + 1.0f; // leitura de x[i+1] agora é de um vetor pronto
    d[i] = di;
    z[i] = di;
  }
}

void Laco2(float* restrict x, float* restrict y, int n) {
  float t, s;
  t=x[0];
  for(int i=1; i<n; ++i) {
    y[i] = 0.5f * (x[i] + x[i-1]); // média de vizinhos, algebricamente equivalente ao original, mas sem dependência
    // s=x[i];
    // y[i]=(s+t)/2.0f;
    // t=s;
  }
}

void main() {
  const int n=32;

  float* restrict x;
  x=(float*)malloc((n+1)*sizeof(float));

  float* restrict y;
  y=(float*)malloc(n*sizeof(float));

  float* restrict z;
  z=(float*)malloc(n*sizeof(float));

  float* restrict d;
  d=(float*)malloc(n*sizeof(float));

  Init(x, y, z, d, n);

  printf("Antes Laco1: ");
  printf("x=%6.2f; ",Soma(0,n,x));
  printf("y=%6.2f; ",Soma(0,n-1,y));
  printf("z=%6.2f; ",Soma(0,n-1,z));
  printf("d=%6.2f\n",Soma(0,n-1,d));

  Laco1(x,y,z,d,n);

  printf("Apos  Laco1: ");
  printf("x=%6.2f; ",Soma(0,n,x));
  printf("y=%6.2f; ",Soma(0,n-1,y));
  printf("z=%6.2f; ",Soma(0,n-1,z));
  printf("d=%6.2f\n",Soma(0,n-1,d));

  Init(x, y, z, d, n);

  printf("\nAntes Laco2: ");
  printf("x=%6.2f; ",Soma(0,n,x));
  printf("y=%6.2f;\n",Soma(0,n-1,y));

  Laco2(x,y,n);

  printf("Apos  Laco2: ");
  printf("x=%6.2f; ",Soma(0,n,x));
  printf("y=%6.2f\n",Soma(0,n-1,y));
  exit(0);
}
