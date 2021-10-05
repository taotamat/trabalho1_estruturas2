#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
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


// op == 1: Todas as inserções foram realizadas.
// op == 2: uma unidade foi lida.
// op == 3: uma palavra foi buscada.
void marcar_tempo(FILE *arq, char *nome, int op, clock_t *tempo_inicial){

	double tempo_total;
	clock_t tempo_final;

	tempo_final = clock();
	tempo_total = tempo_final - (*tempo_inicial);


	if( op == 1)
		fprintf(arq, "\nTempo para inserir todas as unidades na árvore: \n");
	else if( op == 2 ){
		if( nome != NULL )
			fprintf(arq, "\nTempo para concluir a insercao da unidade %s: \n", nome);
	} else if( op == 3 ){
		fprintf(arq, "\nTempo para encontrar a palavra %s na arvore: \n", nome);
	}
	

	fprintf(arq, "%lf milissegundos \n", tempo_total/CLOCKS_PER_SEC);
	fprintf(arq, "%lf segundos\n",  tempo_total/(CLOCKS_PER_SEC/1000));
	fprintf(arq, "\n--------------------------------------\n");
}


// Função chama as funções de leitura dos árquivos
void gestaoLER(FILE *arq, arvUNIDADE *arvPRINCIPAL) {

	FILE *insercaoARQ; // Árquivo onde os resultados do teste de tempo serão salvos;

	clock_t tempo_inicial;
	clock_t tempo_inicial_unidade;

	int count = 0; // Qnt de palavras presentes na unidade.
	// double tempo_total;

	int trava = 0;
	char linha[201];
	UNIDADE *unidade_atual;

	unidade_atual = NULL;
	insercaoARQ = fopen("insercao.txt", "w");
	tempo_inicial = clock();


	do{
		lerLINHA(arq, linha);
		maiusculo(linha);

		//printf("linha = %s \n", linha);

		if( linha[0] == '\0'){
			// Todo o arquivo foi lido e o laço de repetição deve ser lido;
			trava = 1;

			if( unidade_atual != NULL ){
				//printf("unidade_atual = %s \n", unidade_atual->nome);
				fprintf(insercaoARQ, "%d palavras presentes na unidade %s.\n", count, unidade_atual->nome);
				marcar_tempo(insercaoARQ, unidade_atual->nome, 2, &tempo_inicial_unidade);
			}

		} else if( linha[0] == '%' ){
			// Uma nova unidade será aberta;
			// Essa unidade será guardada na arvPRINCIPAL;
			// o ponteiro unidade_atual guardará essa nova unidade;
			// As próximas palavras serão guardadas nessa unidade_atual;
			
			if( unidade_atual != NULL ){
				//printf("unidade_atual = %s \n", unidade_atual->nome);
				fprintf(insercaoARQ, "%d palavras presentes na unidade %s.\n", count, unidade_atual->nome);
				marcar_tempo(insercaoARQ, unidade_atual->nome, 2, &tempo_inicial_unidade);
			}
			
			tempo_inicial_unidade = clock();

			unidade_atual = nova_unidade(arvPRINCIPAL, linha);
			inserir_arvUNIDADE(arvPRINCIPAL, (&arvPRINCIPAL->raiz), unidade_atual);
			count = 0;
			printf("UNIDADE %s SALVA COM SUCESSO! \n", unidade_atual->nome);

		} else {
			// A linha contém as palavras que serão armazenadas na UNIDADE;
			separar_palavras(&unidade_atual, linha);
			count++;
		}

		linha[0] = '\0';
	} while(trava == 0);

	marcar_tempo(insercaoARQ, NULL, 1, &tempo_inicial);
	fclose(insercaoARQ); }