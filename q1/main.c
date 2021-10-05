#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvoreBinaria.h"
#include "funcoes.h"

/*
	Questão 01
	TO-DO:
     [OK] Gerar 1000 números aleatórios, e inserir em uma árvore binária de busca, incialmente vazia.
     [OK] Os valores devem ser gerados aleatoriamente utilizando 2 métodos para garantir a aleatoriedade.
     [OK] Imprimir o nível da folha de maior profundidade 
     [OK] Imprimir o nível da folha de menor profundidade.
     [OK] Repetir as etapas anteriores 30 vezes.
     [OK] Mostrar quantas das 30 vezes a diferença entre a profundidade máxima e mínima foram de 0, 1, 2 , 3...
     [OK] Contabilizar o tempo gasto para inserir todos os elementos na árvore.
     [OK] Em cada uma das inserções faça experimento de verificar o tempo de busca de elementos, use sempre os mesmo elementos em todos 
          os experimentos.
     
     [  ] Organizar o codigo
     [  ] Fazer a 2 questao
*/



int menu(){

	// FUNÇÃO QUE APRESENTA UM MENU.

	int op;
	printf("\n\n");
	
	ast();
	printf("\t\t\tMENU PRINCIPAL:\n");
	ast();
	
	printf("[1] - Gerar as 30 árvores\n");
	printf("[2] - Opcao 2\n");
	printf("[3] - Opcao 3\n");
	printf("[4] - Opcao 4\n");
	printf("[5] - Opcao 5\n");
	printf("[6] - Opcao 6\n");
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

	start();
/*
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
				// FUNÇÃO TAL
				break;

			case 2:
				// FUNÇÃO TAL
				break;

			case 3:
				// FUNÇÃO TAL
				break;

			case 4:
				// FUNÇÃO TAL
				break;

			case 5:
				// FUNÇÃO TAL
				break;

			case 6:
				// FUNÇÃO TAL
				break;

			default:
				// MENSAGEM DE ERRO
				ast();
				printf("Valor inválido, digite novamente:\n");
				ast();
				break;

		}

	} while(op != 0);

*/


	return 0; }


