#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
	int matricula;
	float cr;
	struct aluno *prox;
}TAluno;

typedef TAluno *Hash;
//FUNCAO HASH
int hash(int mat,int tam){
	return mat % tam;
}
//INICIALIZA TABELA
void inicializa(Hash *tab,int m){
	int i;
	for( i = 0; i< m; i++){
		tab[i] = NULL;
	}
}
//ALOCA ALUNO
TAluno *aloca(int mat, float cr){
	TAluno *novo;
	novo = (TAluno*)malloc(sizeof(TAluno));
	novo->cr = cr;
	novo->matricula = mat;
	novo->prox = NULL;
	return novo;
}
//INSERE NA TABELA
void insere(Hash *tab, int m, int mat, float cr){
	int h = hash(mat,m);
	TAluno *p = tab[h];
	TAluno *ant = NULL;
	
	while((p != NULL) && (p->matricula != mat)){
		ant = p;
		p = p->prox;
	}
	TAluno *novo = aloca(mat,cr);
	if(!ant){
		tab[h] = novo;
	}
	else{
		ant->prox = novo;
	}
}
//IMPRIME TABELA
void imprime(Hash *tab,int m){
	int i;
	for( i = 0; i< m;i++){
		printf("%d: ",i);
		if(tab[i]){
			TAluno *p = tab[i];
			printf("\n");
			while(p){
				printf("\t%d\t%f\t%p\n",p->matricula,p->cr,p->prox);
				p = p->prox;
			}
		}
		else{
			printf("NULL\n");
		}
	}
}


int main(){
	int m;
	printf("Digite m (tamanho da tabela hash)... ");
	scanf("%d",&m);
	
	Hash *tab[m];
	inicializa(tab,m);
	insere(tab,m,12,5.8);
	insere(tab,m,3,7.2);
	insere(tab,m,12,4.5);
	insere(tab,m,18,9.1);
	insere(tab,m,9,6.3);
	insere(tab,m,13,9);
	
	imprime(tab,m);
	
	
	
	
	
	
	return 0;
}
