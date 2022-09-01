/**
    UNIVERSIDADE FEDERAL DE MATO GROSSO
    PROFESSOR: IVAIRTON DATA: 30/04/2014
    ALUNOS: ALEX MATOS IUASSE E GIOVANA HIROMI TANITA
    ALGORITMO PARA ELABORAÇÃO DE UMA MATRIZ ESPARSA
    O NOME DO ALGORITMO FOI DADO PELO FATO DE ESPARSA SE PARECER MUITO COM ESPARTA
**/

///CABEÇALHO DE INCLUSÃO
#include <stdio.h>
#include <stdlib.h>

///ESTRUTURA ESPARSA
typedef struct typeNode {
    int value;
    int column;
    int row;
    struct typeNode * right;
    struct typeNode * down;
} typeNode;

///PROTÓTIPOS
void printList ( typeNode *sparseMatrix ) ; ///IMPRIMIR A MATRIZ
typeNode *allocNode ( int value, int c, int r ); ///ALOCAR UM NOVO NO PARA A MATRIZ
void addValue ( typeNode ** sparseMatriz, int value, int c, int r ); ///ADICIONAR UM NOVO ELEMENTO A MATRIZ
int returnValue ( typeNode *sparseMatrix, int c, int r ); ///RETORNAR UM VALOR DE UMA DETERMINADA POSIÇÃO
void plus ( typeNode **esparse, int value, int col, int lin ); ///SOMAR UM ELEMENTO A UMA DETERMINADA POSIÇÃO
void plus_all ( typeNode **esparse, int value ); ///SOMAR UM ELEMENTO A TODO ELEMENTO DA MATRIZ
int plus_all_all ( typeNode **esparse ); ///SOMAR TODOS ELEMENTOS DA MATRIZ E RETORNAR O RESULTADO
void plus_matrix_3 ( typeNode **esparse1, typeNode **esparse2, typeNode **esparse3 ); ///SOMAR 2 MATRIZES E CRIAR UMA TERCEIRA
int return_dimension ( typeNode *esparse ); ///RETORNAR A DIMENSÃO DA MATRIZ

///FUNÇÕES
typeNode *allocNode ( int value, int c, int r ) {
	typeNode *newNode = NULL;
	newNode = ( typeNode* ) malloc ( sizeof ( typeNode ) );
	newNode->value = value;
	newNode->column = c;
	newNode->row = r;
	newNode->right = NULL;
	newNode->down = NULL;
	return newNode;
}

/* c : column   r : row */
void addValue ( typeNode ** sparseMatriz, int value, int c, int r ) {

    typeNode *newNode = allocNode ( value, c, r );

    if ( * sparseMatriz == NULL ) {
        typeNode *root = allocNode ( 0, 0, 0 );
        typeNode *newColumn = allocNode ( 0, c, 0 );
        typeNode *newRow = allocNode ( 0, 0, r );
        root->right = newColumn;
        root->down = newRow;
        newColumn->down = newNode;
        newRow->right = newNode;
        * sparseMatriz = root;
    }
    else {
        typeNode *auxC = *sparseMatriz; /* auxiliar retardado colunas */
        typeNode *auxR = *sparseMatriz; /* auxiliar retardado linhas */
        typeNode *auxCol = auxR->right;
        typeNode *auxRow = auxR->down;
        int choiceR=0; int coiceC=0;

        /*      !!  TRATAMENTO DAS COLUNAS !!       */
        while ( auxC->right != NULL ) {
            if ( c <= auxCol->column ) {
                if ( c == auxCol->column ) coiceC=1; /* Nao precisa criar o indice */
                if ( c < auxCol-> column ) coiceC=2; /* Precisa criar o indice */
                break;
            }

            auxC = auxC->right;
            if ( auxC->right!=NULL ) auxCol = auxCol->right;
        }
        if ( c > auxCol->column ) coiceC=3;

        if ( coiceC == 3 ) {
            typeNode *newCol = allocNode ( 0, c, 0 );
            auxCol->right = newCol;
        }

        if ( coiceC==2 ) {
            typeNode *newCol = allocNode ( 0, c, 0 );
            newCol->right = auxCol;
            auxC->right = newCol;
        }

        if ( coiceC == 0 ) {
            typeNode *newCol = allocNode ( 0, c, 0 );
            auxC->right = newCol;
        }
        else auxC = auxC->right; /* Agora o auxC esta na posicao exata para receber o novo valor */
        coiceC = 0;

        if ( auxC->down == NULL ) {
            auxC->down = newNode;
        }
        else {

            auxCol = auxCol->down;
            while ( auxC->down != NULL ) {
                if ( r == auxCol->row && c == auxCol->column ){
                    printf ( "Posicao ja preenchida!\n" );
                    return;
                }

                if ( r < auxCol->row ) {
                    coiceC = 2;
                    break;
                }
                auxC = auxC->down;
                if ( auxC->down != NULL ) auxCol = auxCol->down;
            }

            if ( coiceC == 2 ) {
                newNode->down = auxCol;
                auxC->down = newNode;
            }
            if ( coiceC == 0 ) {
                auxC->down = newNode;
            }
        }

        /*      !! TRATAMENTO DAS LINHAS !!         */
        while ( auxR->down != NULL ) {
            if ( r <= auxRow->row ) {
                if ( r == auxRow->row ) choiceR=1; /* Nao precisa criar o indice */
                if ( r < auxRow-> row ) choiceR=2; /* Precisa criar o indice */
                break;
            }
            auxR = auxR->down;
            if ( auxR->down!=NULL ) auxRow = auxRow->down;
        }
        if ( r > auxRow->row ) choiceR=3;

        if ( choiceR == 3 ) {
            typeNode *newRow = allocNode ( 0, 0, r );
            auxRow->down = newRow;
        }

        if ( choiceR==2 ) {
            typeNode *newRow = allocNode ( 0, 0, r );
            newRow->down = auxRow;
            auxR->down = newRow;
        }
        if ( choiceR == 0 ) {
            typeNode *newRow = allocNode ( 0, 0, r );
            auxR->down = newRow;
        }
        else auxR = auxR->down; /* Agora o auxR esta na posicao exata para receber o novo valor */
        choiceR = 0;

        if ( auxR->right == NULL ) {
            auxR->right = newNode;
        }
        else {
            auxRow = auxRow->right;
            while ( auxR->right != NULL ) {
                if ( c == auxRow->column && r == auxRow->row ) {
                    printf ( "Posicao ja preenchida!\n" );
                    return;
                }
                if ( c < auxRow->column ) {
                    choiceR = 2;
                    break;
                }
                auxR = auxR->right;
                if ( auxR->right != NULL ) auxRow = auxRow->right;
            }

            if ( choiceR == 2 ) {
                newNode->right = auxRow;
                auxR->right = newNode;
            }
            if ( choiceR == 0 ) {
                auxR->right = newNode;
            }
        }
    }
}

