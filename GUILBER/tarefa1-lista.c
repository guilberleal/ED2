#include <stdio.h>
#include <stdlib.h>

struct lista
{
    int info;
    struct lista *prox;
};

typedef struct lista Lista;

Lista *cria_lista(void)
{
    return NULL;
}

Lista *insere_inicio(Lista *li, int i)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = li;
    return novo;
}

Lista *insere_fim(Lista *li, int i)
{
    Lista *novo, *aux = (Lista *)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = NULL;

    Lista *p = li;
    Lista *q = li;

    while (p != NULL)
    {
        q = p;
        p = p->prox;
    }

    if (q != NULL)
        q->prox = novo;
    else
        li = novo;

    return li;
}

Lista *insere_ordenado(Lista *li, int i)
{
    Lista *novo;
    Lista *ant = NULL;
    Lista *p = li;

    while (p != NULL && p->info < i)
    {
        ant = p;
        p = p->prox;
    }

    novo = (Lista *)malloc(sizeof(Lista));
    novo->info = i;

    if (ant == NULL)
    {
        novo->prox = li;
        li = novo;
    }
    else
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return li;
}

Lista *insere_fim_recursivo(Lista *li, int i)
{

    if (li == NULL)
    {
        li->info = i;
        li->prox = NULL;
        return li;
    }

    return insere_fim_recursivo(li->prox, i);
}

Lista *insere_ordenado_recursivo(Lista *li, Lista *ant, int i)
{
}

Lista *exclui(Lista *li, int i)
{
}

Lista *altera(Lista *li, int vantigo, int vnovo)
{
}

void imprime(Lista *li)
{
    Lista *p;

    for (p = li; p != NULL; p = p->prox)
    {
        printf("info = %d\n", p->info);
    }
}

int main(void)
{
    Lista *lista = NULL;


    //Recebe o endereço da lista, e o valor a ser inserido no inicio
    insere_inicio(&lista, 20);
    insere_inicio(&lista, 10);

    // //Recebe o endereço da lista, o valor a ser inserido no inicio, e a posição
    // inserePosicao(&lista, 25, 2);

    //Recebe o endereço da lista, e o valor a ser inserido no fim
    insere_fim(&lista, 30);

    //Imprimir a Lista
    imprime(lista);

    return 0;
}
