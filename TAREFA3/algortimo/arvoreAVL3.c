/*  UFMT-2021
    Arthur e Guilber
    trabalho 3-ED2
    Arvore Binaria Classica
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct no{
    struct no *esq;
    struct no *dir;
    int valor;
    int altura;
    int rot;
};
typedef struct no No;
//PROTOTIPOS
//MANIPULACAO ARVORE
void imprimir(No *raiz, int nivel);
No *novoNo(int x);
int maior(int a, int b);
int alturaDoNo(No *no);
int fatorDeBalanceamento(No *no);
No *balancear(No *raiz);
No *rotacaoEsquerda(No *r);
No *rotacaoDireita(No *r);
No* rotacaoDireitaEsquerda(No *r);
No *inserir(No *raiz, int x);
//MANIPULACAO ARQUIVO
void LeArquivos(No *arv,int tam, int numeracao);
void LerArquivo(No *arv,int tam, char *nomeArq);

int main(){
    int i, num, h;
    No *raiz;
    raiz=NULL;
    No *arvore;
    arvore=NULL;
    printf("Digite o tamanho dos arquivos que deseja inserir na tabela:\n");
    scanf("%d",&i);
    printf("Digite o numero do arquivo:\n");
    scanf("%d",&num);
    LeArquivos(arvore,i,num);
    /*raiz=inserir(raiz, 10);
    raiz= inserir(raiz, 30);
    raiz=inserir(raiz, 15);
    raiz=inserir(raiz, 8);
    raiz=inserir(raiz, 6);
    imprimir(raiz, 1);*/
    return 0;
}
//FUNCAO QUE LE ARQUIVO E COLOCA NA ARVORE
void LerArquivo(No *arv, int tam, char *nomeArq){

	FILE *arq;
	arq = fopen(nomeArq,"r");

	if(arq == NULL){
		printf("\nErro no arquivo\n");
	}

	//LE DO ARQUIVO
	int valor,i;
	char vl[6];
	//for( i=0;i<tam;i++){
	while( (fscanf(arq,"%s\n", vl))!=EOF ){
		//fscanf(arq,"%d\n",&valor);
		valor = atoi(vl);
		printf("%d\n",valor);
		arv=inserir(arv, valor);
	}
	//int h=alturaArvore(arv);
    printf("altura arvore:%d\n",arv->altura);
    printf("rotacoes para balancear:%d\n",arv->rot);
	fclose(arq);
}

void LeArquivos(No *arv,int tam, int numeracao){
		char nome[50];
		itoa(tam,nome,10);
		char aux[50] = "_Algoritmo_";
		strcat(nome,aux);
		char aux1[1];
		int aux2 = numeracao;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		printf("\n%s\t",nome);
		strcat(nome,".txt");
		LerArquivo(arv,tam,nome);
		printf("\n");
}

No *novoNo(int x){
    No *novo= malloc(sizeof(No));
    if(novo){
        novo->valor= x;
        novo->esq= NULL;
        novo->dir= NULL;
        novo->altura=0;
        novo->rot=0;
    }else{
        printf("Erro ao alocar no em novo no\n");
    }
    return novo;
}

int maior(int a, int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}

int alturaDoNo(No *no){
    if(no==NULL){
        return -1;
    }else{
        return no->altura;
    }
}

int fatorDeBalanceamento(No *no){
    if(no){
        return (alturaDoNo(no->esq)-alturaDoNo(no->dir));
    }else{
        return 0;
    }
}
//Funcao para rotacao esquerda
No *rotacaoEsquerda(No *r){
    No *y, *f;

    y= r->dir;
    f= y->esq;

    y->esq= r;
    r->dir= f;

    r->altura= maior(alturaDoNo(r->esq),alturaDoNo(r->dir))+1;
    y->altura= maior(alturaDoNo(y->esq),alturaDoNo(y->dir))+1;

    return y;
}

//Funcao para rotacao direita
No *rotacaoDireita(No *r){
    No *y, *f;

    y= r->esq;
    f= y->dir;

    y->dir= r;
    r->esq= f;

    r->altura= maior(alturaDoNo(r->esq),alturaDoNo(r->dir))+1;
    y->altura= maior(alturaDoNo(y->esq),alturaDoNo(y->dir))+1;

    return y;
}

//funcao rotacao direita esquerda
No* rotacaoDireitaEsquerda(No *r){
    r->dir= rotacaoDireita(r->dir);
    return rotacaoEsquerda(r);
}

//funcao rotacao esquerda direita
No* rotacaoEsquerdaDireita(No *r){
    r->esq= rotacaoEsquerda(r->esq);
    return rotacaoDireita(r);
}

No *inserir(No *raiz, int x){
    if(raiz==NULL){
        return novoNo(x);
    }else{
        if(x < raiz->valor){
            raiz->esq= inserir(raiz->esq, x);
            raiz->rot= raiz->rot +1;
        }else if(x > raiz->valor){
            raiz->dir= inserir(raiz->dir, x);
            raiz->rot= raiz->rot +1;
        }else{
            printf("\n Insercao nao realizada\n %d elemento com erro\n",x);
        }
    }
    raiz->altura= maior(alturaDoNo(raiz->esq),alturaDoNo(raiz->dir))+1;
    raiz=balancear(raiz);

    return raiz;
}

No *balancear(No *raiz){
    int fb= fatorDeBalanceamento(raiz);
    if(fb < -1 && fatorDeBalanceamento(raiz->dir)<=0){
        raiz=rotacaoEsquerda(raiz);
        raiz->rot= raiz->rot +1;

    }else if(fb > 1 && fatorDeBalanceamento(raiz->esq)>=0){
        raiz=rotacaoDireita(raiz);
        raiz->rot= raiz->rot +1;

    }else if(fb > 1 && fatorDeBalanceamento(raiz->esq)< 0){
        raiz=rotacaoEsquerdaDireita(raiz);
        raiz->rot= raiz->rot +1;

    }else if(fb < -1 && fatorDeBalanceamento(raiz->dir) > 0){
        raiz=rotacaoDireitaEsquerda(raiz);
        raiz->rot= raiz->rot +1;
    }

    return raiz;
}

void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->dir, nivel +1);
        printf("\n \n");
        for(i=0; i<nivel; i++){
            printf("\t");
        }
        printf("%d",raiz->valor);
        imprimir(raiz->esq, nivel+1);
    }

}