int returnValue ( typeNode *sparseMatrix, int c, int r ) {
    if ( sparseMatrix == NULL ) printf ( "Matriz vazia!\n" );
    else {
        typeNode *col = sparseMatrix;
        typeNode *lar = sparseMatrix;

        while ( col != NULL ) {
            while ( lar != NULL ) {
                if ( lar->row == r && lar->column == c ) {
                        printf ( "Encontrado o elemento %d\n", lar->value );
                        return lar->value;
                }
                lar = lar->right;
            }
            col = col->down;
            lar = col;
        }
    }
    printf ( "Nao existe elemento nessa posicao\n" );
}

void printList ( typeNode *sparseMatrix ) {
    if ( sparseMatrix == NULL ) printf ( "Matriz vazia!\n" );
    else {
        typeNode *aux2 = sparseMatrix;
        typeNode *aux = sparseMatrix;
        typeNode *lar = sparseMatrix;
        int l=0;
        while ( lar->right != NULL ) {
            lar=lar->right;
        }
        l = lar->column;

        int i, j, k;
        j=1;
        while ( aux2 != NULL ) {
            i=0;
            aux2 = aux2->down;
            while ( aux != NULL ) {
                while ( i < aux->column ) {
                    printf ( "[_] " );
                    i++;
                }
                if ( i == aux->column ) {
                    printf ( "[%d] ", aux->value );
                    aux = aux->right;
                    i++;
                }
                if ( aux == NULL ) {
                    while ( i<=l ) {
                        printf ( "[_] " );
                        i++;
                    }
                }
            }
            printf ( "\n" );
            if ( aux2 == NULL ) {
                printf ( "\n\n" );
                return;
            }
            while ( j < aux2->row ) {
                k=0;
                while ( k <= l  ) {
                    printf ( "[_] ");
                    k++;
                }
                printf ( "\n" );
                j++;
            }

            if ( j == aux2->row ) {
                aux=aux2;
                j++;
            }
        }
    }
}

void plus ( typeNode **esparse, int value, int col, int lin )
{
    if ( esparse == NULL )
        addValue ( esparse, value, col, lin );
    else
    {
        typeNode *aux = *esparse;
        typeNode *aux2 = NULL;

        while ( aux != NULL ){
            while ( aux2 != NULL ){
                if ( aux2->column == col && aux2->row == lin ){
                    aux2->value += value;
                    break;
                }
                aux2 = aux2->right;
            }
            aux = aux->down;
            aux2 = aux;
        }
    }
    addValue ( esparse, value, col, lin );
}

