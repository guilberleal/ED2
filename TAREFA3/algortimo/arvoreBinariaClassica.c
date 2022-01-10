/*  UFMT-2021
    Arthur e Guilber
    trabalho 3-ED2
    Arvore Binaria Classica
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct estr_arv_bin{
    struct estr_arv_bin *esq;
    struct estr_arv_bin *dir;
    int valor;
};
typedef struct estr_arv_bin tipo_arv_bin;

//PROTOTIPOS
//MANIPULACAO ARVORE
tipo_arv_bin *alocaNovoNoArvBin(int vl);
void insereArvBin(tipo_arv_bin **arv, int valor);
void percursoPreOrdem(tipo_arv_bin *arv);
void percursoEmOrdem(tipo_arv_bin *arv);
void percursoPosOrdem(tipo_arv_bin *arv);
void arvoreVazia(tipo_arv_bin **arv);
void insereArvore(tipo_arv_bin **arv);
int verificaValor(tipo_arv_bin *arv, int vl);
int qtdNoArvore(tipo_arv_bin *arv);
int alturaArvore(tipo_arv_bin *arv);
void imprimeNoFolhas(tipo_arv_bin *arv);
void imprimeNivel(tipo_arv_bin *arv);
void imprimePorNivel(tipo_arv_bin *arv, int nivel);
//MANIPULACAO ARQUIVO
void LeArquivos(tipo_arv_bin *arv,int tam, int numeracao);
void LerArquivo(tipo_arv_bin *arv,int tam, char *nomeArq);
int main(){
    int i, num, h;
    tipo_arv_bin *arvore;
    arvore=NULL;
    printf("Digite o tamanho dos arquivos que deseja inserir na tabela:\n");
    scanf("%d",&i);
    printf("Digite o numero do arquivo:\n");
    scanf("%d",&num);
    LeArquivos(arvore,i,num);
    return 0;
}
//FUNCAO QUE LE ARQUIVO E COLOCA NA ARVORE
void LerArquivo(tipo_arv_bin *arv,int tam, char *nomeArq){

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
		insereArvBin(&arv, valor);
	}
	int h=alturaArvore(arv);
    printf("altura arvore:%d\n",h);
	fclose(arq);
}
void LeArquivos(tipo_arv_bin *arv,int tam, int numeracao){
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
//FUNCAO QUE PERCORRE POS ORDEM
void percursoPosOrdem(tipo_arv_bin *arv){
    if(arv!=NULL){
        percursoPreOrdem(arv->esq);
        percursoPreOrdem(arv->dir);
        printf(" %d ", arv->valor);
    }
}
//FUNCAO QUE PERCORRE EM ORDEM
void percursoEmOrdem(tipo_arv_bin *arv){
    if(arv!=NULL){
        percursoPreOrdem(arv->esq);
        printf(" %d ", arv->valor);
        percursoPreOrdem(arv->dir);
    }
}
//FUNCAO QUE IMPRIME POR NIVEL CHAMANDO A ORDENA
void imprimeNivel(tipo_arv_bin *arv){
    int h=alturaArvore(arv);
    int i;
    for(i=0;i<=h;i++){
        imprimePorNivel(arv,i);
    }
}
//FUNCAO QUE ORDENA A IMPRESSAO TODOS OS VALORES POR NIVEL
void imprimePorNivel(tipo_arv_bin *arv, int nivel){
    if(arv==NULL){
        return;
    }
    if(nivel==1){
        printf(" %d ",arv->valor);
    }else if(nivel>1){
        imprimePorNivel(arv->esq,nivel-1);
        imprimePorNivel(arv->dir,nivel-1);
    }
}


//FUNCAO QUE IMPRIME TODOS OS NOS FOLHAS
void imprimeNoFolhas(tipo_arv_bin *arv){
    if(arv!=NULL){
      if((arv->dir==NULL)&&(arv->esq==NULL)){
            printf(" [%d] ", arv->valor);
      }else{
            imprimeNoFolhas(arv->esq);
            imprimeNoFolhas(arv->dir);
      }
    }
}


// FUNCAO QUE VERIFICA E RETORNA A ALTURA DA ARVORE
int alturaArvore(tipo_arv_bin *arv){
    if(arv!=NULL){
       if((arv->dir==NULL) && (arv->esq)){
            return 0;
       }else{
            int altura_dir, altura_esq;
            altura_dir= alturaArvore(arv->dir);
            altura_esq= alturaArvore(arv->esq);
            if(altura_dir>altura_esq){
                return altura_dir+1;
            }else{
                return altura_esq+1;
            }
       }
    }
    return 0;
}
//FUNCAO QUE CONTA QUANTIDADE DE NOS E RETORNA
int qtdNoArvore(tipo_arv_bin *arv){
    if(arv!=NULL){
        int qtdDir, qtdEsq, valor;
        qtdDir=qtdNoArvore(arv->dir);
        qtdEsq=qtdNoArvore(arv->esq);
        valor=qtdDir+qtdEsq+1;
        return valor;

    }else{
        return 0;
    }
}
//FUNCAO QUE VERIFICA VALOR
int verificaValor(tipo_arv_bin *arv, int vl){
    if(arv==NULL){
        return 0;
    }else if(arv->valor==vl){
        return 1;
    }else if(arv->valor>vl){
        return verificaValor(arv->esq, vl);
    }else{
        return verificaValor(arv->dir, vl);
    }

}
//FUNCAO QUE INSERE UM VALOR NA ARVORE
void insereArvore(tipo_arv_bin **arv){
    int valor,opc;
    while(1){
        printf("Deseja inserir um novo valor: 1-SIM OU 2-NÃO\n");
        scanf("%d", &opc);
        if(opc==1){
            printf("Digite o valor que deseja inserir\n");
            scanf("%d",&valor);
            insereArvBin(arv, valor);
        }else if(opc==2){
            break;
        }
    }
}

//FUNCAO QUE ALOCA NOVO NO NA ARVORE
tipo_arv_bin *alocaNovoNoArvBin(int vl){
    tipo_arv_bin *novo_no;
    novo_no=(tipo_arv_bin*) malloc(sizeof(tipo_arv_bin));
    novo_no->valor=vl;
    novo_no->esq=NULL;
    novo_no->dir=NULL;
    return novo_no;
}
//FUNCAO QUE INSERE NOVO VALOR
void insereArvBin(tipo_arv_bin **arv, int valor){
    if((*arv)==NULL){
        (*arv)= alocaNovoNoArvBin(valor);
    }else{
        if(valor < (*arv)->valor){
            insereArvBin(&(*arv)->esq, valor);
        }else{
            insereArvBin( &(*arv)->dir, valor);
        }
    }
}

//FUNCAO QUE PERCORRE EM PRE ORDEM
void percursoPreOrdem(tipo_arv_bin *arv){
    if(arv!=NULL){
        printf(" %d ", arv->valor);
        percursoPreOrdem(arv->esq);
        percursoPreOrdem(arv->dir);
    }
}




