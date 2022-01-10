/*  UFMT-2021
    Arthur e Guilber
    trabalho 2-ED2
    Etapa 1 gerando arquivos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define LIM 1024 //chave
//Prototipos
int geraVl(int vl);
int geraVlPar(int vl);
//Funcao principal
int main(){
    int i, aux;
    char c;
    while(1){
    printf("Digite a quantidade de numeros gerados:\n");
    scanf("%d",&i);
    aux=geraVl(i);
    if(aux){
        printf("valores gerados Aleatorios com sucesso!\n");
    }else{
        printf("falha ao gerar valores aleatorios!\n");
    }
    aux=geraVlPar(i);
    if(aux){
        printf("valores gerados Par com sucesso!\n");
    }else{
        printf("falha ao gerar valores aleatorios!\n");
    }
    printf("Se deseja parar digite 'n' \n");
    scanf("%s", &c);
    if(c=='n'){
        break;
    }

    }
return 0;
}
int geraVl(int vl){
    int i,j,k, auxVR;
	char valorRandom[3] = "aaa";
	for(k=0;k<5;k++){
		char nome[50];//gerando nome do arquivo
		itoa(vl,nome,10);
		char aux[50] = "_Ale_";//nome dos arquivos com chaves aleatorias
		strcat(nome,aux);
		char aux1[1];
		int aux2 = k+1;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		strcat(nome,".txt");
		printf("\n%s\t",nome);//termina de gerar o nome do arquivo na variavel nome
		//Criando arquivo 
		FILE *arq;	
		int j;
		arq = fopen(nome,"wt");
		if(arq == NULL){
			printf("\nErro no arquivo\n");
		}
		
		//gerando valores aleatorios
	    srand(time(NULL));
	    for (i=0;i<vl;i++){
	    	auxVR= (rand() %(LIM-1));
	    	printf("%d ", auxVR);
	    	fprintf(arq,"%d\t",auxVR);
	    	valorRandom[0] = 'a'+(char)(rand()%26);
			valorRandom[1] = 'a'+(char)(rand()%26);
			valorRandom[2] = 'a'+(char)(rand()%26);
	    	for(j=0;j<3;j++){
				printf("%c",valorRandom[j]);
				fprintf(arq,"%c",valorRandom[j]);
			}
			printf("\n");
			fprintf(arq,"\n");	
	    }
	    	fclose(arq);
	}
    return 1;
}

int geraVlPar(int vl){
int i,j,k, auxVR;
	char valorRandom[3] = "aaa";
	for(k=0;k<5;k++){
		char nome[50];//gerando nome do arquivo
		itoa(vl,nome,10);
		char aux[50] = "_Par_";//nome dos arquivos com chaves aleatorias
		strcat(nome,aux);
		char aux1[1];
		int aux2 = k+1;
		itoa(aux2,aux1,10);
		strcat(nome,aux1);
		strcat(nome,".txt");
		printf("\n%s\t",nome);//termina de gerar o nome do arquivo na variavel nome
		//Criando arquivo 
		FILE *arq;	
		int j;
		arq = fopen(nome,"wt");
		if(arq == NULL){
			printf("\nErro no arquivo\n");
		}
		
		//gerando valores aleatorios
	    srand(time(NULL));
	    for (i=0;i<vl;i++){
	    	auxVR= (rand() %(LIM-1));
	    	if(auxVR % 2 != 0){	
				auxVR = auxVR+1;
			}
	    	printf("%d ", auxVR);
	    	fprintf(arq,"%d\t",auxVR);
	    	valorRandom[0] = 'a'+(char)(rand()%26);
			valorRandom[1] = 'a'+(char)(rand()%26);
			valorRandom[2] = 'a'+(char)(rand()%26);
	    	for(j=0;j<3;j++){
				printf("%c",valorRandom[j]);
				fprintf(arq,"%c",valorRandom[j]);
			}
			printf("\n");
			fprintf(arq,"\n");	
	    }
	    	fclose(arq);
	}
    return 1;


    return 1;
}


	


