/**
 * Alunos: Alex Matos Iuasse, Giovana Hiromi Tanita
 * Grafos Trabalho 7 Problema 1
 * Professor: Ivairton
 * Estrutura de Dados 2
 * Data: Agosto 21, 2014
 **/

#include <stdio.h>
#include <stdlib.h>

#define TAB 8 /** tamanho de um tabuleiro **/

#include "Funcoes_Auxiliares_para_Grafo.c"

/**
 * void inserir_vertice ( tipo_grafo *grafo, tipo_nodo novo_nodo );
 * void inserir_aresta ( tipo_grafo *grafo, char vertice_1, char vertice_2, int tempo_de_retardo  );
 * int busca_binaria ( tipo_grafo *grafo, char a_buscar );
 **/

/** Protótipos **/
void ler_entrada ( tipo_grafo *grafo, tipo_grafo *solucao );
void print ( tipo_grafo *grafo );
void busca ( tipo_grafo *grafo, int *pos, int *pos1, int o );
int validarPos_cavalo ( tipo_grafo *grafo, tipo_grafo *solucao, int x, int y, int ret );
int mover_cavalo ( tipo_grafo *grafo, tipo_grafo *solucao, int x, int y, int ret, int *xa, int *ya );

/** Função para ler entrada de um arquivo de texto **/
void ler_entrada ( tipo_grafo *grafo, tipo_grafo *solucao ) {
  
  FILE *entrada;
  tipo_nodo vetor;
  char nome[111];
  char letra, letra1;
  int peso;
  
  entrada = fopen ("problema1_entrada1","rt");
  while ( !feof (entrada) ) {
    fscanf (entrada,"%s %c\n",nome,&letra);
    strcpy (vetor.nome, nome);
    vetor.letra = letra;
    vetor.posicao = letra - 97;
    inserir_vertice ( grafo,vetor );
    inserir_vertice ( solucao, vetor );
  }
  fclose (entrada);
  
  entrada = fopen ("problema1_entrada","rt");
  while ( !feof (entrada) ) {
    fscanf (entrada,"%c %c %i\n",&letra,&letra1,&peso);
    inserir_aresta ( grafo,letra,letra1,peso );
  }
  fclose (entrada);
  
}

/** Função para efetuar o debug visual **/
void print ( tipo_grafo *grafo ) {
  int i,j;
  
  for ( i = 0; i < TAB; i ++ ) {
    printf("\n");
    for ( j = 0; j < TAB; j ++ ) {
      if ( grafo->matriz_adjacencia[i][j] != infinito )
	printf ("[ %i ]",grafo->matriz_adjacencia[i][j]);
      else
	printf ("[   ]");
    }
  }
  
}

/** Função capaz de retornar a posição de inicio e de fim **/
void busca ( tipo_grafo *grafo, int *pos, int *pos1, int o ) {
  int i,j,k = 0;
  /** i = x j = y **/
  for ( i = 0; i < 8; i ++ ) {
    for ( j = 0; j < 8; j ++ ) {
      /** Procura a existencia de um numero na matriz de matriz_adjacencia **/
      if ( grafo->matriz_adjacencia[i][j] == o ){
	/** retorna com ponteiro a posição **/
	*pos = i;
	*pos1 = j;
	k = 1;
	break;
      }
    }
    if ( k == 1) break;
  }
  /** indicar que não existe mais posições validas **/
  if ( k == 0 ) {
  *pos = 8;
  *pos1 = 8;
  }
}

/** Função para retornar se uma posição é valida, 1 caso sim e 0 caso mão **/
int validarPos_cavalo ( tipo_grafo *grafo, tipo_grafo *solucao, int x, int y, int ret ) {
  
  /** Tratando posições negativas e posições maiores que as permitidas **/
  if ( ( x >= 0 && y < TAB ) && ( x < TAB && y >= 0 ) ) {
    /** Se a posição estiver livre em grafo e solucao, então coloca-se uma relação de aresta em solucao **/
    if ( grafo->matriz_adjacencia [x][y] == infinito && solucao->matriz_adjacencia [x][y] == infinito ) {
      //printf ("Aresta inserida em : [ %i ] [ %i ]\n",x,y);//debug
      inserir_aresta ( solucao, (char) x+97, (char) y+97, 1 );
      return 1;
      /** caso a posição não seja valida, manda ret para proximo movimento **/
    } else { return 0; }
    /** caso a posição não seja valida, manda ret para proximo movimento **/
  } else { return 0; }
}

