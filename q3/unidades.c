#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unidades.h"
#include "palavras.h"
#include "arquivo.h"

// Função que aloca uma nova unidade.
UNIDADE *alocaUNIDADE(){
	UNIDADE *nova;
	nova = (UNIDADE *) malloc(sizeof(UNIDADE));
	nova->qnt = 0;
	nova->arvorePALAVRAS = NULL;
	nova->esq = NULL;
	nova->dir = NULL;
	return nova; }

// Função que aloca uma nova árvore de UNIDADES:
arvUNIDADE *aloca_arvUNIDADE(){
	arvUNIDADE *nova;
	nova = (arvUNIDADE *) malloc(sizeof(arvUNIDADE));
	nova->raiz = NULL;
	nova->qnt = 0;
	return nova; }

// Função que nomea a nova UNIDADE.
void nomeaUNIDADE(UNIDADE *nova, char *linha){
	int tam; // Tamanho da string *linha
	int i;
	int j = 0;
	tam = strlen(linha);
	for(i=1; i<tam; i++){
		nova->nome[j] = linha[i];
		j = j + 1; } }

// Inserir uma nova unidade na árvore de unidade arvPRINCIPAL;
void inserir_arvUNIDADE(arvUNIDADE *arvPRINCIPAL, UNIDADE **aux, UNIDADE *nova){

	int comparacao;

	if( *aux != NULL )
		comparacao = strcmp((*aux)->nome, nova->nome);


	if( *aux == NULL ){
		// arvore não possue uma raiz, então o novo é a nova raiz.
		*aux = nova;
		arvPRINCIPAL->qnt = arvPRINCIPAL->qnt + 1;
	} else if( comparacao < 0 && (*aux)->esq != NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho esquerdo do NO aux.
		inserir_arvUNIDADE(arvPRINCIPAL, &((*aux)->esq), nova);
	} else if( comparacao < 0 && (*aux)->esq == NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux FOR NULL, 
		// Então o novo NO será o novo filho esquerdo do NO aux.
		(*aux)->esq = nova;
		arvPRINCIPAL->qnt = arvPRINCIPAL->qnt + 1;
	} else if( comparacao > 0 && (*aux)->dir != NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho direito do NO aux.
		inserir_arvUNIDADE(arvPRINCIPAL, &((*aux)->dir), nova);
	} else if( comparacao > 0 && (*aux)->dir == NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux FOR NULL, 
		// Então o novo NO será o novo filho direito do NO aux.
		(*aux)->dir = nova;
		arvPRINCIPAL->qnt = arvPRINCIPAL->qnt + 1;
	}  }

// Essa função cria uma nova unidade;
	// Aloca espaço para uma nova UNIDADE;
	// Em seguida, Chama a função nomeaUNIDADE - que passará os dados de *linha para a nova unidade
	// Depois chamará a função de inserir na árvore principal.
	// E para finalizar, ela retornará o endereço de memória dessa nova UNIDADE;
UNIDADE *nova_unidade(arvUNIDADE *arvPRINCIPAL, char *linha){
	UNIDADE *nova;
	nova = alocaUNIDADE();
	nomeaUNIDADE(nova, linha);
	return nova; }

// Apresentar os nomes das unidade em PRE-ORDEM
void preordem_unidade(UNIDADE *unidade){
	if(unidade != NULL){
		
		printf("-------------------------------------------- \n");
		printf("| %s \n", unidade->nome);
		// printf("unidade->arvorePALAVRAS->raiz = %p \n", unidade->arvorePALAVRAS);
		preordem_palavra(unidade->arvorePALAVRAS->raiz);
		printf("-------------------------------------------- \n\n\n");

		preordem_unidade(unidade->esq);
		preordem_unidade(unidade->dir);
	} }

// Apresentar os nomes das unidade em IN-ORDEM
void inordem_unidade(UNIDADE *unidade){
	if(unidade != NULL){
		inordem_unidade(unidade->esq);

		printf("UNIDADE = %s \n", unidade->nome);
		inordem_palavra(unidade->arvorePALAVRAS->raiz);

		inordem_unidade(unidade->dir);
	} }

// Apresentar os nomes das unidade em POS-ORDEM
void posordem_unidade(UNIDADE *unidade){
	if(unidade != NULL){
		posordem_unidade(unidade->esq);
		posordem_unidade(unidade->dir);
		printf("UNIDADE = %s \n", unidade->nome);
		posordem_palavra(unidade->arvorePALAVRAS->raiz);
	} }

// Função que busca uma unidade na árvore de unidades.
	/*  strcmp(string1, string2);

	Possíveis valores de retorno:
	0: conteúdo das strings são iguais
	< 0: conteúdo da string1 é menor do que string2
	> 0: conteúdo da string1 é maior do que string2 */
UNIDADE *buscaUNIDADE(UNIDADE *unidade, char *palavra){
	int comparacao;
	UNIDADE *aux;
	aux = NULL;
	if(unidade != NULL){
		comparacao = strcmp(palavra, unidade->nome);

		if( comparacao == 0 )  // São iguais!
			aux = unidade;
		else if( comparacao > 0 )
			aux = buscaUNIDADE(unidade->esq, palavra);
		else if( comparacao < 0 )
			aux = buscaUNIDADE(unidade->dir, palavra); 

	}
	return aux; }

// Imprime os dados de uma unidade encontrada;
void imprimirUNIDADE(UNIDADE *encontrado, char *palavra) {
	if(encontrado != NULL){
		printf("\n-------------------------------------------- \n");
		printf("| %s \n", encontrado->nome);
		preordem_palavra(encontrado->arvorePALAVRAS->raiz);
		printf("-------------------------------------------- \n\n\n");
	} else printf("A unidade %s não foi encontrada. \n", palavra); }

// Solicita que o usuário digite a unidade que deseja busca
// Em seguida ele chama a funçao que busca a UNIDADE na árvore principal.
// E por fim, chama a função de apresentação;
void gestao_imprimirUNIDADE(arvUNIDADE *arvPRINCIPAL) {
	char palavra[51];
	UNIDADE *encontrado;
	printf("Digite o nome da unidade que deseja buscar: ");
	scanf(" %[^\n]s", palavra );
	setbuf(stdin, NULL); // Limpesa do buffer
	maiusculo(palavra); // Deixa tudo em maiusculos.
	encontrado = buscaUNIDADE(arvPRINCIPAL->raiz, palavra); // Busca a unidade
	imprimirUNIDADE(encontrado, palavra); /* Imprimir o que foi encontrado */}

