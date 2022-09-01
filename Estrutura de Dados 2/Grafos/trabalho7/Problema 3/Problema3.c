/**
 * Alunos: Alex Matos Iuasse, Giovana Hiromi Tanita
 * Grafos Trabalho 7 Problema 3
 * Professor: Ivairton
 * Estrutura de Dados 2
 * Data: Agosto 21, 2014
 **/

#include <stdio.h>
#include <stdlib.h>

#include "Funcoes_Auxiliares_para_Grafo.c"

/**
 * void inserir_vertice ( tipo_grafo *grafo, tipo_nodo novo_nodo );
 * void inserir_aresta ( tipo_grafo *grafo, char vertice_1, char vertice_2, int tempo_de_retardo  );
 * int busca_binaria ( tipo_grafo *grafo, char a_buscar );
 **/

/** Protótipos **/
void ler_entrada ( tipo_grafo *grafo );
void print ( tipo_grafo *grafo );

/** Função para ler entrada de um arquivo de texto **/
void ler_entrada ( tipo_grafo *grafo ) {
  
  FILE *entrada;
  tipo_nodo vetor;
  char nome[111];
  char letra, letra1;
  int peso;
  
  entrada = fopen ("problema3_entrada","rt");
  while ( !feof (entrada) ) {
    fscanf (entrada,"%s %c\n",nome,&letra);
    strcpy (vetor.nome, nome);
    vetor.letra = letra;
    vetor.posicao = letra - 97;
    inserir_vertice ( grafo,vetor );
  }
  fclose (entrada);
  
  entrada = fopen ("problema3_entrada1","rt");
  while ( !feof (entrada) ) {
    fscanf (entrada,"%c %c %i\n",&letra,&letra1,&peso);
    inserir_aresta ( grafo,letra,letra1,peso );
  }
  fclose (entrada);
  
}

/** Função para efetuar o debug visual **/
void print ( tipo_grafo *grafo ) {
  int i,j;
  
  for ( i = 0; i < grafo->contador_vertices; i ++ ) {
    printf("\n");
    for ( j = 0; j < grafo->contador_vertices; j ++ ) {
      printf ("[ %i ]",grafo->matriz_adjacencia[i][j]);
    }
  }
  
}

void menor_distancia ( tipo_grafo * grafo, tipo_nodo nodo_inicial, tipo_nodo nodo_final ) {
   int i;
   tipo_distancias distancias[ N ];

   algoritmo_de_dijkstra ( nodo_final.posicao, nodo_inicial.posicao, grafo->matriz_adjacencia, distancias );

   for ( i=0; i<N; i++ ) distancias[i].check = 0;

   i = nodo_final.posicao;
   while ( i!=nodo_inicial.posicao ) {
        distancias[i].check = 1;
        i = distancias[i].posicao_anterior;
   }
   distancias[nodo_inicial.posicao].check = 1;

   printf ( "O caminho mínimo tem custo = %d ms\nO caminho é: ", distancias[ nodo_final.posicao ].distancia );

   for ( i=nodo_inicial.posicao ; i <= nodo_final.posicao ; i++ )
      if ( i != nodo_inicial.posicao ) {
         if ( distancias[ i ].distancia != infinito )
            if ( distancias[i].check == 1 ) {
	      if ( i != nodo_final.posicao ){
		printf( "( %s, %s )(%dms), ", grafo->vetor[ distancias[ i ].posicao_anterior ].nome, grafo->vetor[ distancias[ i ].posicao_posterior ].nome, distancias[ i ].distancia );
	      }else printf( "( %s, %s )(%dms)\n\n", grafo->vetor[ distancias[ i ].posicao_anterior ].nome, grafo->vetor[ distancias[ i ].posicao_posterior ].nome, distancias[ i ].distancia );
	    }
      }
}

/** Função para determinar um possivel fluxo maximo **/
int fluxo ( tipo_grafo grafo, int pos ) {
  int i, max = 0;
  
  for ( i = 0; i < pos; i ++ ) {
    if ( grafo.matriz_adjacencia[i][pos] != infinito ){
      max += grafo.matriz_adjacencia[i][pos];
    }
  }
  return max;
}

/** Função para achar o Fluxo maximo em um grafo **/
void fluxo_maximo ( tipo_grafo grafo, int s, int t ) {
  
  int i,j,max;
  
  /** grafo residual **/
   tipo_grafo rgrafo; 
  
  /** inicializando fluxo do grafo residual **/
   for ( i = 0; i < grafo.contador_vertices; i ++ )
     for ( j = 0; j < grafo.contador_vertices; j ++ )
       rgrafo.matriz_adjacencia[i][j] = 0;
     
  /** achar um caminho de s ate t **/
  
  /** achar fluxo maximo incidente em t **/
  max = fluxo ( grafo, t );
  /** injetar esse fluxo maximo no grafo residual **/
  
  /** achar um caminho possivel para esse fluxo, caso não encontrado, diminuir fluxo **/

}

/** Função principal que deve ser colocada em á parte somente para testes **/
int main (int argc, char **argv) {
  
  tipo_grafo grafo;
  
  int i, j;
  
  for ( i = 0; i < N; i ++ ) {
    for ( j = 0; j < N; j ++ ) {
      grafo.matriz_adjacencia [i][j] = infinito;
    }
  }
  grafo.contador_vertices = 0;
  
  ler_entrada ( &grafo );
  menor_distancia ( &grafo, grafo.vetor[0], grafo.vetor[12] );
  
  return 0;
}