/** Função que recebera uma posição de inicio, a partir dela, sera feito calculos de movimento em L **/
int mover_cavalo ( tipo_grafo *grafo, tipo_grafo *solucao, int x, int y, int ret, int *xa, int *ya ) {
  
    int retorno;
    if ( ret <= 7 ) {
      switch ( ret ) {
	case 0:
	  //pra cima esquerda
	  retorno = validarPos_cavalo ( grafo, solucao, x - 2, y - 1, ret );
	  break;
	case 1:
	  //pra cima direita
	  retorno = validarPos_cavalo ( grafo, solucao, x - 2, y + 1, ret );
	  break;
	case 2:
	  //pro lado esquerda para cima
	  retorno = validarPos_cavalo ( grafo, solucao, x + 1, y - 2, ret );
	  break;
	case 3:
	  //pro lado esquerda para baixo
	  retorno = validarPos_cavalo ( grafo, solucao, x - 1, y - 2, ret );
	  break;
	case 4:
	  //pro lado direita para cima
	  retorno = validarPos_cavalo ( grafo, solucao, x - 1, y + 2, ret );
	  break;
	case 5:
	  //pro lado direita para baixo
	  retorno = validarPos_cavalo ( grafo, solucao, x + 1, y + 2, ret );
	  break;
	case 6:
	  //pra baixo esquerda
	  retorno = validarPos_cavalo ( grafo, solucao, x + 2, y - 1, ret );
	  break;
	case 7:
	  //pra baixo direita
	  retorno = validarPos_cavalo ( grafo, solucao, x + 2, y + 1, ret );
	  break;
      }
      /** verifica retorno se 1 quer dizer que foi adicionado uma aresta **/
      if ( retorno == 1 ) {
	*xa = x;
	*ya = y;
	mover_cavalo ( grafo, solucao, x, y, 0, xa, ya );
	/** se retorno for 0, quer dizer que a posição não e valida, entado faz-se a chamada para proxima posição **/
      } else if ( retorno == 0 ) {
	ret = ret + 1;
	x = *xa;
	y = *ya;
	mover_cavalo ( grafo, solucao, x, y, ret, xa, ya );
      }
    } else {
      busca ( solucao, &x, &y, 1 );
      /** Se as posições forem diferentes das validas, quer dizer que nao há mais posição valida **/
      if ( ( x >= 0 && y < TAB ) && ( x < TAB && y >= 0 ) )  {
	//printf ("Par ordenado a ser calculado [ %i ] [ %i ]\n",x,y);
	solucao->matriz_adjacencia [x][y] = 2;
	*xa = x; 
	*ya = y;
	mover_cavalo ( grafo, solucao, x, y, 0, xa, ya );
	/** Fecha a função **/
      } else { return 0; }
    }
  
}

/** Busca em largura **/
void busca_largura ( tipo_grafo *grafo, char vertice ) {
  
  for ( 
  
}

/**
 * Atenção: 
 * 	A relação de posição inicial deve ser colocada como 2
 **/


/** Função principal que deve ser colocada em á parte somente para testes **/
int main (int argc, char **argv) {
  
  /** Grafo constituido pelas relações de posições validas ou não **/
  tipo_grafo grafo;
  /** Grafo constituido pelas posições validas do cavalo **/
  tipo_grafo solucao;
  
  int i, j, pos,pos1,ret = 0;
  
  /** inicializando os grafos **/
  for ( i = 0; i < TAB; i ++ ) {
    for ( j = 0; j < TAB; j ++ ) {
      grafo.matriz_adjacencia [i][j] = infinito;
      solucao.matriz_adjacencia [i][j] = infinito;
    }
  }
  /** inicializando o contador de vertices **/
  grafo.contador_vertices = 0;
  solucao.contador_vertices = 0;
  /** lendo entrada de um arquivo **/
  ler_entrada ( &grafo, &solucao );
  /** realizando a busca da posição inicial **/
  busca ( &grafo, &pos, &pos1, 2 );
  /** definindo essa posição inicial como ja calculada **/
  solucao.matriz_adjacencia [pos][pos1] = 2;
  /** chamando a função para construir um grafo com os movimentos em L do cavalo **/
  mover_cavalo ( &grafo, &solucao, pos, pos1, ret, &pos, &pos1 );
  print ( &solucao );
  printf ("\n");
  /** chamar uma função de achar menor caminho **/
  //CHAMAR AQUIIIIIIIIIIIIII IT'S OVER 8000
  
  return 0;
}