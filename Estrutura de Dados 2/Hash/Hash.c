/**
 **   ALGORITMO DE CRIACAO DE TABELAS HASH
 **   TRATAMENTO DE COLISAO INTERNA E EXTERNA
 **   AVALIACAO DA MELHOR FUNCAO HASH
 **   AUTORES: GIOVANA HIROMI, ALEX MATOS IUASSE
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tam 100


/*************************************************
*                                                *
*                                                *
*                    ETAPA 2                     *
*                                                *
*                                                *
**************************************************/

/********************************************
*   Estruturas.                             *
********************************************/
typedef struct tipo_hsh
{
    char* nome;
    struct tipo_hsh *proximo;
} tipo_hash;

typedef struct dado
{
    int chave;
    char nome[4];
    int colisoes;
} tipoDado;

/**
    PROTOTIPOS DE FUNCOES
**/

int dispersao_de_fibonacci (int chave);
int meio_do_quadrado( int chave );
int metodo_divisao ( int chave );
tipo_hash *aloca_no ( char *nome );
void insere_hash ( int chave, char *nome, tipo_hash **hash_meioquad, tipo_hash **hash_divisao, tipo_hash **hash_fibo );
void insereHash ( tipoDado *tab_hash_fibo, tipoDado *tab_hash_meioquad, tipoDado *tab_hash_divisao, char *nome, int chave );
void avaliacao_externa ( tipo_hash **hash_meioquad, tipo_hash **hash_divisao, tipo_hash **hash_fibo );
void avaliacao_interna ( tipoDado *tab_hash_fibo, tipoDado *tab_hash_meioquad, tipoDado *tab_hash_divisao );


/********************************************
*   Funcoes Hash.                           *
********************************************/
int dispersao_de_fibonacci (int chave)
{
    int a, n;
    double d, A;
    n=13;
    A=(sqrt(5)-1)/2;
    a= (int) floor(n*modf(A*chave,&d));
    return(a);
}

int meio_do_quadrado( int chave )
{
    int v , x , y , w ;
    x=-1;
    while ( x<0 ) {

        w = chave * chave ;
        y = w << 16 ;
        x = y >> 29 ;
        chave = w;

    }
    return (x);
}

int metodo_divisao ( int chave )
{
    int tab_chave;
    tab_chave = chave*7;
    tab_chave = tab_chave%tam;

    return tab_chave;
}


/********************************************
*   Alocação dinâmica.                      *
********************************************/
tipo_hash *aloca_no ( char *nome )
{
    int i;
    tipo_hash *novo_no = NULL;
    novo_no = ( tipo_hash* ) malloc ( sizeof ( tipo_hash ) );
    novo_no->nome = ( char* ) malloc ( sizeof ( char ) );
    strcpy ( novo_no->nome, nome );
    novo_no->proximo = NULL;
    return novo_no;
}


/********************************************
*   Insercao Hash EXTERNA                   *
********************************************/
void insere_hash ( int chave, char *nome, tipo_hash **hash_meioquad, tipo_hash **hash_divisao, tipo_hash **hash_fibo )
{
    int indice;
    /*****************************
    *   Dispersao de Fibonacci   *
    ******************************/
    indice = dispersao_de_fibonacci( chave );
    while ( indice > tam ) indice = indice-tam;
    if ( hash_fibo [ indice ] == NULL )
    {
        tipo_hash *novo_no = aloca_no ( nome );
        (  hash_fibo [ indice ] ) = novo_no;
    }
    else
    {
        tipo_hash *novo_no = aloca_no ( nome );
        tipo_hash *aux = hash_fibo [ indice ];
        while ( aux->proximo != NULL )
            aux = aux->proximo;
        aux->proximo = novo_no;
    }

    /*****************************
    *   Metodo Meio do Quadrado  *
    ******************************/
    indice = meio_do_quadrado( chave );
    while ( indice > tam ) indice = indice-tam;
    if ( hash_meioquad [ indice ] == NULL )
    {
        tipo_hash *novo_no_q1 = aloca_no ( nome );
        (  hash_meioquad [ indice ] ) = novo_no_q1;
    }
    else
    {
        tipo_hash *novo_no_q = aloca_no ( nome );
        tipo_hash *aux_q = hash_meioquad [ indice ];
        while ( aux_q->proximo != NULL ) {
                aux_q = aux_q->proximo;
        }
        aux_q->proximo = novo_no_q;
    }
    /*****************************
    *   Metodo da Divisao        *
    ******************************/
    indice = metodo_divisao( chave );
    while ( indice > tam ) indice = indice-tam;
    if ( hash_divisao [ indice ] == NULL )
    {
        tipo_hash *novo_no = aloca_no ( nome );
        (  hash_divisao [ indice ] ) = novo_no;
    }
    else
    {
        tipo_hash *novo_no = aloca_no ( nome );
        tipo_hash *aux = hash_divisao [ indice ];
        while ( aux->proximo != NULL )
            aux = aux->proximo;
        aux->proximo = novo_no;
    }
}

