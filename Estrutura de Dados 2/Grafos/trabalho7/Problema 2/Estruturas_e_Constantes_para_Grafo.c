/**
 *    UNIVERIDADE FEDERAL DE MATO GROSSO     UFMT-CUA.    07.08.14
 *    TRABALHO VI    GRAFOS                  ESTRUTURA DE DADOS II.
 *    DOCENTE        IVAIRTON M. SANTOS
 *    DISCENTE       GIOVANA HIROMI TANITA   201211722002
 *
 *    [ ARQUIVO ]    Estruturas_e_Constantes_para_Grafo.c
 *
 *        Este arquivo contém as biliotecas, constantes e estruturas de dados
 *    necessárias para armazenar as informações, dos grafos. São estas:
 *
 *    ( i   ) Biblioteca de entrada e saída.
 *    ( ii  ) Biblioteca de manipulação de string.
 *    ( iii ) Estrutura que armazena os dados de cada nodo da rede de computadores.
 *    ( iv  ) Estrutura que armazena os dados do grafo.
 *    ( v   ) Estrutura que armazena o menor caminho.
 *
 *                                                                                            Love&Care
 *                                                                                           7DOLL's CODE
 **/

# include <stdio.h>                /** Funções de entrada e saída, printf, scanf, etc. **/
# include <string.h>               /** Usa a função strcpy para copiar a string nome. **/
# include <stdlib.h>
# include <ctype.h>
//s# include <conio.h>
# define N 99                      /** Constante que define o tamanho do vetor e matriz do grafo. **/
# define infinito 9999             /** Constante "infinito" usado no algoritmo de Dijkstra **/

typedef struct nodo {              /** Estrutura com os atributos de cada nodo. **/
   char letra;                     /** armazena a letra do nodo, ex.: a, b, c, etc. **/
   char nome[ 1111 ];              /** Armazena o nome do nodo, ex.: COMP1. **/
   int posicao;                    /** Armazena a posição em que estará este nodo no vetor, letra - 97, seguindo a tabela ASCII **/
} tipo_nodo ;

typedef struct grafo {              /** Estrutura de grafo utilizando o método de matriz de adjacência. **/
   tipo_nodo vetor[ N ];            /** Vetor do tipo_nodo, guarda todos os vértices que são inseridos no grafo **/
   int matriz_adjacencia[ N ][ N ]; /** Matriz de adjacencia, guarda as arestas e seu respectivo tempo de retardo, usa a "posicao" do tipoNodo como índice **/
   int contador_vertices;           /** Conta quantos vértices foram inseridos no grafo **/
} tipo_grafo ;

typedef struct tipo_distancias {    /** Estrutura que vai armazenar o menor caminho de um nodo para os outros. **/
    int distancia;                  /** Distancia do vértice que conecta o nodo da "posicao_anterior" e "posicao_posterior". **/
    int posicao_anterior;           /** Guarda o número da primeira aresta ligada pelo vértice de peso "distancia". **/
    int posicao_posterior;          /** Guarda o número da segunda aresta ligada pelo vértice de peso "distancia" **/
    int check;                      /** Flag que determina se o nodo faz parte do caminho mínimo entre um nodo X e Y, usado na Função 3. **/
} tipo_distancias;
