/**
 * Alunos: Alex Matos Iuasse, Giovana Hiromi Tanita
 * Grafos Trabalho 7 Problema 2
 * Professor: Ivairton
 * Estrutura de Dados 2
 * Data: Agosto 21, 2014
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coloracao_grafo.c"

/**
 * void inserir_vertice ( tipo_grafo *grafo, tipo_nodo novo_nodo );
 * void inserir_aresta ( tipo_grafo *grafo, char vertice_1, char vertice_2, int tempo_de_retardo  );
 * int busca_binaria ( tipo_grafo *grafo, char a_buscar );
 **/

/** Ler uma entrada de um arquivo **/
void ler_entrada ( tipo_grafo *grafo ) {
  FILE *entrada;
  tipo_nodo vetor;
  char nome[111];
  char letra, letra1;
  
  entrada = fopen ("problema2_entrada","rt");
  while ( !feof (entrada) ) {
    fscanf (entrada,"%s %c\n",nome,&letra);
    strcpy (vetor.nome, nome);
    vetor.letra = letra;
    vetor.posicao = letra - 97;
    inserir_vertice ( grafo,vetor );
  }
  fclose (entrada);
  
  entrada = fopen ("problema2_relacao","rt");
  while ( !feof (entrada) ) {
    fscanf (entrada,"%c %c\n",&letra,&letra1);
    inserir_aresta ( grafo,letra,letra1,1 );
  }
  fclose (entrada);
  
}

/** Função separar turma para salas **/
void turma_salas ( tipo_grafo *grafo ) {
  algoritmo_coloracao ( grafo );
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
  
  ler_entrada (&grafo);
  turma_salas (&grafo);
  
  return 0;
}