/********************************************
*   Insercao Hash INTERNA.                  *
********************************************/
void insereHash ( tipoDado *tab_hash_fibo, tipoDado *tab_hash_meioquad, tipoDado *tab_hash_divisao, char *nome, int chave )
{

    int tab_chave;
    int c;

    /*****************************
    *   Dispersao de Fibonacci   *
    ******************************/
    c=0;
    tab_chave = dispersao_de_fibonacci ( chave );
    while ( tab_chave > tam )
    {
        tab_chave = tab_chave - tam;
    }
    while ( tab_hash_fibo[tab_chave].chave != -1 )
    {
        if ( c==0 ) tab_hash_fibo[0].colisoes++;
        c++;
        tab_chave=tab_chave+2;
        if ( tab_chave > tam ) tab_chave = 0;
    }
    if ( tab_hash_fibo[tab_chave].chave == -1 )
    {
        strcpy (tab_hash_fibo[tab_chave].nome, nome);
        tab_hash_fibo[tab_chave].chave = chave;
    }

    /*****************************
    *   Metodo Meio do Quadrado  *
    ******************************/
    c=0;
    tab_chave = meio_do_quadrado ( chave );
    while ( tab_chave > tam )
    {
        tab_chave = tab_chave - tam;
    }
    while ( tab_hash_meioquad[tab_chave].chave != -1 )
    {
        if ( c==0 ) tab_hash_meioquad[0].colisoes++;
        c++;
        tab_chave=tab_chave+2;
        if ( tab_chave > tam ) tab_chave = 0;
    }
    if ( tab_hash_meioquad[tab_chave].chave == -1 )
    {
        strcpy (tab_hash_meioquad[tab_chave].nome, nome);
        tab_hash_meioquad[tab_chave].chave = chave;
    }

    /*****************************
    *   Metodo da Divisao        *
    ******************************/
    c=0;
    tab_chave = meio_do_quadrado ( chave );
    while ( tab_chave > tam )
    {
        tab_chave = tab_chave - tam;
    }
    while ( tab_hash_divisao[tab_chave].chave != -1 )
    {
        if ( c==0 ) tab_hash_divisao[0].colisoes++;
        c++;
        tab_chave=tab_chave+2;
        if ( tab_chave > tam ) tab_chave = 0;
    }
    if ( tab_hash_divisao[tab_chave].chave == -1 )
    {
        strcpy (tab_hash_divisao[tab_chave].nome, nome);
        tab_hash_divisao[tab_chave].chave = chave;
    }
}


/*************************************************
*                                                *
*                                                *
*                    ETAPA 3                     *
*                                                *
*                                                *
**************************************************/

