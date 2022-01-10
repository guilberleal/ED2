#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMTAB 100
#define LIM 1024

//Criação das estruturas de registro e a tabela HASH
typedef struct registro{
	int chave;
	char valor[3];
	struct registro *prox;
}Reg;
typedef Reg* Hash;

//Funcao hash1
int hash(int chave, int tam){
	return chave % tam;
}
//Funcao hash2
int hash2(int chave){
	return chave * 0.09;
}

void limpaTabela(Hash *tab, int m);
Reg* aloca(int chave, char valor[3]);
void insere(Hash *tab, int chave, char valor[3]);
void insereDois(Hash *tab, int chave, char valor[3]);
void imprime(Hash *tab, int m);
void colisoes(Hash *tab, int m);
void geraVetorAleatorio(int *vetAux,Reg *tab,int tam, int chave);
void geraVetorAleatorioPar(int *vetAux,Reg *tab,int tam, int chave);
void geraArquivo(Reg *tab, int nElementos, int tipoEntrada, char nomeARQ[50]);
void SalvarArquivo(Hash *tab,int tam,char *nomeArq);
void LerArquivo(Hash *tab,int tam,char *nomeArq);
void GeraArquivos(Hash *tab, int tam);
void LeArquivos(Hash *tab,int tam);

//funcao principal
int main(){
	
	
	Hash *tab[TAMTAB];
	limpaTabela(tab,TAMTAB);
	
	printf("\nInserindo valores na tabela HASH TIPO 1");
	GeraArquivos(tab,50);
	GeraArquivos(tab,100);
	GeraArquivos(tab,150);
	printf("\nValores gerados com sucesso!");
	printf("\nCarregando valores na tabela HASH TIPO 2");
	LeArquivos(tab,50);
	LeArquivos(tab,100);
	LeArquivos(tab,150);
		
	printf("\nFIM\n");
	return 0;
}

//inicializa a tabela com os valores null
void limpaTabela(Hash *tab, int m){
	int i;
	for( i=0; i<m;i++){
		tab[i] = NULL;
	}
}

//aloca um no fora da estrutura
Reg* aloca(int chave, char valor[3]){
	Reg *novo = (Reg*) malloc(sizeof(Reg));
	novo->chave = chave;
	strncpy(novo->valor,valor,3);
	novo->prox= NULL;
	return novo;
}

