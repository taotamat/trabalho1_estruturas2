#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unidades.h"
#include "palavras.h"
#include "arquivo.h"

// ----------------------------------------------------------- //
void ast(){

	printf("-------------------------------------------------------------\n"); }

// transforma todos os caracteres de uma string em MAIUSCULAS;
void maiusculo(char *palavra){
	int tam;
	tam = strlen(palavra)-1;
	while(tam >= 0){
		if( isalpha(palavra[tam]) != 0 )
			palavra[tam] = toupper(palavra[tam]);
		tam--;
	} }

// Função que ler o arquivo
void lerLINHA(FILE *arq, char *linha) {
	int aux = 0;
	int i = 0;
	char c;
	do{
		c = fgetc(arq);

		if( c == EOF || arq == NULL || c == '\n') {
			aux = 1;
			linha[i] = '\0';
		} else {
			linha[i] = c; // Todos os caracteres na linha deverão
			i++;
		}

	} while(aux == 0); }

// Função chama as funções de leitura dos árquivos
void gestaoLER(FILE *arq, arvUNIDADE *arvPRINCIPAL) {

	int trava = 0;
	char linha[201];
	UNIDADE *unidade_atual;

	do{
		lerLINHA(arq, linha);
		maiusculo(linha);

		if( linha[0] == '\0'){
			// Todo o arquivo foi lido e o laço de repetição deve ser lido;
			trava = 1;
		} else if( linha[0] == '%' ){
			// Uma nova unidade será aberta;
			// Essa unidade será guardada na arvPRINCIPAL;
			// o ponteiro unidade_atual guardará essa nova unidade;
			// As próximas palavras serão guardadas nessa unidade_atual;
			unidade_atual = NULL;
			unidade_atual = nova_unidade(arvPRINCIPAL, linha);
			inserir_arvUNIDADE(arvPRINCIPAL, (&arvPRINCIPAL->raiz), unidade_atual);
			printf("UNIDADE %s SALVA COM SUCESSO! \n", unidade_atual->nome);
		} else {
			// A linha contém as palavras que serão armazenadas na UNIDADE;
			separar_palavras(&unidade_atual, linha);
		}

		linha[0] = '\0';

	} while(trava == 0); }