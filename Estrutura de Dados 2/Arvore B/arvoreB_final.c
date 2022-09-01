/** Cabeçalho **/
/**
                UNIVERSIDADE FEDERAL DE MATO GROSSO - UFMT
                         24 de Julho de 2014

                                   ~ * ~

   Docente: Ivairton Santos
   Discentes: Giovana Hiromi Tanita
              Alex Matos Iuasse
   Disciplina: Estrutura de Dados II
   Trabalho 5) Estrutura: "Árvore B".

**/

/*************************************************************************/

/** Bibliotecas **/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/*************************************************************************/

/** Constantes **/

#define T 3 // Constante T que determina o tamanho da Árvore B
#define MAX_CHAVES ( 2 * T - 1 ) // Máximo de registros
#define MAX_FILHOS ( 2 * T ) // Máximo de filhos
#define MIN_FILHOS ( T - 1 ) // Mínimo de registros
#define MIN_CHAVES ( T - 1 )

/*************************************************************************/

/** Estrutura tipo para a árvore B **/

typedef struct tipoArvB {
   int num_chaves; /** Quantidade de chaves contidas em um nó **/
   char chaves[MAX_CHAVES]; /** Vetor com as chaves armazenadas no nó **/
   struct tipoArvB * filhos[MAX_FILHOS]; /** Vetor de ponteiros para os filhos **/
   int folha; /** Flag que sinaliza se um nó é folha **/
} tipoArvB;


/*************************************************************************/

/** Função para imprimir a árvore B em pré-ordem. **/

void imprimeB ( tipoArvB *no ) {
   int i;
   /** Imprime as chaves **/
   if ( no != NULL ) {
      printf ( "[ " );
      for ( i=0; i<no->num_chaves; i++ ) {
         printf ( "%c ", no->chaves[i] );
      }
      printf ( "]\n" );
      /** Executa a chamada recursiva para os filhos **/
      for ( i=0; i<no->num_chaves+1; i++ ) {
         imprimeB ( no->filhos[i] );
      }
   }
}

/*************************************************************************/

/** Função que realiza a busca binária. **/

int buscaBinaria ( tipoArvB *raiz, char valor ) {
   int inicio, meio, fim;
   inicio = 0;
   fim = raiz->num_chaves-1;

   while ( inicio <= fim ) {
      meio = ( (fim+inicio) / 2 );
      /** Se o valor foi encontrado, retorna a posição em que a chave está **/
      if ( raiz->chaves[meio] == valor ) return meio;
      else {
         if ( valor < raiz->chaves[meio] ) fim = (meio-1);
         else inicio = meio+1;
      }
   }
   /** Se o valor não for encontrado, retorna a posição do ponteiro para o filho direito **/
   return inicio;
}

/*************************************************************************/

/** Função que realiza a busca de um sucessor **/

/** Enviar o filho [na posição chave + 1]
Retorno o número que será o sucessor do número que será removido  descer 
um a direita e o resto a esquerda **/
char buscaSucessor ( tipoArvB *raiz ) {
    if ( raiz->folha == 1 ) return raiz->chaves[0];
    else return buscaSucessor ( raiz->filhos[0] );
}
/*************************************************************************/

/** Função que concatena paginas, pos_indica, é o indicador de direta ou esquerda **/

void concatena ( tipoArvB *pagina, int pos, int pos_indica ) {
    /** Descer a chave do pai **/ 
    (pagina->filhos[pos])->chaves[T-2] = pagina->chaves[pos];
    (pagina->filhos[pos])->num_chaves ++;
    pagina->chaves[0] = 0;
    
    int i;
    /** Concatenar a pagina que esta desbalanceada com o irmão **/
    for ( i = 0; i < T-1; i ++ ) {
      (pagina->filhos[pos])->chaves[(T-1)+i] = (pagina->filhos[pos_indica])->chaves[i];
      (pagina->filhos[pos])->num_chaves ++;
    }
    /** Liberar o irmão **/
    free ( pagina->filhos[pos_indica] );
    /** Organizar as chaves do pai **/
    for ( i = pos; i < pagina->num_chaves; i ++ ) {
      pagina->chaves[i] = pagina->chaves[i+1];
    }
    /** Organizar os filhos do pai (pagina) **/
    for ( i = pos+1; i < pagina->num_chaves+1; i ++ ) {
      pagina->filhos[i] = pagina->filhos[i+1];
    }
    pagina->num_chaves --;
    /** Liberar o ultimo filho do pai da memoria **/
    free ( pagina->filhos[pagina->num_chaves+1]);
    pagina->filhos[pagina->num_chaves+1] = NULL;
}