void plus_all ( typeNode **esparse, int value )
{
    if ( esparse == NULL )
        printf ( "\nMatriz vazia\n");
    else
    {
        typeNode *aux = *esparse;
        typeNode *aux2 = NULL;

        while ( aux != NULL )
        {
            while ( aux2 != NULL )
            {
                if ( aux2->value != 0 )
                    aux2->value += value;
                aux2 = aux2->right;
            }
            aux = aux->down;
            aux2 = aux;
        }
    }
}

int plus_all_all ( typeNode **esparse )
{
    int all_plus;

    if ( esparse == NULL )
        printf ( "\nMatriz vazia\n");
    else
    {
        typeNode *aux = *esparse;
        typeNode *aux2 = NULL;

        while ( aux != NULL )
        {
            while ( aux2 != NULL )
            {
                if ( aux2->value != 0 )
                    all_plus += aux2->value;
                aux2 = aux2->right;
            }
            aux = aux->down;
            aux2 = aux;
        }
    }
    return all_plus;
}

int return_dimension ( typeNode *esparse )
{
    typeNode *col = esparse;
    typeNode *row = esparse;
    int lin = 0, coll = 0;

    while ( col != NULL )
    {
        while ( row != NULL )
        {
            if ( row->down == NULL )
                if ( lin < row->row)
                    lin = row->row;
            row = row->down;
        }
        if ( col->right == NULL )
            if ( coll < col->column )
                coll = col->column;
        col = col->right;
        row = col;
    }
    return ( lin*coll );
}

int returnValue2 ( typeNode **sparseMatrix, int c, int r ) {
    typeNode *col = *sparseMatrix;
    typeNode *lar = *sparseMatrix;

    while ( col != NULL )
    {
        while ( lar != NULL )
        {
            if ( lar->row == r && lar->column == c )
                if ( lar->value != 0 )
                    return lar->value;
            else
                return 0;
            lar = lar->right;
        }
        col = col->down;
        lar = col;
    }
}

void plus_matrix_3 ( typeNode **esparse1, typeNode **esparse2, typeNode **esparse3 )
{
    typeNode *col = *esparse1;
    typeNode *lin = *esparse1;
    int aux;

    while ( col != NULL )
    {
        while ( lin != NULL )
        {
            aux = returnValue2 ( esparse2, lin->column, lin->row );
            if ( aux != 0 )
                addValue ( esparse3, lin->value + aux, lin->column, lin->row );
            else
                if ( lin->value != 0 )
                    addValue ( esparse3, lin->value, lin->column, lin->row );
            lin = lin->down;
        }
        col = col->right;
        lin = col;
    }
}


///FUNÇÃO PRINCIPAL
int main ( int argc, char **argv )
{
    typeNode *esparse = NULL;
    typeNode *esparse1 = NULL;
    typeNode *esparse2 = NULL;
    typeNode *esparse3 = NULL;

    FILE *archive = NULL;
    char *data, *lin, *col;
    int plus_alll, aux1, aux2;

    data = ( char* ) malloc ( sizeof ( char ) );
    lin = ( char* ) malloc ( sizeof ( char ) );
    col = ( char* ) malloc ( sizeof ( char ) );

    archive = fopen ( "matrix.txt", "rt+" );
    while ( !feof ( archive ) )
    {
        fscanf ( archive, "%s%s%s", lin, col, data );
        //addValue ( &esparse, atoi (data), atoi (lin), atoi (col) );
        addValue ( &esparse1, atoi (data), atoi (lin), atoi (col) );
        //addValue ( &esparse2, atoi (data), atoi (lin), atoi (col) );
    }
    fclose ( archive );
    printList ( esparse1 );

    archive = fopen ( "matrix1.txt", "rt+" );
    while ( !feof ( archive ) )
    {
        fscanf ( archive, "%s%s%s", lin, col, data );
        //addValue ( &esparse, atoi (data), atoi (lin), atoi (col) );
        //addValue ( &esparse1, atoi (data), atoi (lin), atoi (col) );
        addValue ( &esparse2, atoi (data), atoi (lin), atoi (col) );
    }
    fclose ( archive );
    printList ( esparse2 );

    aux1 = return_dimension ( esparse1 );
    printf ( "dim: %i\n", aux1 );
    aux2 = return_dimension ( esparse2 );
    printf ( "dim2: %i\n", aux2 );

    if ( aux1 > aux2 )
        plus_matrix_3( &esparse1, &esparse2, &esparse3 );
    else
        plus_matrix_3( &esparse2, &esparse1, &esparse3 );

    printList ( esparse3 );

/*
    printList ( esparse );
    plus ( &esparse, 5, 1, 5 );
    printList ( esparse );
    plus_all ( &esparse, 1000 );
    printList ( esparse );
    plus_alll = plus_all_all ( &esparse );
    printf ( "A soma de todos elementos e: %i\n", plus_alll );
*/
    return 0;
}
