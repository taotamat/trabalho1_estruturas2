#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unidades.h"
#include "palavras.h"
#include "arquivo.h"
#include "balanceamento.h"

/*
	Enunciado da questão:
	(2,5 pontos) Cada unidade em um livro-texto inglês contém um vocabulário Inglês-Português de palavras que são usadas 
	pela primeira vez em uma unidade em particular. Faça um programa que converta um conjunto de tais vocabulários armazenados 
	em um arquivo Inglês em um conjunto de vocabulários Português-Inglês. Para isso considere que:

	[OK] - (a) Os nomes das unidades são precedidos por um símbolo de porcentagem.
	[OK] - (b) Há somente uma entrada por linha.
	[OK] - (c) Uma palavra em Inglês é separada por dois pontos de sua(s) equivalente(s) portuguesa(s); se há mais deuma equivalente, 
	elas são separadas por vírgula.

	Para produzir as palavras em ordem alfabética,: 
		[OK] - crie uma árvore binária de busca para cada unidade que contenha as palavras em português, 
		[OK] - e listas ligadas das equivalentes inglesas. 

	[OK] - Assegure-se de que exista apenas um nó para cada palavra portuguesa na árvore. 
	[OK] - Além disso, permita o usuário informar uma unidade e então imprima todas as palavras da unidade em português 
	seguida das equivalentes em inglês. 
	[OK] - Depois. imprima todas as palavras em inglês equivalentes a uma palavra em português dada, 
	pesquisando para isso em todas as árvores das unidades cadastradas. 
	[  ] - Por fim permita o usuário remover uma determinada palavra 
	em português de uma unidade, e consequentemente as palavras em inglês equivalentes a ela.
*/

//----------------------------------------------------------//
// Menu Principal:

int menu(){

	// FUNÇÃO QUE APRESENTA UM MENU.

	int op;
	printf("\n\n");
	
	ast();
	printf("\t\t\tMENU PRINCIPAL:\n");
	ast();
	
	printf("[1] - Ler o arquivo e salvar os dados nas estruturas  \n");
	printf("[2] - Apresentar os nomes das unidades em PRE-ORDEM   \n");
	printf("[3] - Apresentar os nomes das unidades em IN-ORDEM    \n");
	printf("[4] - Apresentar os nomes das unidades em POS-ORDEM   \n");
	printf("[5] - Imprimir palavras de uma unidade selecionada    \n");
	printf("[6] - Imprimir a lista de palavras inglesas referentes a uma palavra portuguesa\n");
	printf("[7] - Remover uma palavra de uma unidade \n");
	printf("[0] - Sair\n");

	ast();
	printf("SELECIONE A OPCAO DE DESEJADA: ");
	scanf("%d", &op);
	ast();

	printf("\n\n");

	return op; }

//----------------------------------------------------------//
// FUNÇÃO MAIN:

int main(){

	int op;
	FILE *arq;
	arvUNIDADE *arvPRINCIPAL;
	arq = fopen("arquivo.txt", "r"); 		/* 		abre o árquivo 					*/
	arvPRINCIPAL = aloca_arvUNIDADE();		/* 		aloca uma árvore principal 		*/

	do{

		op = menu();

		switch(op){

			case 0:
				// ENCERRAR O PROGRAMA;
				ast();
				printf("\t\tPrograma encerrado!\n");
				ast();
				break;

			case 1:
				// Ler o árquivo e salvar os vocabulários nas árvores
				gestaoLER(arq, arvPRINCIPAL);
				break;

			case 2:
				// Apresentar os nomes das unidades em PRE-ORDEM
				preordem_unidade(arvPRINCIPAL->raiz);
				break;

			case 3:
				// Apresentar os nomes das unidades em IN-ORDEM
				inordem_unidade(arvPRINCIPAL->raiz);
				break;

			case 4:
				// Apresentar os nomes das unidades em POS-ORDEM
				posordem_unidade(arvPRINCIPAL->raiz);
				break;

			case 5:
				// Imprimir todas as palavras portuguesas de uma determinada unidade;
				gestao_imprimirUNIDADE(arvPRINCIPAL);
				break;

			case 6:
				// Imprimir todas as palavras inglesas de uma palavra selecionada;
				gestao_imprimirPALAVRA(arvPRINCIPAL->raiz);
				break;

			case 7:
				// Remover uma palavra de uma unidade;
				gestao_removePALAVRA(arvPRINCIPAL);
				break;

			default:
				// MENSAGEM DE ERRO
				ast();
				printf("Valor inválido, digite novamente:\n");
				ast();
				break;

		}

	} while(op != 0);


	// fechando arquivo
  	fclose(arq);

	return 0; }


/*

Adicionais:	

	Compilar e executar:
		gcc nomedoprograma.c -o nomedoprograma -lm && ./nomedoprograma
	
	Ler uma string que contenha espaços e limpeza de buffer:
		scanf(" %[^\n]s", (*carro).chassi);
		setbuf(stdin, NULL);
	


*/