/*************************************************************************/

/** Função que redistribui **/

void redistribui ( tipoArvB *pagina, int pos, int pos_indica ) {
    /** Descer pai **/
    (pagina->filhos[pos])->chaves[T-2] = pagina->chaves[pos];
    (pagina->filhos[pos])->num_chaves ++;
    /** Subir filho para posição do pai **/
    pagina->chaves[pos] = (pagina->filhos[pos_indica])->chaves[0];
    int i;
    /** Organizar chaves do irmão que emprestou uma chave **/
    for ( i = 0; i < (pagina->filhos[pos+1])->num_chaves; i ++ ) {
      (pagina->filhos[pos_indica])->chaves[i] = (pagina->filhos[pos_indica])->chaves[i+1];
    }
    (pagina->filhos[pos_indica])->num_chaves --;
}

/*************************************************************************/

/** Função que verifica se uma pagina esta desbalanceada **/
/** Estou mandando o pai (pagina) da pagina que tem a chave para remover **/
void verifica_pagina ( tipoArvB *pagina, int pos ) {
    /** redistribuição ou concatenação Atualizar flag **/
    if ( pos == 0 ) {	/** so tem irmao a direita **/
	/** verifica se e possivel redistribuir **/
	if ( (pagina->filhos[pos+1])->num_chaves > MIN_CHAVES ) {  
	    /** Fazer redistribuição **/
	    redistribui ( pagina, pos, pos+1 );
	} else {    /** Fazer concatenação **/
	    concatena ( pagina, pos, pos+1 );
	}
    } else if ( pos == MAX_FILHOS ) {	/** so tem irmao a esquerda **/
	/** verifica se e possivel redistribuir **/
	if ( (pagina->filhos[pos-1])->num_chaves > MIN_CHAVES ) {
	    /** fazer redistribuição **/
	    redistribui ( pagina, pos, pos-1 );
	} else {    
	    /** fazer concatenação **/
	    concatena ( pagina, pos, pos-1 );
	}
    } else { /** A pagina da chave a remover esta no meio **/
	/** verificar dos dois lados **/
	if ( (pagina->filhos[pos+1])->num_chaves > MIN_CHAVES ) {
	    /** fazer redistribuição **/
	    redistribui ( pagina, pos, pos+1 );
	} else if ( (pagina->filhos[pos-1])->num_chaves > MIN_CHAVES) {
	    /** fazer redistribuição **/
	    redistribui ( pagina, pos, pos-1 );
	} else {
	    /** fazer concatenação **/
	    concatena ( pagina, pos, pos-1 );
	}
    }
}

/*************************************************************************/

/** Função que remove uma chave **/

void remover ( tipoArvB *raiz, char valor, int *flag ) {
    /** Se a raiz é nula **/
    if ( raiz == NULL ) {
	printf ("Nenhuma chave presente na arvore!");
    } else {
	/** Busca binaria para valor **/
	int pos = buscaBinaria ( raiz, valor );
	if ( raiz->chaves[pos] == valor ) {
	    /** Verificar se e folha **/
	      if ( raiz->folha == 0 ) { /*** HIROMI ARRUMAR AQUI QUANDO COLOCAR A INDICAÇÃO DE FOLHA, MUDAR PARA 1 ***/
		/** Move os elementos do vetor **/
		memmove( &(raiz)->chaves[pos], &(raiz)->chaves[pos+1],(raiz->num_chaves - pos - 1)*sizeof(char*) );
		raiz->num_chaves -- ;
		if ( raiz->num_chaves < MIN_CHAVES) {
		    *flag = 1; /** pagina desbalanceada **/
		}
	    } else {
		char sucessor = buscaSucessor ( raiz->filhos[pos+1] );
		raiz->chaves[pos] = sucessor;
		remover ( raiz->filhos[pos+1], sucessor, flag );
		if ( *flag == 1 ) {
		    /** chamar funções que tratem o caso de desbalanceamento **/
		    verifica_pagina ( raiz, pos );
		    
		    /** verificar num_chaves **/
		    if ( raiz->num_chaves >= MIN_CHAVES ) {
			*flag = 0; /** pagina balanceada **/
		    }
		}
	    }
	} else {
	    if ( raiz->filhos[pos] != NULL ) {
		remover ( raiz->filhos[pos], valor, flag );
		if ( *flag == 1 ) {
		    /** chamar funções que tratem o caso de desbalanceamento **/
		    verifica_pagina ( raiz, pos );
		    
		    /** verificar num_chaves **/
		    if ( raiz->num_chaves >= MIN_CHAVES ) {
			*flag = 0; /** pagina balanceada **/
		    }
		}
	    } else {
		printf ("Chave não encontrada!\n");
	    }
	}
    } 
}

