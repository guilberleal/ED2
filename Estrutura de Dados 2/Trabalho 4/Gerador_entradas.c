/**
 **   AUTORES: ALEX MATOS IUASSE, GIOVANA HIROMI
 **   ALGORITMO PARA ELABORACAO DAS ENTRADAS NO ARQUIVO
 **/

#include <stdio.h> //BIBLIOTECA COM SCANF
#include <stdlib.h> //BIBLIOTECA COM A FUNCAO RAND
#include <string.h> //BIBLIOTECA PARA MANIPULAR STRINGS
#include <time.h> //BIBLIOTECA AUXILIAR PARA RANDOMIZAR A FUNCAO RAND

/***************************************************************************
*   As chaves que ja foram guardadas no arquivo serao colocados em uma     *
* LISTA com o objetivo de minimizar esforcos.                              *
****************************************************************************/

/** ESTRUTURA DA LISTA **/
typedef struct estruturaNo
{
    int valor;
    struct estruturaNo *prox;
} tipoNo;

/** PROTÓTIPOS **/
int entradas ( int qtd_linhas, char *nome_arq, tipoNo** lista );
int numeros ( );
/** PROTÓTIPOS DA LISTA QUE VERIFICA SE NÚMERO E IGUAL AO QUE JA FOI INSERIDO **/
tipoNo *alocaNo (int valor);
void insere_lista (tipoNo **lista, int valor );
int verifica_lista ( tipoNo *lista, int x );

/** FUNÇÕES **/
tipoNo *alocaNo (int valor)
{
    tipoNo *novoNo = NULL;
    novoNo = (tipoNo*) malloc (sizeof(tipoNo));
    novoNo->valor = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void insere_lista (tipoNo **lista, int valor )
{
    tipoNo *novo_No = alocaNo(valor);
    tipoNo *aux;

    if ( *lista == NULL ) *lista=novo_No;
    else
    {
        aux = *lista;
        while ( aux-> prox != NULL ) aux = aux->prox;
        aux->prox = novo_No;
    }
}

/***************************************************************************
*   Caso o valor x esteja na lista, retornara 2. Caso contrario retornara  *
* 0, cumprindo o necessario para as funcoes de gerar chave pararem o loop. *
****************************************************************************/
int verifica_lista ( tipoNo *lista, int x )
{
    while ( lista != NULL )
    {
        if ( lista->valor == x ) return 2;
        lista = lista->prox;
    }
    return 1;
}

int numeros ( tipoNo *lista )
{
    int chave = -1;
    int x;

    while ( chave == -1 )
    {
        if ( x = ( 0 + rand() % 100000 ) )
        {
            if ( verifica_lista( lista, x ) == 1 )
            {
                chave = x ;
                return chave;
            }
            /** Apenas para reforçar a ideia de "continua o loop", pode remover se quiser. **/
            else chave = -1;
        }
    }
}

int entradas ( int qtd_linhas, char *nome_arq, tipoNo **lista )//FUNCAO PARA FICAR GERANDO ARQUIVOS
{
    FILE* arquivo;
    int j;
    char* key;
    int chave;

    if ( ( arquivo = fopen ( nome_arq, "wt+" ) ) == NULL )//VERIFICACAO DA ABERTURA DO ARQUIVO
        printf ( "\n\a[ ERROR TO OPEN ]\a\n" );
    else
    {
        for ( j = 0; j < qtd_linhas; j ++ )//LAÇO PARA CRIAR J LINHAS
        {
            key = ( char* ) malloc ( sizeof ( char ) );//ALOCAR O TAMANHO DE UM CHAR PARA O PONTEIRO KEY

            chave = numeros ( *lista );
            insere_lista ( lista, chave );
            sprintf ( key, "%d", chave ); //CONVERTER PARA STRING, PARA POR NO ARQUIVO

            if ( ( fputs ( key, arquivo ) ) != 0 )
                printf ( "\n\a[ ERROR KEY ]\a\n" ); //POR O NUMERO NO ARQUIVO
            fputs ( "\t", arquivo );
            if ( j < qtd_linhas - 1 )
                fputs ( "\n", arquivo );
        }
        fclose ( arquivo );//FECHAR ARQUIVO
    }
    return 0;
}

int main( int argc, char **argv )//FUNCAO PRINCIPAL
{
    tipoNo *lista = NULL;
    srand ( atoi ( argv [ 2 ] ) );//FUNCAO PARA RANDOMIZAR
    entradas ( atoi ( argv [ 1 ] ), argv [ 2 ], &lista );
    return 0;
}