void avaliacao_externa ( tipo_hash **hash_meioquad, tipo_hash **hash_divisao, tipo_hash **hash_fibo )
{

    FILE * RELATORIO;
    RELATORIO = fopen ( "RelatorioExterno.txt", "at+" );
    if ( RELATORIO == NULL ) printf ( "Ocorreu um erro.\n" );
    else
    {

        int distancia_fibo, distancia_meioquad, distancia_divisao, qt_fibo, qt_meioquad, qt_divisao, i;
        int colisoes_fibo, colisoes_meioquad, colisoes_divisao;
        float result_fibo, result_meioquad, result_divisao;

        distancia_fibo=0;
        distancia_meioquad=0;
        distancia_divisao=0;
        qt_fibo=0;
        qt_meioquad=0;
        qt_divisao=0;
        i=0;
        colisoes_fibo=0;
        colisoes_meioquad=0;
        colisoes_divisao=0;

        i=0;
        while ( i<tam )
        {
            if ( hash_fibo[i]==NULL )
            {
                qt_fibo++;
                while ( hash_fibo[i]==NULL )
                {
                    distancia_fibo++;
                    i++;
                    if ( i>tam ) break;
                }
            }
            else
            {
                tipo_hash *aux = hash_fibo [ i ];
                while ( aux->proximo != NULL )
                {
                    colisoes_fibo++;
                    aux = aux->proximo;
                }
                i++;
            }
        }
        result_fibo = distancia_fibo / qt_fibo;
        fprintf( RELATORIO, "Dispersao de Fibonacci:\nCOLISOES %d\nMEDIA DE DISTANCIA %f\n\n", colisoes_fibo, result_fibo);

        i=0;
        while ( i<tam )
        {
            if ( hash_meioquad[i]==NULL )
            {
                qt_meioquad++;
                while ( hash_meioquad[i]==NULL )
                {
                    distancia_meioquad++;
                    i++;
                    if ( i>tam ) break;
                }
            }
            else
            {
                tipo_hash *aux = hash_meioquad [ i ];
                while ( aux->proximo != NULL )
                {
                    colisoes_meioquad++;
                    aux = aux->proximo;
                }
                i++;
            }
        }
        result_meioquad = distancia_meioquad / qt_meioquad;
        fprintf( RELATORIO, "Meio do Quadrado:\nCOLISOES %d\nMEDIA DE DISTANCIA %f\n\n", colisoes_meioquad, result_meioquad);
        i=0;
        while ( i<tam )
        {
            if ( hash_divisao[i]==NULL )
            {
                qt_divisao++;
                while ( hash_divisao[i]==NULL )
                {
                    distancia_divisao++;
                    i++;
                    if ( i>tam ) break;
                }
            }
            else
            {
                tipo_hash *aux1 = hash_divisao [ i ];
                while ( aux1->proximo != NULL )
                {
                    colisoes_divisao++;
                    aux1 = aux1->proximo;
                }
                i++;
            }
        }
        if ( qt_divisao!=0 )result_divisao = distancia_divisao / qt_divisao;
        fprintf( RELATORIO, "Metodo de Divisao:\nCOLISOES %d\nMEDIA DE DISTANCIA %f\n\n", colisoes_divisao, result_divisao);
    }
    fclose ( RELATORIO );
}

void avaliacao_interna ( tipoDado *tab_hash_fibo, tipoDado *tab_hash_meioquad, tipoDado *tab_hash_divisao )
{
    FILE * RELATORIO;
    RELATORIO = fopen ( "RelatorioInterno.txt", "at+" );
    if ( RELATORIO == NULL ) printf ( "Ocorreu um erro.\n" );
    else
    {
        int distancia_fibo, distancia_meioquad, distancia_divisao, qt_fibo, qt_meioquad, qt_divisao, i, j;
        float result_fibo, result_meioquad, result_divisao;
        qt_fibo=0;
        qt_meioquad=0;
        qt_divisao=0;
        distancia_fibo=0;
        distancia_meioquad=0;
        distancia_divisao=0;
        i=0;

        while ( i<tam )
        {
            if ( tab_hash_fibo[i].chave==-1 )
            {
                qt_fibo++;
                while ( tab_hash_fibo[i].chave==-1 )
                {
                    distancia_fibo++;
                    i++;
                    if ( i>tam ) break;
                }
            }
            else i++;
        }
        result_fibo = distancia_fibo / qt_fibo;
        fprintf( RELATORIO, "Dispersao de Fibonacci:\nCOLISOES %d\nMEDIA DE DISTANCIA %f\n\n", tab_hash_fibo[0].colisoes, result_fibo);

        i=0;
        while ( i<tam )
        {
            if ( tab_hash_meioquad[i].chave==-1 )
            {
                qt_meioquad++;
                while ( tab_hash_meioquad[i].chave==-1 )
                {
                    distancia_meioquad++;
                    i++;
                    if ( i>tam ) break;
                }
            }
            else i++;
        }
        result_meioquad = distancia_meioquad / qt_meioquad;
        fprintf( RELATORIO, "Meio do Quadrado:\nCOLISOES %d\nMEDIA DE DISTANCIA %f\n\n", tab_hash_meioquad[0].colisoes, result_meioquad);

        i=0;
        while ( i<tam )
        {
            if ( tab_hash_divisao[i].chave==-1 )
            {
                qt_divisao++;
                while ( tab_hash_divisao[i].chave==-1 )
                {
                    distancia_divisao++;
                    i++;
                    if ( i>tam ) break;
                }
            }
            else i++;
        }
        result_divisao = distancia_divisao / qt_divisao;
        fprintf( RELATORIO, "Metodo da Divisao:\nCOLISOES %d\nMEDIA DEDISTANCIA %f\n\n", tab_hash_divisao[0].colisoes, result_divisao);
    }
    fclose ( RELATORIO );
}

