//UFMT - CUA 
//CIENCIA DA COMPUTACAO
//TRABALHO DE ESTRUTURA DE DADOS 2
//KEVYN MENEZES CARVALHO



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct MATRIZ {
	int valor;
	int linha;
	int coluna;
	struct MATRIZ *proxLinha;
	struct MATRIZ *proxColuna;
}tipoMatEsparsa;



tipoMatEsparsa* acessaNo(tipoMatEsparsa**, int, int);
tipoMatEsparsa* alocaCanto(tipoMatEsparsa*);




int main(){
	tipoMatEsparsa *matriz, *personagem;
	FILE *arquivo;
	char opcao[10], output[10];

	arquivo = fopen("out.txt", "w");
	//alocando o no do canto
	matriz = alocaCanto(matriz);
	//inicializando personagem na primeira posicao (0, 0)
	personagem = acessaNo(&matriz, 0, 0);

	printf("BEM VINDO AO LABIRINTO\nUSE AS SEGUINTES TECLAS PARA INTERACAO:\n");
	printf("'A' : MOVIMENTAR-SE PARA A ESQUERDA\n");
	printf("'D' : MOVIMENTAR-SE PARA A DIREITA\n");
	printf("'S' : MOVIMENTAR-SE PARA BAIXO\n");
	printf("'W' : MOVIMENTAR-SE PARA CIMA\n");
	printf("'E' : SAIR DO JOGO\n\nSUA OPCAO: ");
	scanf("%s", opcao);
	*opcao = tolower(*opcao);



	fprintf(arquivo,"%s", "linha, coluna\n");
	fprintf(arquivo, "%d, %d\n", personagem->linha, personagem->coluna);
	while (*opcao != 'e'){
		if (*opcao == 'a'){//anda uma coluna para esquerda
			if (personagem->coluna > 0){//somente se a coluna for > 0
				personagem = acessaNo(&matriz, personagem->linha, personagem->coluna-1);
				fprintf(arquivo, "%d, %d\n", personagem->linha, personagem->coluna);
			}
		} else if (*opcao == 'w'){//anda uma linha para cima
			if (personagem->linha > 0){//somente se a linha for > 0
				personagem = acessaNo(&matriz, personagem->linha-1, personagem->coluna);
				fprintf(arquivo, "%d, %d\n", personagem->linha, personagem->coluna);
			}
		} else if (*opcao == 'd'){//anda uma coluna para direita
			personagem = acessaNo(&matriz, personagem->linha, personagem->coluna+1);
			fprintf(arquivo, "%d, %d\n", personagem->linha, personagem->coluna);
		} else if (*opcao == 's'){//anda uma linha para baixo
			personagem = acessaNo(&matriz, personagem->linha+1, personagem->coluna);
			fprintf(arquivo, "%d, %d\n", personagem->linha, personagem->coluna);
		}
		
		printf("SUA OPCAO: ");
		scanf("%s", opcao);
		*opcao = tolower(*opcao);
	}

	fclose(arquivo);
	return 0;
}



tipoMatEsparsa* acessaNo(tipoMatEsparsa **mat, int linha, int coluna){
	tipoMatEsparsa *novoNo, *aux, *node;
	aux = *mat;
	//acessando o no pela coluna, e se nao houver esta coluna, a aloco na memoria
	while(aux->proxColuna != NULL && aux->proxColuna->coluna < coluna){
		aux = aux->proxColuna;
	}
	//se chegou na ultima coluna e essa coluna nao existe, aloco ela
	if (aux->proxColuna == NULL){
		novoNo = malloc(sizeof(tipoMatEsparsa));
		novoNo->proxColuna = NULL;
		novoNo->proxLinha = NULL;
		novoNo->coluna = coluna;
		novoNo->linha = -1;
		aux->proxColuna = novoNo;
		aux = novoNo;
	} else { // se nao esta no ultimo elemento
		//e o proxima coluna tem um indice maior, entao aloco uma coluna no meio das duas
		if (aux->proxColuna->coluna > coluna){
			novoNo = malloc(sizeof(tipoMatEsparsa));
			novoNo->proxColuna = aux->proxColuna;
			novoNo->proxLinha = NULL;
			novoNo->coluna = coluna;
			novoNo->linha = -1;
			aux->proxColuna = novoNo;
			aux = novoNo;
		} else {
			//se nao esta no ultimo elemento
			//e a proxima coluna tem indice igual, entao a coluna ja existe,
			//sendo assim, so ando com o auxiliar para a posicao correta
			aux = aux->proxColuna;
		}
	}

	//quando chego na posicao de coluna correta, tenho que descer as linhas ate chegar na linha desejada
	while(aux->proxLinha != NULL && aux->proxLinha->linha < linha){
		aux = aux->proxLinha;
	}
	//aqui segue a mesma logica para coluna
	if (aux->proxLinha == NULL){
		novoNo = malloc(sizeof(tipoMatEsparsa));
		novoNo->coluna = coluna;
		novoNo->linha = linha;
		novoNo->valor = 0;
		novoNo->proxLinha = NULL;
		novoNo->proxColuna = NULL;
		aux->proxLinha = novoNo;
		node = novoNo;
	} else {
		if (aux->proxLinha->linha > linha){
			novoNo = malloc(sizeof(tipoMatEsparsa));
			novoNo->coluna = coluna;
			novoNo->linha = linha;
			novoNo->valor = 0;
			novoNo->proxLinha = aux->proxLinha;
			novoNo->proxColuna = NULL;
			aux->proxLinha = novoNo;
			node = novoNo;
		} else {
			//exceto que se já existe o no na coluna/linha desejada, entao nao preciso
			//me preocupar em alocar esse no, e nem linka-lo pela linha, entao
			//simplesmente retorno o endereco e termino minha funcao
			return aux->proxLinha;
		}
	}

	//Se a funcao continuar a partir dessa linha, entao tenho a certeza
	//que esse no nao existia na memoria antes, entao, agora tenho que ir
	//e linka-lo corretamente na sua linha

	//partindo do canto da matriz
	aux = *mat;
	//seguindo a mesma logica, agora para linhas
	while (aux->proxLinha != NULL && aux->proxLinha->linha < linha){
		aux = aux->proxLinha;
	}
	if (aux->proxLinha == NULL){
		novoNo = malloc(sizeof(tipoMatEsparsa));
		novoNo->coluna = -1;
		novoNo->linha = linha;
		novoNo->proxLinha = NULL;
		novoNo->proxColuna = NULL;
		aux->proxLinha = novoNo;
		aux = novoNo;
	} else {
		if (aux->proxLinha->linha > linha){
			novoNo = malloc(sizeof(tipoMatEsparsa));
			novoNo->coluna = -1;
			novoNo->linha = linha;
			novoNo->proxLinha = aux->proxLinha;
			novoNo->proxColuna = NULL;
			aux->proxLinha = novoNo;
			aux = novoNo;
		} else {
			aux = aux->proxLinha;
		}
	}
	//chegando na linha desejada, caminho ate a coluna do no, para linka-lo
	while(aux->proxColuna != NULL && aux->proxColuna->coluna < coluna){
		aux = aux->proxColuna;
	}
	//linkando
	node->proxColuna = aux->proxColuna;
	aux->proxColuna = node;
	//retorno o no
	return node;
}


tipoMatEsparsa* alocaCanto(tipoMatEsparsa *mat){
	mat = malloc(sizeof(tipoMatEsparsa));
	mat->linha = -1;
	mat->coluna = -1;
	mat->proxColuna = NULL;
	mat->proxLinha = NULL;
	return mat;
}

