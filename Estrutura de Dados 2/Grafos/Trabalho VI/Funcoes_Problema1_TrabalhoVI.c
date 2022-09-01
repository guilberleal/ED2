/**
 *    UNIVERIDADE FEDERAL DE MATO GROSSO     UFMT-CUA.    07.08.14
 *    TRABALHO VI    GRAFOS                  ESTRUTURA DE DADOS II.
 *    DOCENTE        IVAIRTON M. SANTOS
 *    DISCENTE       GIOVANA HIROMI TANITA   201211722002
 *
 *    [ ARQUIVO ]    Funcoes_Problema1_TrabalhoVI.c
 *
 *        Este arquivo contém as funções solicitadas para o Trabalho VI conforme as
 *    especificações do "Problema 1". São estas:
 *
 *    ( i   ) Busca por um dado nodo a partir de seu nome.
 *             ( i.i    ) Caso nodo encontrado, imprime "nó está presente.".
 *             ( i.ii   ) Caso nodo não encontrado, imprime "o nó não existe.".
 *    ( ii  ) Calcula a distância de um dado nodo para todos os outros nodos a partir de seu nome.
 *             ( ii.i   ) O formato segue "COMPX = K".
 *    ( iii ) Identifica o caminho com o menor retardo entre um nó de origem até o destino a partir de seu nome.
 *
 *                                                                                            Love&Care
 *                                                                                           7DOLL's CODE
 **/

/**
 *                                  [ PROTÓTIPOS ]
 **/
 # include "Funcoes_Auxiliares_para_Grafo.c"
 tipo_nodo busca_nome ( tipo_grafo *grafo, tipo_nodo nodo_auxiliar, int flag );

/**
 *      [ FUNÇÃO ( 1 ) ]      BUSCAR O NODO PELO NOME
 *      Do enunciado: "A partir do nome do nó, verificar se o nó está presente no grafo".
 *
 *      [ SOLUÇÃO ]
 *          A função recebe um nodo_auxiliar contendo o nome do nodo a ser buscado. Funciona da mesma
 *      forma que uma busca binária porém utilizando da função strcmp da string.h. Caso a string
 *      que está na posição "meio" do vetor seja encontrado, imprime a mensagem "O nó está presente"
 *      e retorna o nodo original. Se não houver nenhum retorno, significa que o nó não existe.
 *          A flag determina se a mensagem de retorno deverá ser impressa ou não, pois esta função
 *      é reutilizada em outros momentos onde não deverá haver impressão de mensagem.
 *
 **/
tipo_nodo busca_nome ( tipo_grafo *grafo, tipo_nodo nodo_auxiliar, int flag ) {
   int inicio, meio, fim;
   inicio = 0;
   fim = grafo->contador_vertices;

   while ( inicio <= fim ) {
      meio = ( ( fim + inicio ) / 2 );
      if ( strcmp ( grafo->vetor[ meio ].nome, nodo_auxiliar.nome ) == 0 ) {
         if ( flag == 0 )
            printf ( "O nó está presente.\n" );
         return grafo->vetor[ meio ];
      }
      else {
         if ( strcmp ( grafo->vetor[ meio ].nome, nodo_auxiliar.nome ) > 0 )
            fim = ( meio - 1 );
         else
            inicio = ( meio + 1 );
      }
   }
   if ( flag == 0 ) printf ( "O nó NÃO existe.\n" );
}

/**
 *      [ FUNÇÃO ( 2 ) ]      CALCULAR A DISTÂNCIA DE UM NODO PARA TODOS OS OUTROS
 *      Do enunciado: "A partir do nome do nó, calcular sua distância para todos os outros nós da rede".
 *
 *      [ SOLUÇÃO ]
 *          A função recebe o grafo e o nodo_inicial.
 *          A função com o Algoritmo de Dijkstra é chamada e processa o nodo_inicial em relação a TODOS
 *      os outros nodos presentes no grafo, as distâncias são gravadas no vetor "distancias". Essas distâncias
 *      são impressas seguindo o modelo "COMPX = K".
 *
 **/
void distancia_vertices ( tipo_grafo * grafo, tipo_nodo nodo_inicial ) {
   int i, j;
   tipo_distancias distancias[ N ];

   algoritmo_de_dijkstra ( grafo->contador_vertices, nodo_inicial.posicao, grafo->matriz_adjacencia, distancias );

   for ( i=nodo_inicial.posicao ; i <= grafo->contador_vertices ; i++ )
      if ( i != nodo_inicial.posicao ) {
         if ( distancias[ i ].distancia != infinito )
            printf( "%s = %d\n", grafo->vetor[ i ].nome, distancias[ i ].distancia );
      }
      else {
         printf ( "%s = 0\n", grafo->vetor[i].nome );
      }
}

/**
 *      [ FUNÇÃO ( 3 ) ]      CAMINHO DE MENOR RETARDADO DE UM NODO PARA OUTRO
 *      Do enunciado: "A partir dos nomes dos nós de origem e destino, identificar o caminho com o menor retardo.".
 *
 *      [ SOLUÇÃO ]
 *          A função recebe o grafo, nodo_inicial e nodo_final.
 *          A função com o Algoritmo de Dijkstra é chamada e processa o nodo_inicial em relação a todos
 *      os outros nodos entre este e o nodo_final, as distâncias são gravadas no vetor "distancias".
 *          Após isso, é dado um "check" em todas as posições de distância relevantes ao menor caminho
 *      entre o nodo_inicial e nodo_final que são impressos seguindo o modelo "O caminho é: (COMPX, COMPY)(Kms)"
 *
 **/
void menor_distancia ( tipo_grafo * grafo, tipo_nodo nodo_inicial, tipo_nodo nodo_final ) {
   int i, j;
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
            if ( distancias[i].check == 1 )
            if ( i != nodo_final.posicao )
            printf( "( %s, %s )(%dms), ", grafo->vetor[ distancias[ i ].posicao_anterior ].nome, grafo->vetor[ distancias[ i ].posicao_posterior ].nome, distancias[ i ].distancia );
            else printf( "( %s, %s )(%dms)\n\n", grafo->vetor[ distancias[ i ].posicao_anterior ].nome, grafo->vetor[ distancias[ i ].posicao_posterior ].nome, distancias[ i ].distancia );
      }
}
