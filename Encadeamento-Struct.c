#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ponto{
    float x;
    float y;
} Ponto;

typedef struct circulo{
    Ponto p;
    float r;
} Circulo;

float distancia(Ponto *p, Ponto *q){
    float d = sqrt((q->x - p->x) * (q->x - p->x) + (q->y - p->y) * (q->y - p->y));
    return d;
}
int interior(Circulo *c, Ponto *p){
    float d = distancia(&c->p, p);
    return (d < c->r);
}

int main(){
    Circulo c;
    Ponto p;
    printf("Digite as coordenadas do centro e o raio do circulo:\n");
    scanf("%f %f %f", &c.p.x, &c.p.y,&c.r);

    printf("Digite as coordenadas do ponto:\n");
    scanf("%f %f %f", &p.x, &p.y);

    printf("Pertence ao interior = %d\n", interior(&c,&p));
    return 0;
}