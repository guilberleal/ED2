#include <stdio.h>
#include <stdlib.h>

struct Tipo_lista{
    int info;
    struct TipoLista *prox;
};typedef struct Tipo_lista Lista;

//Prototipos
Lista *alocaLista(int i);
Lista *insere_inicio(Lista *lst, int i);
Lista *insere_fim(Lista *lst,int i);
Lista *excluiValor(Lista *lst,int i);
void imprimeLista(Lista *lst);
Lista *alteraValor(Lista *lst, int vantigo, int vnovo);
Lista *insere_ordenado_recursivo(Lista *lst,Lista *aux2, int i);
Lista *insere_fim_recursivo (Lista* lst, int i);


int main(){
    Lista *lista;
    lista = NULL;

    lista = insere_fim(lista,20);
    lista = insere_fim(lista,30);
    lista = insere_fim(lista,40);

    lista = insere_inicio(lista,10);
    lista = insere_inicio(lista,5);

    imprimeLista(lista);
    
    lista = excluiValor(lista,20);
    lista = alteraValor(lista,40,60);
    lista = insere_fim_recursivo(lista,30);
    lista = insere_fim_recursivo(lista,70);
    lista = insere_ordenado_recursivo(lista,NULL,10);
    lista = insere_ordenado_recursivo(lista,NULL,50);
    imprimeLista(lista);


    return 0;
}

Lista *alocaLista(int i){
    Lista *novo;
    novo = (Lista*) malloc(sizeof(Lista));
    novo->prox = NULL;
    novo->info = i;
    return novo;

}

Lista *insere_inicio(Lista *lst, int i){
    Lista *novo_no;
    novo_no = alocaLista(i);
    novo_no->prox = lst;
    lst = novo_no;
    return lst;
}

Lista *insere_fim(Lista *lst,int i){
    Lista *novo_no, *aux;
    novo_no = alocaLista(i);
    if(lst == NULL){
        lst = novo_no;
    }
    else{
        aux = lst;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo_no;
        return lst;    
    }
}

Lista *excluiValor(Lista *lst,int i){
    Lista *aux,*aux2;
    aux = lst;
    aux2 = aux;
    while((aux->prox != NULL) && (aux->info != i)){
        aux2 = aux;
        aux = aux->prox;
    }
    if(aux != NULL && (aux->info == i)){
        aux2->prox = aux->prox;
        free(aux);
        return lst;
    }
    else{
        printf("ERRO Valor nao encontrado");
        return -1;
    }
}

void imprimeLista(Lista *lst){
    printf("LISTA: [ ");
    while(lst != NULL){
        printf(" %d ", lst->info);
        lst = lst->prox;
    }
    printf("] \n");
}

Lista *alteraValor(Lista *lst,int vantigo, int vnovo){
    Lista *aux;
    aux = lst;
    while((aux->prox != NULL) && (aux->info != vantigo)){
        aux = aux->prox;
    }
    if(aux != NULL && (aux->info == vantigo)){
    	aux->info = vnovo;
        return lst;
    }
    else{
        printf("ERRO Valor nao encontrado");
        return -1;
    }
}

Lista *insere_ordenado_recursivo(Lista* lst, Lista *aux2, int i){
	Lista *aux;
	aux = alocaLista(i);
	

	if(lst != NULL){
		if(lst->info > i){
			aux->prox = lst;
			lst = aux;
			if(aux2 != NULL){
				aux2->prox = aux;
			}
		}else{
			if(lst->prox != NULL){
				insere_ordenado_recursivo(lst->prox, lst, i);
			}else{
				lst->prox = aux;
				aux->prox = NULL;
			}
		}
	}else{
		lst = aux;
		aux->prox = NULL;
	}

	return lst;
}


Lista* insere_fim_recursivo (Lista* lst, int i){
	Lista* aux;
	aux = alocaLista(i);
	
	if(lst == NULL){
		lst = aux;
	}else if(lst->prox == NULL){
		lst->prox = aux;
	}else{
		insere_fim_recursivo(lst->prox,i);
	}
	
	return lst;
}

