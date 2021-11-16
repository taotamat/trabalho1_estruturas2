#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#include "arvoreAVL.h"
#include "balanceamento.h"
// balanceamento.c

// Função que ajusta a altura do NO raiz verificando a altura de seus filhos.
void ajustaALTURA(NO **raiz){

	//printf("ajustaALTURA, ");

	int esquerda, direita;

	if( *raiz != NULL ) {

		if( (*raiz)->esq == NULL && (*raiz)->dir == NULL ){
			// É UM NO FOLHA
			(*raiz)->altura = 0;
		
		} else {

			if( (*raiz)->esq != NULL )
				esquerda = (*raiz)->esq->altura;
			else
				esquerda = -1;


			if( (*raiz)->dir != NULL )
				direita = (*raiz)->dir->altura;
			else
				direita = -1;


			if( esquerda > direita )
				(*raiz)->altura = esquerda + 1;
			else
				(*raiz)->altura = direita + 1;
		}

		/*
		
		} else if( raiz->esq != NULL && raiz->dir != NULL ){
			// É UM NO PAI DE DOIS FILHOS
			if( raiz->esq->altura >= raiz->dir->altura  )
				raiz->altura = raiz->esq->altura + 1; // esquerda possui a altura maior;
			else
				raiz->altura = raiz->dir->altura + 1; // direita possui a altura maior;
		} else {
			// É UM NO PAI QUE POSSUI APENAS UM FILHO
			if( raiz->esq != NULL )
				raiz->altura = raiz->esq->altura + 1; // Raiz só possui o filho da esquerda.
			else
				raiz->altura = raiz->dir->altura + 1; // Raiz só possui o filho da direita.
		} */
	}



}

// Função que calcula o fator de balanceamento;
int fatorBALANCEAMENTO(NO *raiz){
	
	// Retorna -100 caso a raiz seja NULL.

	//printf("fatorBALANCEAMENTO, ");

	int esquerda = (-1);
	int direita = (-1);
	int resultado = -100;

	if( raiz != NULL ) {


		if( raiz->esq != NULL )
			esquerda = raiz->esq->altura;


		if( raiz->dir != NULL )
			direita = raiz->dir->altura;

		/*
		
		if( raiz->esq == NULL && raiz->dir == NULL ){
			// raiz não possui nenhum filho.
			esquerda = -1;
			direita = -1;
		} else if( raiz->esq != NULL && raiz->dir != NULL ){
			// raiz possui os dois filhos. 
			esquerda = raiz->esq->altura;
			direita = raiz->dir->altura;
		} else {
			// Raiz só possui 1 filho.
			if( raiz->esq != NULL ){
				// Raiz possui o filho da esquerda.
				esquerda = raiz->esq->altura;
				direita = -1;
			} else {
				// Raiz possui o filho da direita.
				direita = raiz->dir->altura;
				esquerda = -1; } 
		}*/

		resultado = esquerda - direita;

		if( resultado < (-1) ){ // Acrescentei essa padronização.
			resultado = (-2);

		} else if( resultado > 1 ){
			resultado = 2; }

		//printf("resultado = %d \n", resultado);
	}

	return resultado; }

// função que faz um giro no sentido funcao horario
void horario(NO **raiz, NO *aux){
	//printf("horario, ");
	(*raiz)->esq = aux->dir;
	aux->dir = *raiz;
	ajustaALTURA(raiz);
	ajustaALTURA(&aux);
	*raiz = aux; 
	ajustaALTURA(raiz);
	} // Fim da função.

// função que faz um giro no sentido anti-horario
void antihorario(NO **raiz, NO *aux){
	//printf("antihorario, ");
	(*raiz)->dir = aux->esq;
	aux->esq = *raiz;
	ajustaALTURA(raiz);
	ajustaALTURA(&aux);
	*raiz = aux;
	ajustaALTURA(raiz);
	

} // Fim da função.

// Função que ajusta o galho de dentro
void galho_de_dentro_esquerda(NO **raiz, NO *no) {
	
	//printf("galho_de_dentro_esquerda, ");

	int fb;
	NO *no1;
	no1 = NULL;
	fb = fatorBALANCEAMENTO(no);
	//printf("fb = %d \n", fb);
	if( fb < (-1) ) {

		//printf("no->dir e no->esq = %p e %p \n", no->dir, no->esq);
		//printf("no1->dir e no1->esq = %p e %p \n ", no1->dir, no1->esq);

		no1 = no->dir;
		no->dir = no1->esq;
		no1->esq = no;
		(*raiz)->esq = no1;
		ajustaALTURA(&no);
		ajustaALTURA(&no1);
		ajustaALTURA(raiz);
		no = no1;		
	} }

// Ajusta o galho de dentro.
void galho_de_dentro_direita(NO **raiz, NO *no) {
	
	//printf("galho_de_dentro_direita, ");

	int fb;
	NO *no1;
	no1 = NULL;

	fb = fatorBALANCEAMENTO(no);
	if( fb >= 1 ) {
		no1 = no->esq;
		no->esq = no1->dir;
		no1->dir = no;
		(*raiz)->dir = no1;
		ajustaALTURA(&no);
		ajustaALTURA(&no1);
		ajustaALTURA(raiz);
		no = no1;
	} 

}

// Função que faz a chamada para as funções que realizam o balanceamento;
void gestaoHORARIO(NO **raiz){
	
	//printf("gestaoHORARIO, ");

	NO **aux;
	aux = &(*raiz)->esq;
	int fb;

	galho_de_dentro_esquerda(raiz, *aux);
	ajustaALTURA(raiz);

	fb = fatorBALANCEAMENTO(*raiz);

	if( fb < -1 || fb > 1){
		aux = &(*raiz)->esq;
		horario(raiz, *aux);
	} }

// Função que faz a chama para as funções que realizam o balanceamento;
void gestaoANTIHORARIO(NO **raiz) {
	
	//printf("gestaoANTIHORARIO, ");

	NO **aux;
	aux = &(*raiz)->dir;
	int fb;

	galho_de_dentro_direita(raiz, *aux);
	ajustaALTURA(raiz);

	if(fb < -1 || fb > 1){
		aux = &(*raiz)->dir;
		antihorario(raiz, *aux);
	} }

// Função que chama as funções de balanceamento;
void gestaoBALANCEAMENTO(NO **raiz) {

	// Faz o calculo de balanceamento
		// Se o calculo de balanceamento dê -2 ou 2:
			// Verifica qual função deve ir:
				// Se o lado pendente for o esquerdo: ir pra função horário;
				// Se o lado pendente for o direito: ir para a função anti-horário;

	int fb; // Fator de balanceamento.
	//ajustaALTURA(raiz);

	//printf("gestaoBALANCEAMENTO, ");

	if( *raiz != NULL ) {
		//printf("raiz = %d \n", (*raiz)->info);
		// ajustaALTURA(*raiz);
		fb = fatorBALANCEAMENTO(*raiz);

		if( fb == (-2) || fb == 2 ){
			// Está desbalanceado!
			//printf("Houve balanceamento. raiz->altura = %d \n", (*raiz)->altura);
			if( fb == 2 ) {
				// O lado esquerdo está pendendo.
				gestaoHORARIO(raiz); // Rotação horaria.
			} else {
				// O lado direito está pendendo.
				gestaoANTIHORARIO(raiz); // Rotação antihoraria
			}
			
			ajustaALTURA(raiz);
			//printf("FINALIZOU e a raiz eh %d! - raiz->altura = %d \n", (*raiz)->info, (*raiz)->altura);
		}
	} 
}