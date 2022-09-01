/**
 * ALGORITMO DE UMA ARVORE BINARIA
 * AUTOR: ALEX MATOS IUASSE
 */

//CABEÇALHO DE INCLUSAO

#include <stdio.h>
#include <stdlib.h>

//ESTRUTURA ARVORE

struct no_arvore
{
	int entrada;
	struct no_arvore *esquerda;
	struct no_arvore *direita;
};
typedef struct no_arvore tipo_arvore;

//ESTRUTURA DA LISTA

struct estruturano
{
	int valor;
	struct estruturano *prox;
};
typedef struct estruturano tipono;

//FUNCAO DE ALOCAR NO NA LISTA

tipono *alocano (int valor)
{
	tipono *novono = NULL;
	novono = (tipono*) malloc (sizeof(tipono));
	novono->valor = valor;
	novono->prox = NULL;
	return (novono);
}

//FUNCAO DE INSERIR NA LISTA

void insereinicio (tipono **lista, int valor)
{
	tipono *novono = alocano(valor);

	if(*lista == NULL)
	{
	     *lista = novono;
	}
	else
	{
	      novono->prox = *lista;
	      *lista = novono;
	}
}

//FUNCAO DE IMPRIMIR LISTA

void imprimir (tipono *lista)
{
    while (lista != NULL)
    {
        printf("[ %d ]\t",lista->valor);
        lista = lista->prox;
    }
}

//FUNCAO DE ALOCAR NOVOS NOS NA ARVORE

tipo_arvore *aloca_no (int entrada)
{
	tipo_arvore *novo_no = NULL;
	novo_no = (tipo_arvore*) malloc (sizeof(tipo_arvore));
	novo_no->entrada = entrada;
	novo_no->esquerda = NULL;
	novo_no->direita = NULL;
	return novo_no;
}

//FUNCAO DE INSERCAO NA ARVORE

void insere_arvore (tipo_arvore **arvore, int entrada)
{
	if (*arvore == NULL)
	{
		tipo_arvore *novo_no = aloca_no(entrada);
		*arvore = novo_no;
	}
	else
	{
		if ( entrada < (*arvore)->entrada )
			insere_arvore (&((*arvore)->esquerda),entrada);
		else
			insere_arvore (&((*arvore)->direita), entrada);
	}
}

//FUNCAO QUE BUSCA UM DETERMINADO NO NA ARVORE

void busca (tipo_arvore *arvore, int entrada)
{
	if ( arvore != NULL )
	{
		if ( arvore->entrada == entrada)
			printf("\nVALOR ENCONTRADO\n");
		else
		{
			if (entrada < arvore->entrada )
				busca ( arvore->esquerda,entrada);
			else
				busca ( arvore->direita,entrada);
		}
	}
	else
		printf("\nVALOR NAO ENCONTRADO\n");
}

//FUNCAO QUE MEDE O NIVEL DE UM CERTO NO

void nivel_no(tipo_arvore *arvore, int entrada, int cont)
{
    if ( arvore != NULL )
	{
		if (arvore->entrada == entrada)
			printf("O NO [ %i ] TEM NIVEL: [ %i ]\n\n",entrada,cont);
		else
		{
			if (entrada < arvore->entrada )
				nivel_no ( arvore->esquerda,entrada,cont+1);
			else
				nivel_no ( arvore->direita,entrada,cont+1);
		}
	}
}

//FUNCAO QUE COLOCA EM UMA LISTA TODOS NOS DE UM NIVEL

void lista_nivel (tipo_arvore *arvore, tipono **lista2, int nivel, int cont)
{
    if ( arvore != NULL )
	{
	    lista_nivel ( arvore->esquerda,lista2,nivel,cont+1);
	    if (cont == nivel)
			insereinicio(lista2,arvore->entrada);
        lista_nivel ( arvore->direita,lista2,nivel,cont+1);
	}
}

//FUNCAO QUE MEDE A ALTURA DE UMA ARVORE

int altura (tipo_arvore *arvore)
{
	if ( arvore == NULL )
        return -1;
    else
	{
	    int h_esq,h_dir;

        h_esq = altura (arvore->esquerda) + 1;
        h_dir = altura (arvore->direita) + 1;
        if (h_esq < h_dir)
            return h_dir ;
        else
            return h_esq ;
	}
}

//FUNCAO QUE VERIFICA SE UM NO E FOLHA OU NAO

int verifica_folha (tipo_arvore *arvore, int entrada)
{
    if ( arvore != NULL )
	{
		if ( arvore->entrada == entrada)
        {
            if (arvore->esquerda == NULL && arvore->direita == NULL)
                return 0;
            else
                return 1;
        }
		else
		{
			if (entrada < arvore->entrada )
				verifica_folha ( arvore->esquerda,entrada );
			else
				verifica_folha ( arvore->direita,entrada );
		}
	}
	else
		printf("\nVALOR NAO ENCONTRADO\n");
}