/*************************************************************************/

/** Função que aloca um novo nó na memória. **/

tipoArvB * alocaNovoNo () {
   tipoArvB * novoNo;
   int i;

   novoNo = ( tipoArvB* ) malloc ( sizeof ( tipoArvB ) );
   novoNo->num_chaves = 0;
   novoNo->folha = 1;

   for ( i=0; i < MAX_CHAVES; i++ ) novoNo->chaves[i] = 0;
   for ( i=0; i < MAX_FILHOS; i++ ) novoNo->filhos[i] = NULL;

   return novoNo;
}

/*************************************************************************/

/** Após todas as condições para a inserção correta de uma determinada chave
forem atendidas, utiliza-se essa função para inserir uma chave e o ponteiro
para o filho direito desta nova chave. **/

void insereChave ( tipoArvB * no, char valor, tipoArvB *filhoDir ) {

   int i, pos;
   /** Utiliza-se a busca binária para encontrar a posição correta no
   vetor de chaves. **/
   pos = buscaBinaria ( no, valor);
   i = no->num_chaves;

   /** Executa o remanejamento dos valor para que o vetor ainda se
   mantenha ordenado **/
   while ( ( i > pos ) && (valor < no->chaves[i-1]) ) {
      no->chaves[i] = no->chaves[i-1];
      no->filhos[i+1] = no->filhos[i];
      i--;
   }

   /** Insere a nova chave. **/
   no->chaves[pos] = valor;
   no->filhos [pos+1] = filhoDir;
   no->num_chaves++;

}


/*************************************************************************/

/** Função que busca a posição onde o novo valor deve ser inserido,
executa a inserção (utilizando a função anterior) e executa as sub-
divisões quando necessário. **/

tipoArvB * insere ( tipoArvB *raiz, char valor, int * flag, char *valorRetorno  ) {

   int i, pos;
   char meio; /** Auxiliar que armazena a chave que subirá para o pai **/
   tipoArvB *noAux, *filhoDir; /** Filho à direita da chave **/


   if ( raiz == NULL ) {
      /** Como alcançou um nó folha, o nó anterior ( o pai ) é onde deve
      ser feita a inserção **/
      *flag = 1; /** 1 representa a flag de verdadeiro **/
      *valorRetorno = valor;
      return ( NULL );
   }

   else {
      /** Inicializa a busca pelo nó em que se deve inserior a chave **/
      pos = buscaBinaria ( raiz, valor );
      /** Identifica se o valor já está na árvore. **/

      if ( ( raiz->num_chaves > pos ) && ( raiz->chaves[pos] == valor ) ) {
         printf ( "O valor da chave já está presente na Árvore B!\n" );
         *flag = 0; /** 0 representa a flag de falso **/
         return ( NULL );
      }

      else {
         /** Caso o valor não tenha sido encontrado, desce na árvore até alcançar
         um nó folha, onde ocorrerá a inserção. Utiliza-se uma chamada recursiva
         da função de inserção **/
         filhoDir = insere( raiz ->filhos[pos], valor, flag, valorRetorno );

         /** Se a flag tiver retornado verdadeira ( ou seja, foi possível descer na
         árvore com sucesso ) baste inserir a chave. **/

         if ( *flag ) {
            if ( raiz->num_chaves < MAX_CHAVES ) {
               /** Verifica se há espaço livre para dividir o nó **/
               insereChave ( raiz, *valorRetorno, filhoDir );
               *flag = 0;
	       return ( NULL );
	    } else {
               /** Se não houver espaço livre, deve-se fazer o split ( dividir o nó )
               antes de poder inserir a chave. **/
               noAux = alocaNovoNo ( );
               noAux->num_chaves = 0;
               meio = raiz->chaves[MIN_CHAVES];

               /** A segunda metade das chaves vai para o novo nó, enquanto a primeira
               metade deve continuar no nó original. **/
               noAux->filhos[0] = raiz->filhos[MIN_CHAVES+1];
               for ( i=MIN_CHAVES + 1; i < MAX_CHAVES; i++ ) {
                  insereChave ( noAux, raiz->chaves[i], raiz->filhos[i+1] );
               }

               /** Atualiza o nó original apagando as chaves que foram colocadas no novo
               nó **/
               for ( i = MIN_CHAVES + 1; i < MAX_CHAVES; i++ ) {
                  raiz->chaves[i] = 0;
                  raiz->filhos[i+1] = NULL;
               }
               raiz->num_chaves = MIN_CHAVES;

               /** Verifica em qual dos novos nós o valor deve ser inserido, chama a
               função insereChave para inserir a chave em seu respectivo nó correto. **/
               if ( pos <= MIN_CHAVES ) {
                  insereChave ( raiz, *valorRetorno, filhoDir );
               } else {
                  insereChave ( noAux, *valorRetorno, filhoDir );
               }

               /** Retorna-se o elemento do meio para inseri-lo no nó pai e o nó auxiliar como filho
               direito do elemento do meio. **/
               *valorRetorno = meio;
               return ( noAux );
               }
         } else return ( NULL );
      }
   }
   
}

