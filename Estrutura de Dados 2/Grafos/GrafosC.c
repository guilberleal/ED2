/**
 * grafos direcionados
 * autor: alex matos iuasse
 * estrutura de dados 2
 **/
#include <stdio.h>
#include <stdlib.h>

#define	N 10

struct vertice {
  char nome;
  int peso;
  int posicao; //letra -97, obs: a - 97 = 0
};
typedef struct vertice tipo_vertice;

struct grafo {
  tipo_vertice vertice [N];
  tipo_vertice matriz_adjacencia [N] [N]; 
  int contador;
};
typedef struct grafo tipo_grafo;

void pega_vertice (tipo_grafo *grafo, tipo_vertice vetor[]) {
  int i,j;
  for (i = 0; i < N; i ++) {
    grafo->vertice[i] = vetor[i];
    for ( j = 0; j < N; j ++ ) {
      grafo->matriz_adjacencia[i][j] = vetor[i];
    }
  }
}

void imprimir (tipo_grafo grafo) {
  int i,j;
  for ( i = 0; i < N; i ++ ) {
      printf("[ %c ] ",grafo.vertice[i].nome);
  }
  
  for (i = 0; i < N; i ++) {
      printf("\n");
    for (j = 0; j < N; j ++ ){
	printf ("[ %i ] ",(grafo.matriz_adjacencia[i][j]).peso);
    }
  }
  printf("\n");
}

void inserir_grafo ( tipo_grafo *grafo, char vertice1, char vertice2, int peso  ) {
  (grafo->matriz_adjacencia[(int)vertice1-97][(int)vertice2-97]).peso = peso;
  (grafo->matriz_adjacencia[(int)vertice2-97][(int)vertice1-97]).peso = peso;
}

int main (int argc, char **argv) {
  
  tipo_grafo grafo;
  tipo_vertice vetor [N];
  int i,j = 97;
  for ( i = 0; i < N; i ++ ) {
    vetor[i].nome = j+i;
    vetor[i].peso = -1;
    vetor[i].posicao = i;
  }
  
  pega_vertice(&grafo,vetor);
  inserir_grafo (&grafo,'a','b',10);
  inserir_grafo (&grafo,'a','c',50);
  imprimir(grafo);
  
  return 0;
}