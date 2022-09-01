/**
 *	ALGORITMO DE COLORAÇÃO
 **/

#include "Funcoes_Auxiliares_para_Grafo.c"

void algoritmo_coloracao ( tipo_grafo *grafo ) {
    int i, j;

    /** Vetor que guarda o conjunto solução */
    int resultados[N];

    /** Vetor que armazena as cores disponíveis, se a posicao "i" do vetor for marcada como 1
    significa que a cor i não está disponível, senão, a cor pode ser utilizada **/
    int cores_disponiveis[N];
    /** Inicializa o vetor, no começo, todas as cores estão disponíveis **/
    for ( i=0; i <=grafo->contador_vertices; i++ ) cores_disponiveis[i]=0;

    for ( i=1; i <=grafo->contador_vertices; i++ ) {
        /** Processa todos os vértices adjacentes e marca suas cores como indisponíveis **/
        for ( j=1; j<=grafo->contador_vertices; j++ ) {
            /** Evita de comparar um vértice com eles mesmo **/
            if ( i!=j ) {
                /** Se for adjacente, a cor desse vértice não pode ser utilizada **/
                if ( eh_adjacente( grafo, i, j ) == 1 ) {
                    cores_disponiveis[resultados[j]] = 1;
                }
            }
        }

        /** Procura a primeira cor disponível **/
        int k;
        for ( k=1; k<=grafo->contador_vertices; k++ )
            if ( cores_disponiveis[k] == 0 )
                break;

        /** atribui a cor encontrada ao vértice a ser processado **/
        resultados[i]=k;

        /** reseta os valores, todas as cores estão disponíveis para a próxima iteração **/
        for ( j=1; j<=grafo->contador_vertices; j++ ) {
            if ( eh_adjacente( grafo, i, j ) ) {
                cores_disponiveis[j] = 0;
            }
        }

    }
    /** imprime o conjunto solução **/
    for ( i=1; i<=grafo->contador_vertices; i++ ) {
        printf ("Vertice %d --- Cor %d\n", i, resultados[i] );
    }

}
