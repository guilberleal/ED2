#include <stdio.h>
#include <stdlib.h>


#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;
#define maxV 1024
#define BRANCO 0
#define CINZA 1
#define PRETO 2

static int pa[1000];
static int cnt, d[maxV], f[maxV],dist[maxV],cor[maxV],pred[maxV];
int tempo = 0;



typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice{
    /* Dados armazenados vao aqui */
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

typedef struct no{
    int u;
    ADJACENCIA *p;
}NO;

NO *pilha;
int fim;
int time;
/* Criando um grafo */
GRAFO *criarGrafo(int v){
    GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
    
    g->vertices     = v;
    g->arestas      = 0;
    g->adj          = (VERTICE *) malloc(v*sizeof(VERTICE));
    int i;
    
    for (i=0; i<v; i++)
        g->adj[i].cab = NULL;
    
    return g;
}

ADJACENCIA *criaAdj(int v,int peso){
    ADJACENCIA *temp = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
    temp->vertice   = v;
    temp->peso      = peso;
    temp->prox      = NULL;
    return (temp);
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
    if (!gr)
        return(false);
    if((vf<0) || (vf >= gr->vertices))
        return(false);
    if((vi<0) || (vf >= gr->vertices))
        return(false);
    
    ADJACENCIA *novo = criaAdj(vf,p);
    
    novo->prox      = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    
    ADJACENCIA *novo2 = criaAdj(vi,p);
    
    novo2->prox      = gr->adj[vf].cab;
    gr->adj[vf].cab = novo2;
    
    gr->arestas++;
    return (true);
}

void imprime(GRAFO *gr){
    printf("Vertices: %d. Arestas: %d, \n", gr->vertices,gr->arestas);
    
    int i;
    for(i=0;i<gr->vertices; i++){
        printf("v%d: ",i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while(ad){
            printf("v%d(%d) ", ad->vertice,ad->peso);
            ad = ad->prox;
        }
        
        printf("\n");
    }
}

void STACKinit(int maxN){
    pilha       = (NO*) malloc (maxN*sizeof(NO));
    fim  = 0;
}


int STACKempty(){
    return fim == 0;
}

void STACKput(int item, ADJACENCIA *px){
    pilha[fim].u = item;
    pilha[fim].p = px;
    fim++;
}

NO STACKget(){
    return pilha[--fim];
}

void STACKfree(){
    free(pilha);
}
void DFS_aux(GRAFO *G,int u);
void DFS_recursivo(GRAFO *G, int raiz);

void imprimeTree(GRAFO *gr){
	int v = 0;
    for( v ; v < gr->vertices; v++){
        printf("(%d,%d)\n",pred[v],v);
    }
    
}

int main(){
    int a,b,w;
    GRAFO *gr = criarGrafo(12);
//    inicio arestas
    criaAresta(gr,0,1,1);
    criaAresta(gr,0,2,1);
    criaAresta(gr,1,3,1);
    criaAresta(gr,1,6,1);
    criaAresta(gr,1,7,1);
    criaAresta(gr,2,3,1);
    criaAresta(gr,2,4,1);
    criaAresta(gr,3,4,1);
    criaAresta(gr,3,8,1);
    criaAresta(gr,3,9,1);
    criaAresta(gr,4,9,1);
    criaAresta(gr,4,8,1);
    criaAresta(gr,6,7,1);
    criaAresta(gr,6,10,1);
    criaAresta(gr,5,11,1);

    imprimeTree(gr);
    
    return 0;
}

void DFS_aux(GRAFO *G,int u){
    int i ;
    for(i=0; u < G->vertices ; i++){
        cor[u] = BRANCO;
        pred[u] = NULL;
    }
    tempo = 0;
    for(i=0; u < G->vertices ; i++){
        if(cor[i] == BRANCO){
            DFS_aux(G,i);
        }
    }
}

void DFS_recursivo(GRAFO *G, int raiz){
    int cont =0;
    cor[raiz] = CINZA;
    tempo++;
    d[raiz] = tempo;
    ADJACENCIA *v = G->adj->cab;
    while(v){
        if(cor[v->vertice] == BRANCO){
            pred[cont] = raiz;
            DFS_aux(G,raiz);
        }
        cont++;
       v =  v->prox;
    }
    cor[raiz] = PRETO;
    tempo++;
    f[raiz] = tempo;
}
