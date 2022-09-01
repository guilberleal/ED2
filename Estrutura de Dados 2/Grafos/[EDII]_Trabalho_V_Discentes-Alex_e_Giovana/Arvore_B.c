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

/** Constantes **/

#define T 3 // Constante T que determina o tamanho da Árvore B
#define MAX_CHAVES ( 2 * T - 1 ) // Máximo de registros
#define MAX_FILHOS ( 2 * T ) // Máximo de filhos
#define MIN_FILHOS ( T - 1 ) // Mínimo de registros
#define MIN_CHAVES ( T - 1 )

/*************************************************************************/

/************************************************************************
*
*                             ESTRUTURAS
*                       tipoLivro e tipoArvB
*
************************************************************************/

/** Estrutura para armazenar os livros **/
typedef struct tipoLivro {
    char ISBN_carac[10]; /** Armazena o código ISBN no formato padrão XXXX-XXXX **/
    int ISBN; /** Armazena o código ISBN como um inteiro de 8 casas decimais, usado para
                fazer as operções da árvore **/
    char titulo[1000]; /** Título do livro **/
} tipoLivro;

/** Estrutura tipo para a árvore B **/

typedef struct tipoArvB {
   int num_chaves; /** Quantidade de chaves contidas em um nó **/
   struct tipoLivro chaves[MAX_FILHOS]; /** Vetor com as chaves armazenadas no nó **/
   struct tipoArvB * filhos[MAX_FILHOS]; /** Vetor de ponteiros para os filhos **/
   int folha; /** Flag que sinaliza se um nó é folha **/
} tipoArvB;

/** Utliza-se de uma lista para guardar todos os elementos da árvore quando o relatório
    final estiver sendo gerado. ***/
typedef struct estruturaNo {
    tipoLivro valor;
    struct estruturaNo *prox;
} tipoNo;

/*************************************************************************/

/************************************************************************
*
*                        PROTÓTIPO DAS FUNÇÕES
*
************************************************************************/

char* buscaB ( tipoArvB *no, int ISBN_code );
void imprimeB ( tipoArvB *no );
void ehFolha ( tipoArvB *no );
int buscaBinaria ( tipoArvB *raiz, int valor );
int buscaSucessor ( tipoArvB *raiz );
void concatena ( tipoArvB *pagina, int pos, int pos_indica );
void redistribui ( tipoArvB *pagina, int pos, int pos_indica );
void verifica_pagina ( tipoArvB *pagina, int pos );
void remover ( tipoArvB *raiz, int valor, int *flag );
tipoArvB * alocaNovoNo ();
void insereChave ( tipoArvB * no, tipoLivro valor, tipoArvB *filhoDir );
tipoArvB * insere ( tipoArvB *raiz, tipoLivro valor, int * flag, tipoLivro *valorRetorno  );
tipoArvB * insereArvB ( tipoArvB * raiz, tipoLivro valor );
tipoNo *alocaNo (tipoLivro valor);
void insere_lista (tipoNo **lista, tipoLivro valor );
void emOrdem ( tipoArvB *no, tipoNo **lista );
void geradorSaidas ( tipoArvB *arvB  );


/*************************************************************************/

/************************************************************************
*
*                            FUNÇÕES EXTRAS NA ÁRVORE.
*                Busca, Impressão, Atualização de nó folha
*
************************************************************************/

/** Função para buscar um livro pelo ISBN. **/

char* buscaB ( tipoArvB *no, int ISBN_code ) {
   int i;
   /** Se a árvore não for nula, percorre o nó procurando pelo elemento **/
   if ( no != NULL ) {
      for ( i=0; i<no->num_chaves; i++ ) {
        /** Ao encontrar o código, retorna o título do livro. **/
        if ( no->chaves[i].ISBN == ISBN_code ) {
            printf ( "Livro encontrado.\nTitulo:" );
            puts ( no->chaves[i].titulo );
            return ( no->chaves[i].titulo );
        }
      }
      /** Executa a chamada recursiva para procurar nos outros filhos,
          percorrendo o vetor de filhos. **/
      for ( i=0; i<no->num_chaves+1; i++ ) {
         buscaB ( no->filhos[i], ISBN_code );
      }
   }
}

/*************************************************************************/

/** Função para imprimir a árvore B em pré-ordem. **/

void imprimeB ( tipoArvB *no ) {
   int i;
   /** Imprime as chaves **/
   if ( no != NULL ) {
      printf ( "\n\n" );
      /** Percorre o vetor de chaves do nó e imprime cada elemento **/
      for ( i=0; i<no->num_chaves; i++ ) {
         printf ( "%s/%s\n", no->chaves[i].ISBN_carac, no->chaves[i].titulo );
      }
      printf ( "\n\n" );
      /** Executa a chamada recursiva para os filhos **/
      for ( i=0; i<no->num_chaves+1; i++ ) {
         imprimeB ( no->filhos[i] );
      }
   }
}

