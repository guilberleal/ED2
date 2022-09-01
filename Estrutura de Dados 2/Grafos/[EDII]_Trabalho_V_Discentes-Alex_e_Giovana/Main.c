/** Cabeçalho **/
/**
                UNIVERSIDADE FEDERAL DE MATO GROSSO - UFMT
                         24 de Julho de 2014

                                   ~ * ~

   Docente: Ivairton Santos
   Discentes: Giovana Hiromi Tanita
              Alex Matos Iuasse
   Disciplina: Estrutura de Dados II
   Trabalho 5) Função Principal: "Árvore B".

**/

/*************************************************************************/

/** Bibliotecas **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore_B.c"


/** Função principal, onde todas as funções da árvore serão chamadas. **/
int main ( int argc, char *argv[] ) {

    /** Inicializando a árvore, auxiliar do tipoLivro, arquivo**/
    tipoArvB * arvB = NULL;
    tipoLivro val;
    FILE * arquivo = NULL;

    /** Variáveis que vão receber os dados do arquivo a serem processados
        e inseridos na árvore. **/
    int i = 0;
    int part1, part2;
    char traco;
    char str1[10];
    char str2[10];
    char full_ISBN_cara[10];
    int t;

    arquivo = fopen ( "books.txt", "rt" );
    while ( !feof ( arquivo ) ) {
        if ( i==0 ) {
            /** Obtém o primeiro inteiro que vem no começo do arquivo. **/
            fscanf ( arquivo, "%d\n", &t );
            i++;
        }
        else {
            /** Obtém o número do ISBN no formato XXXX-XXXX. **/
            fscanf ( arquivo, "%d%c%d", &part1, &traco, &part2 );
            /** Obtém o título do arquivo. **/
            fscanf ( arquivo, " %[^\n]\n", val.titulo );

            /** Transforma o número do ISBN no formato XXXX-XXX para um
                número inteiro (sem o traço) **/
            val.ISBN = part1 * 10000;
            val.ISBN = val.ISBN + part2;

            /** Transforma o número do ISBN em uma string contendo o traço **/
            sprintf( full_ISBN_cara, "%d", part1); /** Primeira parte inteira vira string **/
            sprintf( str1, "%c", traco); /** Transforma o caractere traço em outra string **/
            sprintf( str2, "%d", part2); /** Segunda parte inteira vira string **/
            strcat ( full_ISBN_cara, str1 ); /** Concatena a string da parte 1 com o traço **/
            strcat ( full_ISBN_cara, str2 ); /** Concatena a string1+traço com a string 2 **/

            strcpy ( val.ISBN_carac, full_ISBN_cara ); /** Copia a string completa para o auxiliar do tipoLivro **/

            /** Insere na árvore os elemento a medida que são lidos **/
            arvB = insereArvB ( arvB, val );

        }
    }

    int opcao=0;

    while ( opcao!=5 ) {
        printf ( " 1) Inserir um novo livro\n 2) Buscar por um livro\n 3) Remover um livro\n 4) Imprimir a lista de livros\n 5) Sair\n\n" );
        scanf ( "%d", &opcao );
        if ( opcao < 1 || opcao > 5 ) printf ( "Opcao invalida\n" );
        else {
            switch ( opcao ) {
            case 1 :
                /** Opção de inserir um novo livro manualmente **/
                printf ( "\nInsira o nome do livro: ");
                scanf ( " %[^\n]", val.titulo );
                printf ( "\nInsira o ISBN do livro: (Siga o formato XXXX-XXXX): ");
                scanf ( "%d%c%d", &part1, &traco, &part2 );

                /** Recebe o número do ISBN e transforma em número inteiro **/
                val.ISBN = part1 * 10000;
                val.ISBN = val.ISBN + part2;

                /** Transforma o ISBN em string **/
                sprintf( full_ISBN_cara, "%d", part1);
                sprintf( str1, "%c", traco);
                sprintf( str2, "%d", part2);
                strcat ( full_ISBN_cara, str1 );
                strcat ( full_ISBN_cara, str2 );

                strcpy ( val.ISBN_carac, full_ISBN_cara );

                /** Insere na árvore **/
                arvB = insereArvB ( arvB, val );

                printf ( "\n" );
                break;

            case 2:
                /** Faz a busca pelo número do ISBN **/
                printf ( "\nInsira o ISBN do livro a ser buscado: (Siga o formato XXXX-XXXX): ");
                scanf ( "%d%c%d", &part1, &traco, &part2 );

                /** Transforma em um número inteiro para percorrer a árvore **/
                val.ISBN = part1 * 10000;
                val.ISBN = val.ISBN + part2;

                /** Chama a função de busca. O nome do livro encontrado será impresso na função. **/
                buscaB ( arvB, val.ISBN );
                break;

            case 3:
                /** Remove um livro com o código do ISBN**/
                printf ( "\nInsira o ISBN do livro para remover: (Siga o formato XXXX-XXXX): ");
                scanf ( "%d%c%d", &part1, &traco, &part2 );

                /** Transforma o código em inteiro para percorrer na árvore **/
                val.ISBN = part1 * 10000;
                val.ISBN = val.ISBN + part2;

                int f = 0; /** Inicialização da flag usada na função de remoção **/
                ehFolha ( arvB ); /** Atualiza se os nós são folha ou não **/
                remover ( arvB, val.ISBN, &f); /** Remove o livro com o ISBN inserido **/
                printf ( "Livro removido com sucesso.\n");

                break;

            case 4:
                /** Chama a função de impressão da árvore em pré-ordem **/
                imprimeB ( arvB );
                break;

            case 5:
                /** Gera um arquivo com a lista dos livros em ordem e finaliza a execução do programa **/
                geradorSaidas ( arvB );
                return 0;
            }
        }
    }
    return 0;

}
