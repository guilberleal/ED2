/**
 *    UNIVERIDADE FEDERAL DE MATO GROSSO     UFMT-CUA.    07.08.14
 *    TRABALHO VI    GRAFOS                  ESTRUTURA DE DADOS II.
 *    DOCENTE        IVAIRTON M. SANTOS
 *    DISCENTE       GIOVANA HIROMI TANITA   201211722002
 *
 *    [ ARQUIVO ]    Funcao_Principal.c
 *
 *        Este arquivo contém a função principal. Esta função deve ler o
 *    arquivo de entrada que contém as arestas e vértices, adicioná-los ao
 *    grafo e oferecer três opções para o usuário, sendo estas:
 *
 *    ( i   ) Receber o nome de um nodo e retornar se o mesmo existe ou não no grafo.
 *    ( ii  ) Receber o nome de um nodo e retornar a sua distância em relação a todos os outros nodos.
 *    ( iii ) Receber o nome de dois nodos e retornar o caminho mínimo entre eles.
 *
 *                                                                                            Love&Care
 *                                                                                           7DOLL's CODE
 **/

# include "Funcoes_Problema1_TrabalhoVI.c"

int main ( int argc, char * argv[ ] ) {
    /// Declara e inicializa o grafo
    tipo_grafo grafo;
    tipo_nodo nodo_auxiliar;
    tipo_nodo nodo_auxiliar2;

    int i, j;
    grafo.contador_vertices = 0;

    for ( i=0; i<N; i++ ) {
        for ( j=0; j<N; j++ ) {
            grafo.matriz_adjacencia[ i ][ j ] = infinito;
        }
    }

    int flag=0;
    char string_auxiliar[1000];
    char caractere_auxiliar;
    char caractere_auxiliar_2;
    int inteiro_auxiliar;

    /// Lê os elementos no arquivo
    FILE * arquivo = NULL;
    arquivo = fopen ( "arquivo.txt", "rt" );
    while ( !feof ( arquivo ) ) {
        if ( flag == 0 ) {
            /// Lê a primeira linha do arquivo que deve ser "Vértices"
            fscanf ( arquivo, " %[^\n]\n", string_auxiliar );
            flag++;
        }
        else if ( flag == 1 ) {
            /// Deve ler os vértices
            fscanf ( arquivo, "%c", &caractere_auxiliar );
            if ( caractere_auxiliar == '/' ) {
                fscanf ( arquivo, " %[^\n]\n", string_auxiliar );
                flag++;
            }
            else {
                fscanf ( arquivo, " %s\n", string_auxiliar );

                nodo_auxiliar.letra = caractere_auxiliar;
                nodo_auxiliar.posicao = caractere_auxiliar - 97;
                strcpy ( nodo_auxiliar.nome, string_auxiliar );
                inserir_vertice ( &grafo, nodo_auxiliar );
            }
        }
        else if ( flag == 2 ) {
            /// Deve ler as arestas
            fscanf ( arquivo, "%c %c %d\n", &caractere_auxiliar, &caractere_auxiliar_2, &inteiro_auxiliar );
            inserir_aresta ( &grafo, caractere_auxiliar, caractere_auxiliar_2, inteiro_auxiliar );
        }
    }

    printf ( "\t\t[ FUNCIONALIDADES ]\n" );
    int opcao = 0;
    char nome_a_procurar[100];
    while ( opcao != 4 ) {
        printf ( " 1 ) Verificar se um nodo está presente no grafo\n 2 ) Verificar a distância de um nodo para todos os outros\n 3 ) Verificar o caminho mínimo entre um nodo e outro\n 4 ) Sair\n\n" );
        scanf ( "%d", &opcao );
        if ( opcao < 1 || opcao > 4 ) printf ( " [ erro ] Opçãoo inválida\n" );
        else {
            switch ( opcao ) {

            case 1:
                printf ( "Insira o nome do nodo que deseja procurar: " );
                scanf ( "%s", nodo_auxiliar.nome );
                busca_nome ( &grafo, nodo_auxiliar, 0 );
                break;

            case 2:
                printf ( "Insira o nome do nodo que deseja verificar a distância para os demais: " );
                scanf ( "%s", nodo_auxiliar.nome );
                nodo_auxiliar = busca_nome ( &grafo, nodo_auxiliar, 1 );
                distancia_vertices ( &grafo, nodo_auxiliar );
                printf ( "\n\n\n" );
                break;

            case 3:
                printf ( "Insira o nome do primeiro nodo: ");
                scanf ( "%s", nodo_auxiliar.nome );
                nodo_auxiliar = busca_nome ( &grafo, nodo_auxiliar, 1 );
                printf ( "Insira o nome do segundo nodo: " );
                scanf ( "%s", nodo_auxiliar2.nome );
                nodo_auxiliar2 = busca_nome ( &grafo, nodo_auxiliar2, 1 );
                menor_distancia ( &grafo, nodo_auxiliar, nodo_auxiliar2 );
                printf ( "\n\n" );
                break;

            case 4:
                printf ( "\n\n\n\t\t\t Até mais! \n\n\n\n\n" );
                break;
            }
        }
    }
    return 0;
}
