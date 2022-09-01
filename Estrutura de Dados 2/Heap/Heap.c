/**
    UNIVERSIDADE FEDERAL DE MATO GROSSO
    DATA: 07/05/2014
    ALUNOS: GIONAVA HIROMI TANITA, ALEX MATOS IUASSE
    PROFESSOR: IVAIRTON
    ESTRUTURA DE DADOS 2
    ALGORITMO DE UM HEAP PARA GERENCIAMENTO DE FILAS DE UM BANCO
**/

/** CABEÇALHO **/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** ESTRUTURAS **/
struct heap {
    int priority;
    int identification;
};
typedef struct heap typeHeap;

/** PROTÓTIPOS **/
int leftChild ( int i ); /** INDICE DO FILHO ESQUERDO **/
int rightChild ( int i ); /** INDICE DO FILHO DIREITO **/
int parent ( int i ); /** INDICE DO PAI **/
void printing ( typeHeap heap[], int tam ); /** PRINTAR HEAP **/
int insertHeap ( typeHeap heap[], int N ); /** INSERIR NO HEAP **/
int remove_heap ( typeHeap heap[], int tam ); /** REMOVER DO HEAP **/
void buildHeap ( typeHeap *heap, int i, int N ); /** CONSTROI HEAP **/

/** FUNCTIONS **/
/*i: elemento da ser inserido, N: numero de elementos no vetor */
void buildHeap ( typeHeap heap[], int i, int N ) {
	int parentPosition, LeftChildPosition, RightChildPosition, biggest, aux;

	LeftChildPosition = leftChild ( i );
	RightChildPosition = rightChild ( i );

	if ( ( LeftChildPosition < N ) && ( heap[LeftChildPosition].priority > heap [i].priority ) ) {
		biggest = LeftChildPosition;
	}
	else {
		biggest = i;
	}

	if ( ( RightChildPosition < N ) && ( heap[RightChildPosition].priority > heap [biggest].priority ) ) {
		 biggest = RightChildPosition;
	}
	if ( biggest != i ) {
		aux = heap[i].priority;
		heap[i].priority = heap[biggest].priority;
		heap[biggest].priority = aux;

        aux = heap[i].identification;
		heap[i].identification = heap[biggest].identification;
		heap[biggest].identification = aux;

		buildHeap ( heap, biggest, N );
	}
}

int insertHeap ( typeHeap heap[], int N ) {
	int i;
	for ( i=N/2; i>=0; i-- ) {
		buildHeap ( heap, i, N );
	}
}

int leftChild ( int i ) {
    return ( ( i*2 )+1 );
}

int rightChild ( int i ) {
    return ( ( i*2 )+2 );
}

int parent ( int i ) {
    return floor ( ( i-1 )/2 );
}

void printing ( typeHeap heap[], int tam ) {
	int i;
	for ( i=0; i<tam; i++ ) {
		if ( heap[i].priority!=0 ) printf ( "| Posição: %d\t", i );
	}
	printf ( "|\n" );
		for ( i=0; i<tam; i++ ) {
		if ( heap[i].priority!=0 ) printf ( "| Prioridade: %d  Identificação: %d", heap[i].priority, heap[i].identification );
	}
	printf ( "|\n\n" );
}

int remove_heap ( typeHeap heap[], int tam ) {
	int removido;

    while ( heap[tam].identification==0 ) tam--;

	removido = heap[0].identification;

	heap[0].priority = heap[tam].priority;
	heap[0].identification = heap[tam].identification;
	heap[tam].priority = 0;

    printf ( "Cliente %d atendido\n", removido );
	return removido;
}

int verifica_prioridade ( )
{
    int x;
    scanf ( "%i", &x );
    if ( x > 0 && x < 6 )
        return x;
    else
    {
        printf ( "\nPrioridade digitada errada\n" );
        printf ( "Lista de prioridades, quanto maior a prioridade mais rapido o atendimento:\n\n" );
        printf ( "5- Idosos\n4- Gestantes\n3- Correntistas\n2- Empresas\n1- Visitantes\n\n" );
        printf ( "Prioridade de um cliente: ");
        verifica_prioridade ( );
    }
}

/** FUNÇÃO PRINCIPAL **/
int main ( int argc, char **argv )
{
    typeHeap heap[1000];
    typeHeap client;
    int tam=0;
    int option=0;
    int removido;

    printf ( "Bem vindo ao sistema de atendimento de filas com prioridades\n\n" );
    printf ( "Lista de prioridades, quanto maior a prioridade mais rapido o atendimento:\n\n" );
    printf ( "5- Idosos\n4- Gestantes\n3- Correntistas\n2- Empresas\n1- Visitantes\n\n" );
    while ( option!=5 ) {
        printf ( "Lista de opções do programa:\n" );
        printf ( "\t1- Inserir novo cliente\n\t2- Atender um cliente\n\t3- Visualizar quantidade de clientes" );
        printf ( "\n\t4- Corrigir prioridade e identificação de um cliente\n\t5- Sair\n" );
        printf ( "Digite sua opção: ");
        scanf ( "%d", &option );
        if ( option < 1 || option > 5 ) printf ( "Opcao invalida\n" );
        else {
            switch ( option ) {
            case 1 :
                /* Insere cliente na primeira posicao vaga do heap */
                printf ( "\nIdentificação de um cliente: ");
                scanf ( "%d", &heap[tam].identification );
                printf ( "Prioridade de um cliente: ");
                heap[tam].priority = verifica_prioridade ( );
                //scanf ( "%d", &heap[tam].priority );
                printf ( "\n" );
                tam++;
                break;
            case 2:
                /* Monta o heap e remove o primeiro elemento que é o de maior prioridade */
                printf ( "\n" );
                insertHeap ( &(*heap), tam );
                removido = remove_heap ( &(*heap), tam );
                printf ( "\n" );
                break;
            case 3:
                /* Imprime o heap */
                printing ( heap, tam );
                break;
            case 4:
                /* Corrige uma inserção de cliente errada */
                tam--;
                scanf ( "%d", &heap[tam].priority );
                scanf ( "%d", &heap[tam]. identification );
                tam++;
                break;
            case 5:
                break;
            }
        }
    }

    return 0;

}
