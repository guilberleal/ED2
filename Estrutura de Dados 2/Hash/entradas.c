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

typedef struct estruturaNo {
	int valor;
	struct estruturaNo *prox;
} tipoNo;

int entradas ( int qtd_linhas, char *nome_arq, int tipo, tipoNo** lista );//PROTOTIPO
int pares ( );//PROTOTIPO
void randomizar_nome ( char* nome, int j );//PROTOTIPO
int random_chave ( );

tipoNo *alocaNo (int valor) {
	tipoNo *novoNo = NULL;
	novoNo = (tipoNo*) malloc (sizeof(tipoNo));
	novoNo->valor = valor;
	novoNo->prox = NULL;
	return novoNo;
}

void insere_lista (tipoNo **lista, int valor ) {
	tipoNo *novo_No = alocaNo(valor);
	tipoNo *aux;

	if ( *lista == NULL ) *lista=novo_No;
	else {
		aux = *lista;
		while ( aux-> prox != NULL ) aux = aux->prox;
        aux->prox = novo_No;
	}
}

/***************************************************************************
*   Caso o valor x esteja na lista, retornara 2. Caso contrario retornara  *
* 0, cumprindo o necessario para as funcoes de gerar chave pararem o loop. *
****************************************************************************/
int verifica_lista ( tipoNo *lista, int x ) {
    while ( lista != NULL ) {
        if ( lista->valor == x ) return 2;
            lista = lista->prox;
    }
    return 1;
}

int pares ( tipoNo *lista )//FUNCAO PARA GERAR SOMENTE CHAVES PARES
{
    int chave = -1;
    int x;

    while ( chave == -1 ) {
        if ( ( x = ( 0 + rand() % 1024 ) ) % 2 == 0 )//GERAR NUMEROS PARES
        {
            if ( verifica_lista( lista, x ) == 1 ) {
                chave = x ;
                return chave;//RETORNAR CHAVE QUANDO FOR PAR
            }
            /** Apenas para reforçar a ideia de "continua o loop", pode remover se quiser. **/
            else chave = -1;
        }
    }
}

int random_chave ( tipoNo *lista )
{
    int chave;
    int loop = -1;
    while ( loop == -1 ) {
        chave = 0 + rand () %1024;
        if ( verifica_lista(lista, chave) == 1 ) return chave;
        else loop = -1;
    }
}

void randomizar_nome ( char* nome, int j ) //RANDOMIZAR NOME PARA POR NO ARQUIVO
{
    char *x;
    int i;
    x = ( char* ) malloc ( sizeof ( char ) );
    strcpy ( nome, "Li" );
    sprintf ( x , "%d", j );//TRANSFORMAR UM INTEIRO EM UM CHAR
    strcat ( nome, x );//CONCATENAR UMA STRING
}

int entradas ( int qtd_linhas, char *nome_arq, int tipo, tipoNo **lista )//FUNCAO PARA FICAR GERANDO ARQUIVOS
{
    FILE* arquivo;
    int i, j, y;
    char* key;
    char* nome;
    int chave;

    if ( ( arquivo = fopen ( nome_arq, "wt+" ) ) == NULL )//VERIFICACAO DA ABERTURA DO ARQUIVO
        printf ( "\n\a[ ERROR TO OPEN ]\a\n" );
    else
    {
        for ( j = 0; j < qtd_linhas; j ++ )//LAÇO PARA CRIAR J LINHAS
        {
            key = ( char* ) malloc ( sizeof ( char ) );//ALOCAR O TAMANHO DE UM CHAR PARA O PONTEIRO KEY
            nome = ( char* ) malloc ( sizeof ( char ) );//ALOCAR O TAMANHO DE UM CHAR PARA O PONTEIRO NOME

            if ( tipo == 1 ) {
                chave = pares ( *lista );
                insere_lista ( lista, chave );
                sprintf ( key, "%d", chave );//RANDOMIZAR UMA CHAVE COM A FUNCAO HASH
            }
            else {
                chave = random_chave ( *lista );
                insere_lista ( lista, chave );
                sprintf ( key, "%d", chave );
            }

            randomizar_nome ( nome, j );//RANDOMIZAR UM NOME PARA POR NO ARQUIVO

            if ( ( fputs ( key, arquivo ) ) != 0 )//POR A CHAVE HASH NO ARQUIVO
                printf ( "\n\a[ ERROR KEY ]\a\n" );
            fputs ( "\t", arquivo );
            if ( ( fputs ( nome, arquivo ) ) != 0 )//POR UM NOME NO ARQUIVO
                printf ( "\n\a[ ERROR NOME ]\a\n" );
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
    entradas ( atoi ( argv [ 1 ] ), argv [ 2 ], atoi ( argv [ 3 ] ), &lista );
    return 0;
}