//insere o no dentro da tabela
void insere(Hash *tab, int chave, char valor[3]){
	int h = hash(chave,TAMTAB);
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
//insere usando a segunda hash
void insereDois(Hash *tab, int chave, char valor[3]){
	int h = hash2(chave);
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
//imprime todos os valores dentro da estrutura
void imprime(Hash *tab, int m){
	int i;
	for( i=0;i<m;i++){
		printf("\n%d\n",i);	
		if(tab[i]){
			Reg *p = tab[i];
			while(p){
				printf("[%d - %s - %d]\t\n",p->chave,p->valor,p->prox);
				p = p->prox;
			}
		}else printf("NULL\n");
		printf("\n---------------");
	}
}
//calcula as colisoes
void colisoes(Hash *tab, int m){
	int cont = 0;
	int i;
	for( i=0;i<m;i++){
		if(tab[i]){
			Reg *p = tab[i];
				if(p->prox){
					cont = cont +1;
				}
			}
		}
	printf("\nColisoes: \t%d",cont);
}
//gera o vetor aleatorio
void geraVetorAleatorio(int *vetAux,Reg *tab,int tam, int chave){
	int i,j;
	int vetor[1024];
	
	for( i=0;i<1024;i++){
		vetor[i] = i;
	}
	
	for( i=0;i<tam+1;i++){
		int key = rand() * LIM / RAND_MAX;
		for( j=0;j<1024;j++){
			if(key == vetor[j]){
				if(key > 0){
					vetAux[i] = vetor[j];
					char valorRandom[3] = "aaa";
					
					valorRandom[0] = 'a'+(char)(rand()%26);
					valorRandom[1] = 'a'+(char)(rand()%26);
					valorRandom[2] = 'a'+(char)(rand()%26);
		
					insere(tab,vetAux[i],valorRandom);				
				}else{
					key = key * -1;
					vetAux[i] = vetor[j];
					char valorRandom[3] = "aaa";
					
					valorRandom[0] = 'a'+(char)(rand()%26);
					valorRandom[1] = 'a'+(char)(rand()%26);
					valorRandom[2] = 'a'+(char)(rand()%26);	
					insere(tab,chave,valorRandom);
				}
				vetor[j] = -1;
			}
		}
	}
}
//gera o vetor aleatorio somente de numeros pares				
void geraVetorAleatorioPar(int *vetAux,Reg *tab,int tam, int chave){
	
	int vetor[1024];
	int i,j;
	for( i=0;i<1024;i++){
		vetor[i] = i;
	}
	for( i=0;i<tam;i++){
		int key = rand() * LIM / RAND_MAX;
		for( j=0;j<1024;j++){
			if(key == vetor[j]){
				if(key > 0){
					vetAux[i] = vetor[j];
					char valorRandom[3];
					
					valorRandom[0] = 'a'+(char)(rand()%26);
					valorRandom[1] = 'a'+(char)(rand()%26);
					valorRandom[2] = 'a'+(char)(rand()%26);
		
					if(key % 2 == 0){
						vetAux[i] = key;
						insere(tab,vetAux[i],valorRandom);
					}else{
						key = key+1;
						vetAux[i] = key;
						insere(tab,vetAux[i],valorRandom);
					}
				}else{
					key = key * -1;
					vetAux[i] = vetor[j];
					char valorRandom[3];
					
					valorRandom[0] = 'a'+(char)(rand()%26);
					valorRandom[1] = 'a'+(char)(rand()%26);
					valorRandom[2] = 'a'+(char)(rand()%26);
		
					if(key % 2 == 0){
						vetAux[i] = key;
						insere(tab,vetAux[i],valorRandom);
					}else{
						key = key+1;
						vetAux[i] = key;
						insere(tab,vetAux[i],valorRandom);
					}
				}
				vetor[j] = -1;
			}
		}
	}
}
//gera o arquivo .txt
void geraArquivo(Reg *tab, int nElementos, int tipoEntrada, char nomeARQ[50]){
	
	int vetor[nElementos];
	char nome[50];
	
	if(tipoEntrada == 1){
		geraVetorAleatorioPar(vetor,tab,nElementos,vetor);
	}else if(tipoEntrada == 2){
		geraVetorAleatorio(vetor,tab,nElementos,vetor);
	}else{
		printf("\n --- Tipo de entrada incorreto! ---\n");
	}
	
	strncpy(nome,nomeARQ,50);
	strcat(nome,".txt");
	SalvarArquivo(tab,nElementos,nome);
} 
//salva os valores na Reg no arquivo txt
void SalvarArquivo(Hash *tab,int tam,char *nomeArq){
	int i;
	FILE *arq;	
	
	arq = fopen(nomeArq,"wt");
	if(arq == NULL){
		printf("\nErro no arquivo\n");
	}
	
	//grava no arquivo
	for( i=0;i<TAMTAB;i++){
		if(tab[i]){
			Reg *p = tab[i];
			while(p){
				fprintf(arq,"%d %s\n",p->chave,p->valor);
				p = p->prox;
			}
		}		
	}
	fclose(arq);
}
//le o arquivo na txt e insere na Reg
void LerArquivo(Hash *tab,int tam,char *nomeArq){
	int i;
	FILE *arq;	
	arq = fopen(nomeArq,"rt");
	
	if(arq == NULL){
		printf("\nErro no arquivo\n");
	}
	
	//LE DO ARQUIVO
	int key; 
	char val[3];
	
	for( i=0;i<tam;i++){
		fscanf(arq,"%d %s\n",&key,&val);		
		insereDois(tab,key,val);
	}
	fclose(arq);
}

void GeraArquivos(Hash *tab, int tam){
	int i;
	printf("\n5 arquivos PAR:");	
	for( i=0;i<5;i++){
		char nome[50];
		itoa(tam,nome,10);
		char aux[50] = "_PAR_";
		strcat(nome,aux);
		char aux1[1];
		int aux2 = i+1;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		printf("\n%s\t",nome);
		geraArquivo(tab,tam,1,nome);
		colisoes(tab,TAMTAB);
		limpaTabela(tab,TAMTAB);
	}
	printf("\n OK!");
	printf("\n5 arquivos ALEATORIOS:");
	for( i=0;i<5;i++){
		char nome[50];
		itoa(tam,nome,10);
		char aux[50] = "_ALE_";
		strcat(nome,aux);
		char aux1[1];
		int aux2 = i+1;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		printf("\n%s\t",nome);
		geraArquivo(tab,tam,2,nome);
		colisoes(tab,TAMTAB);
		limpaTabela(tab,TAMTAB);

		}
	printf(" \nOK!");
}

void LeArquivos(Hash *tab,int tam){
	int i;
	printf("\n5 arquivos PAR:");	
	for( i=0;i<5;i++){
		char nome[50];
		itoa(tam,nome,10);
		char aux[50] = "_PAR_";
		strcat(nome,aux);
		char aux1[1];
		int aux2 = i+1;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		printf("\n%s\t",nome);
		strcat(nome,".txt");
		LerArquivo(tab,20,nome);
		colisoes(tab,TAMTAB);
		limpaTabela(tab,TAMTAB);
	}
	printf("\n5 arquivos ALEATORIOS:");
	for( i=0;i<5;i++){
		char nome[50];
		itoa(tam,nome,10);
		char aux[50] = "_ALE_";
		strcat(nome,aux);
		char aux1[1];
		int aux2 = i+1;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		printf("\n%s\t",nome);
		strcat(nome,".txt");
		LerArquivo(tab,20,nome);
		colisoes(tab,TAMTAB);
		limpaTabela(tab,TAMTAB);
	}
}
