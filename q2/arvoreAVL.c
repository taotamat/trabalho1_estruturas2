#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#include "arvoreAVL.h"
#include "balanceamento.h"

int alturaNO(NO *avr){
    return (avr == NULL) ? 0 : avr->altura; 
}

int maior(int a, int b){
    return (a > b) ? a : b;
}

NO *novoNO(int valor){
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->info = valor;
    novo->altura = 0;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

void freeARV(NO *aux){
	if(aux != NULL){
		freeARV(aux->esq); // libera sae  
		freeARV(aux->dir); // libera sad  
		free(aux); 
	}
}


// Função recursiva que insere o novo NO na árvore.
void inserir(NO **aux, NO *novo) {

	//printf("INSERIR\n");

	if( *aux == NULL ){
		// arvore não possue uma raiz, então o novo é a nova raiz.
		*aux = novo;
	} else if( novo->info < (*aux)->info ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho esquerdo do NO aux.
		inserir(&((*aux)->esq), novo);
	} else {
		// Se o dado de novo NO for maior e o filho direito do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho direito do NO aux.
		inserir(&((*aux)->dir), novo);
	}


	/*
	if( *aux == NULL ){
		// arvore não possue uma raiz, então o novo é a nova raiz.
		*aux = novo;

	} else if( novo->info < (*aux)->info && (*aux)->esq != NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho esquerdo do NO aux.
		inserir(&((*aux)->esq), novo);

	} else if( novo->info < (*aux)->info && (*aux)->esq == NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux FOR NULL, 
		// Então o novo NO será o novo filho esquerdo do NO aux.
		(*aux)->esq = novo;

	} else if( novo->info > (*aux)->info && (*aux)->dir != NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho direito do NO aux.
		inserir(&((*aux)->dir), novo);

	} else if( novo->info > (*aux)->info && (*aux)->dir == NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux FOR NULL, 
		// Então o novo NO será o novo filho direito do NO aux.
		(*aux)->dir = novo;
	} */

	ajustaALTURA(aux);
	gestaoBALANCEAMENTO(aux); 

	//ast();

}


// Função que aloca espaço para um novo NO e chama a função de leitura.
NO *gestaoLER(NO **arvore, int valor) {
	NO *novo;
	novo = novoNO(valor);
	inserir(arvore, novo);
	return *arvore;
}


int busca(NO *aux, int num) {

	int resultado=0;
	
	if( aux != NULL ) {
		if( aux->info == num ){
			resultado = 1;
		}
			
		else if( num < aux->info ){
			resultado = busca(aux->esq, num);
		}
			
		else if( num > aux->info ){
			resultado = busca(aux->dir, num);
		}
			
	}

	return resultado; 

}


void etapa1(NO **avr, double *somaTempo){
    printf("etapa 1 <--------------------\n");
    int i, num;
	double tempo_final;
	clock_t tempo;
	tempo = clock();
    for(i=1;i<=1000;i++){
		if(i%2==0){
			num = numAleatorio(20000);
		}
		else{
			num = numAleatorio2(10000,60000);
		}

		//printf("Chegou aqui * \n");
		// printf("num = %d \n", num);

        *avr = gestaoLER(avr,num);
    }
	tempo = clock() - tempo;
	tempo_final = (((double)tempo)/((CLOCKS_PER_SEC/1000)));
	*somaTempo += tempo_final;
	printf("Tempo de inserção = %lf ms\n",tempo_final);
}

void etapa2(NO *avr, int *d){
	printf("etapa 2 <--------------------\n");

	int esquerda, direita;

	if( avr->esq == NULL )
		esquerda = 0;
	else
		esquerda = avr->esq->altura;

	if( avr->esq == NULL )
		direita = -1;
	else
		direita = avr->dir->altura;

    *d = labs(esquerda - direita);
	printf("FOLHAS:\n");
	printf("altura do avr->esq->altura = %d \n", esquerda);
	printf("altura do avr->dir->altura = %d \n", direita);
	//printf("altura esq - altura dir = %d \n-------------\n", avr->esq->altura - avr->dir->altura);

    printf("Diferenca: %d - %d = %d\n",esquerda,direita, *d);
}

//buscar os valores
void etapa3(NO *avr, double *somaBusca){
	printf("etapa 3 <--------------------\n");
	int nums[5] = {100,500,1000,5000,10000};
	double tempo_final;
	int i,r;
	clock_t tempo;
	printf("BUSCA:\n");
	for(i=0;i<5;i++){
		tempo = clock();
		r = busca(avr, nums[i]);
		tempo = clock() - tempo;
		tempo_final = (((double)tempo)/((CLOCKS_PER_SEC/1000)));
		*somaBusca += tempo_final;
		printf("[ %d ] - ",nums[i]);
		printf("tempo de procura = %lf ms  ",tempo_final);
		if(r!=0){
			printf("- encontrado\n");
		}
		else{
			printf("- nao encontrado\n");
		}
	}
}

void start(){
	int i,v[30];
	clock_t tempo;
	tempo = clock();
	double somaTempo=0, somaBusca=0, tempo_final;
	NO *avrPRINCIPAL;
	srand(time(NULL));
	for(i=0;i<30;i++){
		ast();
		avrPRINCIPAL = NULL;
		printf("ARVORE [ %d ]\n",i+1);
		etapa1(&avrPRINCIPAL,&somaTempo); 	// Inserção dos valores aleatórios na árvore.
		etapa2(avrPRINCIPAL,&v[i]);			// Calcular a diferença da profundidade.
		etapa3(avrPRINCIPAL,&somaBusca); 	// Buscar os valores na árvore.
		freeARV(avrPRINCIPAL);
		ast();
	}
	ast();
	printf("RESULTADOS:\n");
	contabilizar(v,30);
	tempo = clock() - tempo;
	tempo_final = (((double)tempo)/((CLOCKS_PER_SEC/1000)));
	ast();
	printf("Tempo médio de inserçao = %lf ms\n",somaTempo/30);
	printf("Tempo medio de busca = %lf ms\n",(somaBusca)/(30*5));
	printf("Execucao = %lf ms\n",tempo_final);
	ast();

}