int main ( int argc, char **argv ) ///FUNCAO PRINCIPAL
{

    FILE *arquivo = NULL;
    char* chave;
    int c,x;
    char* nome;

    ///DECLARACAO DA HASH EXTERNA
    tipo_hash **hash_fibo;
    tipo_hash **hash_meioquad;
    tipo_hash **hash_divisao;

    hash_fibo = ( tipo_hash** ) malloc ( tam * sizeof ( tipo_hash* ) );///ALOCAR TAM ESPACOS PARA HASH
    hash_meioquad = ( tipo_hash** ) malloc ( tam * sizeof ( tipo_hash* ) );
    hash_divisao = ( tipo_hash** ) malloc ( tam * sizeof ( tipo_hash* ) );

    chave = ( char* ) malloc ( 4*sizeof ( char ) );
    nome = ( char* ) malloc ( 4*sizeof ( char ) );

    for ( x = 0; x < tam; x ++ )  ///LACO PARA COLOCAR HASH EXTERNO EM NULO
    {
        hash_fibo [ x ] = NULL;
        hash_meioquad [ x ] = NULL;
        hash_divisao [ x ] = NULL;

    }

    ///DECLARACAO DA HASH INTERNA
    int i;
    tipoDado *interno_fibo;
    tipoDado *interno_meioquad;
    tipoDado *interno_divisao;

    interno_fibo = ( tipoDado* ) malloc ( tam * sizeof ( tipoDado ) );
    interno_divisao = ( tipoDado* ) malloc ( tam * sizeof ( tipoDado ) );
    interno_meioquad = ( tipoDado* ) malloc ( tam * sizeof ( tipoDado ) );

    for ( i=0; i<tam; i++ )  ///LAÇO PARA COLOCAR HASH INTERNO EM "NULO"
    {
        interno_fibo[i].chave=-1;
        interno_meioquad[i].chave=-1;
        interno_divisao[i].chave=-1;
    }

    interno_fibo[0].colisoes=0;
    interno_meioquad[0].colisoes=0;
    interno_divisao[0].colisoes=0;

    ///COMECAR A INSERIR NAS HASH A PARTIR DAS ENTRADAS NO ARQUIVO
    arquivo = fopen ( argv [ 1 ], "rt" );///argv [ 1 ] é o nome do arquivo que vai ser passado como parametro
    while ( !feof ( arquivo ) )
    {
        fscanf ( arquivo, "%s%s", chave, nome );
        //printf ( "%s\t%s\n", chave, nome );
        insere_hash ( atoi ( chave ), nome, hash_meioquad, hash_divisao, hash_fibo );
        insereHash ( interno_fibo, interno_meioquad, interno_divisao, nome, atoi ( chave ) );
    }
    avaliacao_externa ( &(*hash_meioquad), &(*hash_divisao), &(*hash_fibo) );
    avaliacao_interna ( interno_meioquad, interno_divisao, interno_fibo );


    return 0;
}
