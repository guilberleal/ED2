/*  UFMT-2021
    Arthur e Guilber
    trabalho 2-ED2
    Etapa Final 2, 3 e 4 manipulando os arquivos 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIM 1024 // tamanho chave
#define TAM 100	//tamanho tabela
//Estrutura
struct registro{
	int chave;
	char valor[3];
	struct registro *prox;
};
typedef struct registro Reg;
typedef Reg* Hash;//hash será um vetor alocado dinamicamente

//Prototipos
int hash(int mat, int tam);
int hashDois(int mat, int tam);
void inicializa(Hash *tab, int m);
Reg* aloca(int chave, char valor[3]);
void libera(Hash *tab, int m);
void insere(Hash *tab, int chave, char valor[3]);
void insereDois(Hash *tab, int chave, char valor[3]);
void imprime(Hash *tab, int m);
void LerArquivo(Hash *tab,int tam,char *nomeArq, int tipoFunc);
void LeArquivos(Hash *tab,int tam);
void colisoes(Hash *tab, int m);
//Funcao principal
int main(){
	int i;
	char opc;
	Hash *tab[TAM];//criando a tabela
    inicializa(tab,TAM);
	while(1){
		printf("Digite o tamanho dos arquivos que deseja inserir na tabela:\n");
   	    scanf("%d",&i);
		LeArquivos(tab,i);
		printf("Se deseja parar digite 'n' \n");
	    scanf("%s", &opc);
	    if(opc=='n'){
	        break;
    	}
	}

}
//Funcao hash1 metodo da divisao (linear)
int hash(int mat, int tam){
    return mat%tam;
}
// Funcao hash 2
int hashDois(int mat, int tam){
	//return floor( tam*((0.61*mat)mod 1) );
}
//Funcao inicializa 
void inicializa(Hash *tab, int m){
    int i;
    for (i=0; i<m; i++){
        tab[i]=NULL;
    }
}
//Funcao que aloca
Reg* aloca(int chave, char valor[3]){
	Reg *novo = (Reg*) malloc(sizeof(Reg));
	novo->chave = chave;
	strncpy(novo->valor,valor,3);
	novo->prox= NULL;
	return novo;
}

//Funcao que limpa a estrutura
void libera(Hash *tab, int m){
    int i;
    for(i=0; i<m; i++){
        if(tab[i]){
            Reg *p= tab[i];
            Reg *q;
            while(p){
                q=p;
                p=p->prox;
                free(q);
            }

        }
    }
}

//insere na tabela hash a primeira funcao
void insere(Hash *tab, int chave, char valor[3]){
	int h = hash(chave,TAM);
	Reg *p = tab[h];
	Reg *ant= NULL;
	while((p !=NULL) && (p->chave !=chave)){
		ant = p;
		p = p->prox;
	}
	
	if(p){
		strncpy(p->valor,valor,3);
		return;
	}
	
	Reg *novo = aloca(chave,valor);
	if(!ant){
		tab[h] = novo;
	}else{
		ant->prox = novo;		
	}
}
//Funcao que insere na tabela hash a segunda funcao
void insereDois(Hash *tab, int chave, char valor[3]){
	int h = hashDois(chave, TAM);
	Reg *p = tab[h];
	Reg *ant= NULL;
	while((p !=NULL) && (p->chave !=chave)){
		ant = p;
		p = p->prox;
	}
	
	if(p){
		strncpy(p->valor,valor,3);
		return;
	}
	
	Reg *novo = aloca(chave,valor);
	if(!ant){
		tab[h] = novo;
	}else{
		ant->prox = novo;		
	}
}
// Funcao que imprime todos os valores 
void imprime(Hash *tab, int m){
	int i;
	Reg *p;
	for(i=0;i<m;i++){
		printf("%d\n",i);	
		if(tab[i]){
			p = tab[i];
			while(p){
				printf("[%d - %s - %d]\t\n",p->chave,p->valor,p->prox);
				p = p->prox;
			}
		}else printf("NULL\n");
		printf("\n---------------");
	}
}
void LerArquivo(Hash *tab,int tam,char *nomeArq, int tipoFunc){
	
	FILE *arq;	
	arq = fopen(nomeArq,"r");
	
	if(arq == NULL){
		printf("\nErro no arquivo\n");
	}
	
	//LE DO ARQUIVO
	int key/*,i*/; 
	char val[3];
	//for( i=0;i<tam;i++){
    while( fscanf(arq,"%d\t%s",&key,&val)!=EOF){
		//fscanf(arq,"%d\t%s",&key,&val);
		printf("%d %s\n",key,val);		
		if(tipoFunc==1){
			insere(tab,key,val);
		}else{
			insereDois(tab,key,val);
		}
	}
	fclose(arq);
}
void LeArquivos(Hash *tab,int tam){	
	int i;
	printf("\n5 arquivos do tipo 1 do tamanho %d:", tam);	
	for( i=0;i<5;i++){
		char nome[50];
		itoa(tam,nome,10);
		char aux[50] = "_Par_";
		strcat(nome,aux);
		char aux1[1];
		int aux2 = i+1;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		printf("\n%s\t",nome);
		strcat(nome,".txt");
		LerArquivo(tab,tam,nome,1);
		colisoes(tab,TAM);
		//imprime(tab,TAM);
		libera(tab,TAM);
		printf("\n");
	}
	printf("\n5 arquivos do tipo 2 do tamanho %d:", tam);
	for(i=0;i<5;i++){
		char nome[50];
		itoa(tam,nome,10);
		char aux[50] = "_Ale_";
		strcat(nome,aux);
		char aux1[1];
		int aux2 = i+1;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		printf("\n%s\t",nome);
		strcat(nome,".txt");
		LerArquivo(tab,tam,nome,1);
		colisoes(tab,TAM);
		//imprime(tab,TAM);
		libera(tab,TAM);
		printf("\n");
	}
}
//calculando o numero de colisoes
void colisoes(Hash *tab, int m){
	int i, cont=0;
	for(i=0;i<m;i++){
		if(tab[i]){
			Reg *p = tab[i];
				if(p->prox){
					cont = cont +1;
				}
			}
		}
	printf("\nColisoes: \t%d",cont);
}
