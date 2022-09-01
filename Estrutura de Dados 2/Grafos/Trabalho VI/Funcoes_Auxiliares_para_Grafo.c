/**
 *    UNIVERIDADE FEDERAL DE MATO GROSSO     UFMT-CUA.    07.08.14
 *    TRABALHO VI    GRAFOS                  ESTRUTURA DE DADOS II.
 *    DOCENTE        IVAIRTON M. SANTOS
 *    DISCENTE       GIOVANA HIROMI TANITA   201211722002
 *
 *    [ ARQUIVO ]    Funcoes_Auxiliares_para_Grafo.c
 *
 *        Este arquivo contém funções auxiliares para a manipulação do grafo,
 *    ou seja, funções que não foram diretamente solicitadas nas especificações do
 *    Trabalho VI mas que são de extrema importância para que as funcionalidades
 *    funcionem de modo correto. São estas:
 *
 *    ( i   ) Função de inserção de um novo vértice.
 *    ( ii  ) Função de inserção de uma nova aresta.
 *    ( iii ) Função de busca binária.
 *    ( iv  ) Algoritmo de Dijkstra.
 *
 *                                                                                            Love&Care
 *                                                                                           7DOLL's CODE
 **/

/**
 *                                  [ PROTÓTIPOS ]
 **/
 # include "Estruturas_e_Constantes_para_Grafo.c"
 void inserir_vertice ( tipo_grafo *grafo, tipo_nodo novo_nodo );
 void inserir_aresta ( tipo_grafo *grafo, char vertice_1, char vertice_2, int tempo_de_retardo  );
 int busca_binaria ( tipo_grafo *grafo, char a_buscar );
 void algoritmo_de_dijkstra ( int posicao_destino, int posicao_inicio, int matriz_adjacencia[ N ][ N ], tipo_distancias distancias[] );

 /**
 *      ( i )      FUNÇÃO PARA INSERIR UM NOVO VÉRTICE
 *
 *          A função recebe o grafo e o tipo_nodo auxiliar como parâmetro. A idéia é inserir o "novo_nodo" com dados que já
 *      foram anteriormente atribuidos para o grafo.
 *          Caso o contador de vértices seja menor que a constante N, significa que o vetor ainda não está cheio, desta forma,
 *      pode-se copiar os elementos do nodo auxiliar "novo_nodo" para o vetor no grafo. O contador de vértices é incrementado.
 *          Caso contrário, não há nada a se fazer com o vetor cheio. Imprime uma mensagem de erro e a função acaba.
 **/
void inserir_vertice ( tipo_grafo *grafo, tipo_nodo novo_nodo ) {
   if ( grafo->contador_vertices < N ) {
      grafo->vetor[ novo_nodo.posicao ].letra = novo_nodo.letra;
      strcpy ( grafo->vetor[ novo_nodo.posicao ].nome, novo_nodo.nome );
      grafo->vetor[ novo_nodo.posicao ].posicao = novo_nodo.posicao;
      grafo->contador_vertices++;
   }
   else
      printf ( "vetor cheio, não é possível inserir um novo vértice.\n" );
}

/**
 *      ( ii )     FUNÇÃO PARA INSERIR UMA NOVA ARESTA
 *
 *          A função recebe o grafo, a letra que equivale ao primeiro e segundo vértice e o tempo de retardo.
 *          Primeiro, a função procura a posição no vetor em que está as letras usando da função de busca binária
 *      e atribui à sua respectiva posição da matriz o tempo de retardo.
 *          Caso o contador de vértices seja menor ou igual a 1, significa que não existem vértices o suficiente para
 *      serem ligados entre uma aresta. Neste caso, imprime a mensagem de erro e não há nada a fazer.
 *          Caso a busca binária não retorne a posição do vetor significa que o vértice não existe, portanto, retorna
 *      uma mensagem de erro e não há nada a fazer.
 *
 **/
void inserir_aresta ( tipo_grafo *grafo, char vertice_1, char vertice_2, int tempo_de_retardo  ) {
   if ( grafo->contador_vertices > 1 ) {
      int u, v;
      u = busca_binaria ( grafo, vertice_1 );
      v = busca_binaria ( grafo, vertice_2 );
      if ( u == infinito || v == infinito )
         printf ( "[ erro ] um dos vértices não existe.\n" );
      else {
         grafo->matriz_adjacencia[ u ][ v ] = tempo_de_retardo;
         grafo->matriz_adjacencia[ v ][ u ] = tempo_de_retardo;
      }
   }
   else
      printf ( "[ erro ] é preciso ter mais de um vértice para estabelecer uma aresta!\n" );
}

/**
 *      ( iii )    FUNÇÃO DE BUSCA BINÁRIA
 *
 *          Busca a posição do vetor onde está o vértice selecionado na função de adicionar nova aresta. A busca começa
 *      pelo meio, caso o elemento seja encontrado, retorna o meio. Senão, pega o meio do meio de acordo se o elemento
 *      a ser procurado é maior ou menor que o elemento da posição atual.
 *
 **/
int busca_binaria ( tipo_grafo *grafo, char a_buscar ) {
   int inicio, meio, fim;
   inicio = 0;
   fim = grafo->contador_vertices;

   while ( inicio <= fim ) {
      meio = ( ( fim + inicio ) / 2 );
      if ( grafo->vetor[ meio ].letra == a_buscar )
         return meio;
      else {
         if ( a_buscar < grafo->vetor[ meio ].letra )
            fim = ( meio - 1 );
         else
            inicio = meio + 1;
      }
   }

   return infinito;
}

/**
 *      ( iv )     ALGORITMO DE DIJKSTRA
 *
 *          Algoritmo de Dijkstra modificado para calcular o menor caminho de uma posição de início até todos os nodos
 *      "entre" a posição de início e posição de fim, incluindo os mesmos. A função é utilizada tanto na função "2"
 *      quando na função "3".
 *          A função recebe um vetor do "tipo_distancias", onde, em cada posição, é guardado a respectiva distância entre o
 *      nodo da "posicao_inicio" e todos os outros nodos presentes no grafo, assim como salva a posição de partida para chegar
 *      neste determinado nodo.
 *
 **/
void algoritmo_de_dijkstra ( int posicao_destino, int posicao_inicio, int matriz_adjacencia[ N ][ N ], tipo_distancias distancias[] ) {
   int i, u, contador, w, flag[ N ], minimo;
   for ( i = 1 ; i <= posicao_destino ; i++ ) {
      flag[ i ] = 0;
      distancias[ i ].distancia = matriz_adjacencia[ posicao_inicio ][ i ];
      distancias[ i ].posicao_anterior = posicao_inicio;
      distancias[ i ].posicao_posterior = i;
   }
   contador = 2;
   while ( contador <= posicao_destino ) {
      minimo = infinito;
      for ( w = 1 ; w <= posicao_destino ; w++ )
         if ( distancias[ w ].distancia < minimo && !flag[ w ] )
            minimo = distancias[ w ].distancia, u = w;
      flag[ u ] = 1;
      contador++;
      for ( w = 1; w <= posicao_destino ; w++ ) {
         if ( ( distancias[ u ].distancia + matriz_adjacencia[ u ][ w ] < distancias[ w ].distancia ) && !flag[ w ] ) {
            distancias[ w ].distancia = distancias[ u ].distancia + matriz_adjacencia[ u ][ w ];
            distancias[ w ].posicao_anterior = u;
            distancias[ w ].posicao_posterior = w;
         }
      }
   }
}
