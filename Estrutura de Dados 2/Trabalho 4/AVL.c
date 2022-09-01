/** 
	UNIVERSIDADE FEDERAL DE MATO GROSSO
	ARVORE AVL
	ALEX MATOS IUASSE
**/

/** CABEÇALHO **/
#include <stdio.h>
#include <stdlib.h>

/** ESTRUTURA **/
struct avl{
	struct avl *left;
	struct avl *right;
	int data;
	int fb;
};
typedef struct avl type_avl;

/** PROTÓTIPOS **/
int insertAVL ( type_avl **T, int data );
void verifyInsRight ( type_avl **T );
void verifyInsLeft ( type_avl **T );
void rotRight ( type_avl **T );
void rotLeft ( type_avl **T );
void print ( type_avl *T );

/** FUNÇÕES **/
void rotLeftRight ( type_avl **T ){
	type_avl *u, *v;
	u = (*T)->left;
	v = u->right;
	u->right = v->left;
	v->left = u;
	(*T)->left = v->right;
	v->right = *T;
	if ( v->fb == -1 ){
		(*T)->fb = 1;
		u->fb = 0;
	}else if ( v->fb == 0 ){
		(*T)->fb = 0;
		u->fb = 0;
	}else if ( v->fb == 1 ){
		(*T)->fb = 0;
		u->fb = -1;
	}
	*T = v;	
}

void rotRightLeft ( type_avl **T ){
	type_avl *u, *v;
	u = (*T)->right;
	v = u->left;
	u->left = v->right;
	v->right = u;
	(*T)->right = v->left;
	v->left = *T;
	if ( v->fb == -1 ){
		(*T)->fb = 0;
		u->fb = 1;
	}else if ( v->fb == 0 ){
		(*T)->fb = 0;
		u->fb = 0;
	}else if ( v->fb == 1 ){
		(*T)->fb = -1;
		u->fb = 0;
	}
	*T = v;
}

void rotRight ( type_avl **T ){
	type_avl *u;
	u = (*T)->left;
	(*T)->left = u->right;
	u->right = *T;
	(*T)->fb = 0;
	u->fb = 0;
	*T = u;
}

void rotLeft ( type_avl **T ){
	type_avl *u;
	u = (*T)->right;
	(*T)->right = u->left;
	u->left = *T;
	(*T)->fb = 0;
	u->fb = 0;
	*T = u;
}

void verifyInsRight ( type_avl **T ){
	type_avl *u;
	u = (*T)->right;
	if ( u->fb == 1 ){
		rotLeft ( T );
	}
	else{
		rotRightLeft ( T );
	}
	(*T)->fb = 0;
}

void verifyInsLeft ( type_avl **T ){
	type_avl *u;
	u = (*T)->left;
	if ( u->fb == -1 ){
		rotRight ( T );
	}
	else{
		rotLeftRight ( T );
	}	
	(*T)->fb = 0;
}

int insertAVL ( type_avl **T, int data ){
	int flagSucess;
	flagSucess = 0;
	
	/** Verifica se a raiz informada como parâmetro é nula. Nesse caso será alocado um
		novo nó na memória. **/
	if ( *T == NULL){
		*T = ( type_avl* ) malloc ( sizeof(type_avl) );
		(*T)->left = NULL;
		(*T)->right = NULL;
		(*T)->data = data;
		(*T)->fb = 0;
		return 1;	/** Ao inserir novo-nó, será retornado 1 (verdadeiro), de modo a modificar
					a variável 'flagsucess' do procedimento pai (aquele que chamou o
					procedimento de maneira recursiva). Note que a execução desta 
					função terminaria aqui. **/
	}
	
	/** Verifica se o dado a ser inserido é menor que o valor da raiz da sub-árvore atual.
		nesse caso, será neessário descer a esquerda da árvore. **/
	if ( (*T)->data > data ){
		//Executa a chamada recursiva do filho esquerdo
		flagSucess = insertAVL ( &(*T)->left, data );
		
		/** Se ocorrer sucesso na inserção, verifica o balanceamento da árvore, executando uma rotação
			(a ser verificada) se necessário. **/
		if ( flagSucess ) {
			switch ( (*T)->fb ) {
				case 1: //Caso dir > esq, entao gera equilibrio, add um elemento a esq
					(*T)->fb = 0;
					flagSucess = 0;
					break;
				case 0: //Alturas iguais, entao es se torna maior que dir
					(*T)->fb = -1;
					break;
				case -1: //Sera preciso executar uma rotação (a ser verificada).
					verifyInsLeft ( &(*T) );
					flagSucess = 0;
					break;
			}
		}			
	} else /** Se não é uma inserção à esq, entra é à dir. Nesse caso será necessário
			descer à direita da arv **/
	if ( (*T)->data < data ){ 
		//Executa a chamda recursiva com o filho à direita
		flagSucess = insertAVL ( &(*T)->right, data );

		/** Se ocorrer sucesso na inserção, verifica o balanceamento da árvore, executando uma rotação
			(a ser verificada) se necessário. **/
		if ( flagSucess ) {
			switch ( (*T)->fb ) {
				case -1: //Caso dir < esq, entao gera equilibrio, add um elemento a esq
					(*T)->fb = 0;
					flagSucess = 0;
					break;
				case 0: //Alturas iguais, entao dir se torna maior que esq
					(*T)->fb = 1;
					break;
				case 1: //Sera preciso executar uma rotação (a ser verificada).
					verifyInsRight ( &(*T) );
					flagSucess = 0;
					break;
			}
		}
	} else {/** Caso valor inserido ja esteja presente na AVL (não faz nada) **/
		flagSucess = 0;
	}
	return flagSucess;	
}

void print ( type_avl *T ){
	if ( T != NULL ){
		print ( T->left );
		printf ( "[ %i ]\t", T->data );
		print ( T->right );
	}
}

void print2 ( type_avl *T ){
	if ( T != NULL ){
		print ( T->left );
		print ( T->right );
		printf ( "[ %i ]\t", T->data );
	}
}

void print3 ( type_avl *T ){
	if ( T != NULL ){
		printf ( "[ %i ]\t", T->data );
		print ( T->left );
		print ( T->right );
	}
}

/** PRINCIPAL **/
int main ( int argc, char **argv ){
	type_avl *avl = NULL;
	int v[] = {10,20,30,40,35,6,0};
	int i;
	
	for ( i = 0; i < 7; i++ ){
		insertAVL ( &avl, v[i] );
	}
	
	//print ( avl );
	//puts("");
	//print2 ( avl );
	//puts("");
	print3 ( avl );
	puts("");

	return 0;
}