/*************************************************************************/

/** Função que atribui 1 caso o no seja folha e 0 caso nao seja **/

void ehFolha ( tipoArvB *no ) {
   int i;
   /** Imprime as chaves **/
   if ( no != NULL ) {
      for ( i=0; i<no->num_chaves+1; i++ ) {
         if ( no->filhos[i] == NULL ) no->folha=1;
         else no->folha=0;
      }
      /** Executa a chamada recursiva para os filhos **/
      for ( i=0; i<no->num_chaves+1; i++ ) {
         ehFolha ( no->filhos[i] );
      }
   }
}

/*************************************************************************/

/** Função que realiza a busca binária. **/

int buscaBinaria ( tipoArvB *raiz, int valor ) {
   int inicio, meio, fim;
   inicio = 0;
   fim = raiz->num_chaves-1;

   while ( inicio <= fim ) {
      meio = ( (fim+inicio) / 2 );
      /** Se o valor foi encontrado, retorna a posição em que a chave está **/
      if ( raiz->chaves[meio].ISBN == valor ) return meio;
      else {
         if ( valor < raiz->chaves[meio].ISBN ) fim = (meio-1);
         else inicio = meio+1;
      }
   }
   /** Se o valor não for encontrado, retorna a posição do ponteiro para o filho direito **/
   return inicio;
}

/*************************************************************************/

/************************************************************************
*
*           FUNÇÕES PARA A REMOÇÃO NA ÁRVORE.
*
************************************************************************/


/** Função que realiza a busca de um sucessor **/

/** Enviar o filho [na posição chave + 1]
    Retorno o número que será o sucessor do número que será removido  descer
    um a direita e o resto a esquerda **/
int buscaSucessor ( tipoArvB *raiz ) {
    if ( raiz->folha == 1 ) return raiz->chaves[0].ISBN;
    else return buscaSucessor ( raiz->filhos[0] );
}
/*************************************************************************/

/** Função que concatena paginas, pos_indica, é o indicador de direta ou esquerda **/

