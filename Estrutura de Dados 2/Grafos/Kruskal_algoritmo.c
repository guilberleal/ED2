/**
 * Aluno: Alex Matos Iuasse
 * Algoritmo de gafos de Kruskal
 **/


#include <stdio.h>
#include <stdlib.h>

#define N 99

struct nodo {
  char letra;
  int posicao; //letra - 97
};
typedef nodo tipo_nodo;

struct grafo {
  tipo_nodo vetor [N];
  int matriz_adjacencia [N][N];
  int contador_vertices;
};
typedef grafo tipo_grafo;

struct conjunto {
  char nome_conjunto;
  tipo_nodo vetor [N];
};
typedef conjunto tipo_conjunto;

/*
void inserir_vertice();
void inserir_aresta();
int busca_binaria();
void algoritmo_kruskal();
void cria_conjunto ();
void uniao ();
void busca_conjunto ();
void Kruskal ();
*/

void inserir_vertice ( tipo_grafo *grafo, tipo_nodo nodo );
void inserir_aresta ( tipo_grafo *grafo, char vertice_1, char vertice_2, double retardo );
int busca_binaria ( tipo_grafo *grafo, char vertice_buscar );
void cria_conjunto ( tipo_grafo *grafo );
void uniao (  );
void busca_conjunto (  );
void Kruskal ( tipo_grafo *grafo, tipo_grafo *geradora_minima );