/*************************************************************************/

/** Função principal de inserção na árvore B, ecapsula todas as outras
( função a ser chamada pelas funções externas )**/

tipoArvB * insereArvB ( tipoArvB * raiz, char valor ) {

   int flag, i;
   char valorRetorno;
   tipoArvB *filhoDir, *novaRaiz;

   filhoDir = insere ( raiz, valor, &flag, &valorRetorno );

   /** Verifica se ocorreu a descida na árvore adequadamente, se há
   a necessidade de um novo nó como na raíz **/
   if ( flag ) {
      novaRaiz = alocaNovoNo();
      novaRaiz->num_chaves = 1;
      novaRaiz->chaves[0] = valorRetorno;
      novaRaiz->filhos[0] = raiz;
      novaRaiz->filhos[1] = filhoDir;
      
      for ( i=2; i<=MAX_CHAVES; i++ ) novaRaiz->filhos[i] = NULL;
      novaRaiz->folha = 0;
      return ( novaRaiz );
   }
   else {
      return ( raiz );
   }
}



int main ( int argc, char **argv ) {

    tipoArvB * arvB = NULL;
    
    arvB = insereArvB ( arvB, 'a' );
    arvB = insereArvB ( arvB, 'b' );
    arvB = insereArvB ( arvB, 'c' );
    arvB = insereArvB ( arvB, 'd' );
    arvB = insereArvB ( arvB, 'e' );
    arvB = insereArvB ( arvB, 'f' );
    arvB = insereArvB ( arvB, 'g' );
    arvB = insereArvB ( arvB, 'h' );
    arvB = insereArvB ( arvB, 'i' );
    arvB = insereArvB ( arvB, 'j' );
    arvB = insereArvB ( arvB, 'k' );
    arvB = insereArvB ( arvB, 'l' );
    arvB = insereArvB ( arvB, 'm' );
    arvB = insereArvB ( arvB, 'n' );
    arvB = insereArvB ( arvB, 'o' );
    arvB = insereArvB ( arvB, 'p' );
    arvB = insereArvB ( arvB, 'q' );
    arvB = insereArvB ( arvB, 'r' );
    /** ERROS que eu nao consigo resolver
     * 1- remoção ao meio
     * 2- tentar remover o p '-' incrivel que nem entra nao função de remoção, o problema esta na hora da chamada,
     * porem, eu nao sei onde diabos esta o erro !!
     * 3- olhe na função remover, tem um aviso la a respeito da flag
     * 4- Sorry, deixei so os erros contigo :( mas estou com uma enchaqueca tensa desde ontem x.x (obs: nao fui a festa alguma !)
     **/
    int f = 0;
    imprimeB ( arvB );
    remover ( arvB,'p',&f);
    printf("\n");
    imprimeB ( arvB );
  return 0;
}