void concatena ( tipoArvB *pagina, int pos, int pos_indica ) {
      /** Descer a chave do pai **/
    (pagina->filhos[pos])->chaves[T-2] = pagina->chaves[pos];
    pagina->chaves[0].ISBN = 0;

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

    (pagina->filhos[pos])->num_chaves --;
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

void remover ( tipoArvB *raiz, int valor, int *flag ) {
    /** Se a raiz é nula **/
    if ( raiz == NULL ) {
	printf ("Nenhuma chave presente na arvore!");
    } else {
	/** Busca binaria para valor **/
	int pos = buscaBinaria ( raiz, valor );
	if ( raiz->chaves[pos].ISBN == valor ) {
	    /** Verificar se e folha **/
	      if ( raiz->folha == 1 ) {
		/** Move os elementos do vetor **/
		memmove( &(raiz)->chaves[pos], &(raiz)->chaves[pos+1],(raiz->num_chaves - pos - 1)*sizeof(char*) );
		raiz->num_chaves -- ;
		if ( raiz->num_chaves < MIN_CHAVES) {
		    *flag = 1; /** pagina desbalanceada **/
		}
	    } else {
		char sucessor = buscaSucessor ( raiz->filhos[pos+1] );
		raiz->chaves[pos].ISBN = sucessor;
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

/************************************************************************
*
*                FUNÇÕES PARA A INSERÇÃO NA ÁRVORE.
*
************************************************************************/

/** Função que aloca um novo nó na memória. **/

tipoArvB * alocaNovoNo () {
   tipoArvB * novoNo;
   int i;
   /**  Alocao nó e inicializa os elementos **/
   novoNo = ( tipoArvB* ) malloc ( sizeof ( tipoArvB ) );
   novoNo->num_chaves = 0;
   novoNo->folha = 1;

   /** Inicialização dos vetores **/
   for ( i=0; i < MAX_CHAVES; i++ ) novoNo->chaves[i].ISBN = 0;
   for ( i=0; i < MAX_FILHOS; i++ ) novoNo->filhos[i] = NULL;

   return novoNo;
}

/*************************************************************************/

/** Após todas as condições para a inserção correta de uma determinada chave
    forem atendidas, utiliza-se essa função para inserir uma chave e o ponteiro
    para o filho direito desta nova chave. **/

void insereChave ( tipoArvB * no, tipoLivro valor, tipoArvB *filhoDir ) {
   int i, pos;
   /** Utiliza-se a busca binária para encontrar a posição correta no
       vetor de chaves. **/
   pos = buscaBinaria ( no, valor.ISBN );
   i = no->num_chaves;

   /** Executa o remanejamento dos valor para que o vetor ainda se
       mantenha ordenado **/
   while ( ( i > pos ) && (valor.ISBN < no->chaves[i-1].ISBN) ) {
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

tipoArvB * insere ( tipoArvB *raiz, tipoLivro valor, int * flag, tipoLivro *valorRetorno  ) {
   int i, pos;
   char meio; /** Auxiliar que armazena a chave que subirá para o pai **/
   tipoArvB *noAux, *filhoDir; /** Filho à direita da chave **/

   if ( raiz == NULL ) {
      /** Como alcançou um nó folha, o nó anterior ( o pai ) é onde deve
          ser feita a inserção **/
      *flag = 1; /** 1 representa a flag de verdadeiro **/
      valorRetorno->ISBN = valor.ISBN;
      return ( NULL );
   }

   else {
      /** Inicializa a busca pelo nó em que se deve inserior a chave **/
      pos = buscaBinaria ( raiz, valor.ISBN );
      /** Identifica se o valor já está na árvore. **/

      if ( ( raiz->num_chaves > pos ) && ( raiz->chaves[pos].ISBN == valor.ISBN ) ) {
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
               meio = raiz->chaves[MIN_CHAVES].ISBN;

               /** A segunda metade das chaves vai para o novo nó, enquanto a primeira
                   metade deve continuar no nó original. **/
               noAux->filhos[0] = raiz->filhos[MIN_CHAVES+1];
               for ( i=MIN_CHAVES + 1; i < MAX_CHAVES; i++ ) {
                  insereChave ( noAux, raiz->chaves[i], raiz->filhos[i+1] );
               }

               /** Atualiza o nó original apagando as chaves que foram colocadas no novo
                   nó **/
               for ( i = MIN_CHAVES + 1; i < MAX_CHAVES; i++ ) {
                  raiz->chaves[i].ISBN = 0;
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
               valorRetorno->ISBN = meio;
               return ( noAux );
               }
         } else return ( NULL );
      }
   }

}

/*************************************************************************/

/** Função principal de inserção na árvore B, ecapsula todas as outras
    ( função a ser chamada pelas funções externas )**/

tipoArvB * insereArvB ( tipoArvB * raiz, tipoLivro valor ) {

   int i;
   int flag;
   tipoLivro valorRetorno = valor;
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

/*************************************************************************/

/************************************************************************
*
*           FUNÇÕES PARA GERAR O RELATÓRIO FINAL.
*
************************************************************************/

/** Aloca os livros na lista. ***/
tipoNo *alocaNo (tipoLivro valor) {
    tipoNo *novoNo = NULL;
    novoNo = (tipoNo*) malloc (sizeof(tipoNo));
    novoNo->valor.ISBN = valor.ISBN;
    strcpy ( novoNo->valor.ISBN_carac, valor.ISBN_carac );
    strcpy ( novoNo->valor.titulo, valor.titulo );
    novoNo->prox = NULL;
    return novoNo;
}

/** Insere cada livro na lista, sempre no final, para manter
    o formato do percurso em ordem. ***/
void insere_lista (tipoNo **lista, tipoLivro valor ) {
    tipoNo *novo_No = alocaNo(valor);
    tipoNo *aux;
    if ( *lista == NULL ) *lista=novo_No;
    else {
        aux = *lista;
        while ( aux-> prox != NULL ) aux = aux->prox;
        aux->prox = novo_No;
    }
}

/*************************************************************************/

/** Função que gera o arquivo de saida. **/
void emOrdem ( tipoArvB *no, tipoNo **lista ) {
   int i;
   if ( no != NULL ) {
      /** Faz primeiramente a chamada recursiva **/
      for ( i=0; i<no->num_chaves+1; i++ ) emOrdem ( no->filhos[i], lista );

      for ( i=0; i<no->num_chaves; i++ ) {
        /** Insere os elementos na lista assim que são checados **/
        insere_lista ( lista, no->chaves[i] );
      }

   }
}

/** Gera o relatório final com todos os livros cadastrados **/
void geradorSaidas ( tipoArvB *arvB  ) {
    tipoNo *lista = NULL;

    emOrdem ( arvB, &lista );

    FILE * RELATORIO;
    RELATORIO = fopen ( "Relatorio.txt", "wt" );
    if ( RELATORIO != NULL ) {
        while ( lista != NULL ) {
            /** Salva em arquivo seguinto o formato <ISBN>/<Título>
                percorrendo a lista e salvando os elementos em arquivo. **/
            fprintf ( RELATORIO, "%s/", lista->valor.ISBN_carac );
            fputs ( lista->valor.titulo, RELATORIO );
            fprintf ( RELATORIO, "\n" );
            lista = lista->prox;
        }
    }
    fclose ( RELATORIO );
}