//FUNCAO QUE RETORNA TODOS NOS FOLHAS EM UMA LISTA

void retorna_folha (tipo_arvore *arvore, tipono **lista)
{
    if ( arvore != NULL )
	{
	    int aux;
        aux = verifica_folha(arvore,arvore->entrada);
        if(aux == 0)
            insereinicio(lista,arvore->entrada);
		retorna_folha(arvore->esquerda,lista);
		retorna_folha(arvore->direita,lista);
	}
}

//FUNCAO QUE VERIFICA SE UMA ARVORE E COMPLETA/BALANCEADA

int verifica_balanceamento (tipo_arvore *arvore)
{
	if ( arvore == NULL )
        return -1;
    else
	{
	    int h_esq = 0,h_dir = 0;

        h_esq = verifica_balanceamento (arvore->esquerda) +1;
        h_dir = verifica_balanceamento (arvore->direita) +1;
        return abs (h_esq - h_dir);
	}
}

//FUNCOES DE IMPRESSAO EM PRE-ORDEM, POS-ORDEM E ORDEM

void pre_ordem (tipo_arvore *arvore)
{
	if (arvore != NULL)
	{
		printf("[ %i ]  ",arvore->entrada);
		pre_ordem (arvore->esquerda);
		pre_ordem (arvore->direita);
	}
}

void pos_ordem (tipo_arvore *arvore)
{
	if (arvore != NULL)
	{
		pos_ordem (arvore->esquerda);
		pos_ordem (arvore->direita);
		printf("[ %i ]  ",arvore->entrada);
	}
}

void ordem (tipo_arvore *arvore)
{
	if (arvore != NULL)
	{
		ordem (arvore->esquerda);
		printf("[ %i ]  ",arvore->entrada);
		ordem (arvore->direita);
	}
}

//FUNCAO PRINCIPAL

int main (int argc, char **argv)
{
    //DEFINICAO DA ARVORE E DA LISTA
	tipo_arvore *arvore = NULL;
	tipono *lista = NULL;
	tipono *lista2 = NULL;

    //PARA FICAR MAIS FACIL A INSERCAO :D

    //COLOQUEI OS NUMEROS QUE SERAO INSERIDOS NA ARVORE DENTRO DO VETOR
	int numeros [] = {50,25,75,15,30,65,80,90,100};
	int indx = 0;

    //LAÇO PARA ENVIAR OS NUMEROS DO VETOR PARA A ARVORE
	while ( indx != 9 )
	{
		insere_arvore (&arvore,numeros[indx]);
		indx++;
	}

    //IMPRESSAO DA ARVORE DE VARIAS FORMAS
    printf("IMPRESSOES DA ARVORE:\n\n");

	printf("PRE ORDEM:\n");
	pre_ordem (arvore);
    puts("");

	printf("\nPOS ORDEM:\n");
	pos_ordem (arvore);
    puts("");

	printf("\nEM ORDEM:\n");
	ordem (arvore);
	puts("\n");


	//VARIAVEIS AUXILIARES
	int altu,balan,folha;

    //INICIO DOS TESTES

    //IMPRESSOES DOS NOS FOLHAS
    printf("IMPRESSAO DOS NOS FOLHAS:\n");
    retorna_folha(arvore,&lista);
    imprimir(lista);
    puts("\n");

    //VERIFICAR SE UMA ARVORE ESTA BALANCEADA
    //printf("VERIFICACAO SE UMA ARVORE ESTA BALANCEADA OU NAO:\n");
    if (balan = verifica_balanceamento(arvore) <= 1)
        printf("[ ARVORE BALANCEADA ]\n\n");
    else
        printf("[ ARVORE DESBALANCEADA ]\n\n");

    //VERIFICAR SE UM NO DADO E FOLHA OU NAO
    //printf("VERIFICACAO SE UM NO E FOLHA OU NAO:\n");
    if ( folha = verifica_folha (arvore,50) == 0 )
        printf("[ O NO DIGITADO E UM NO FOLHA ]\n\n");
    else
        printf("[ O NO DIGITADO NAO E UM NO FOLHA ]\n\n");

    //VERIFICAR O NIVEL DE UM DETERMINADO NO
    nivel_no(arvore,15,0);

    //VERIFICAR A ALTURA DA ARVORE
    printf("A ARVORE TEM ALTURA DE: [ %i ]\n",altu = altura (arvore));

    //LISTA COM TODOS NOS DE UM DETERMINADO NIVEL
    printf("\nLISTA COM OS NOS DO NIVEL INDICADO:\n");
    lista_nivel(arvore,&lista2,2,0);
    imprimir(lista2);
    puts("\n");
	return 0;
}




