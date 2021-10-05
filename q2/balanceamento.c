#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#include "arvoreAVL.h"
#include "balanceamento.h"
// balanceamento.c

// Função que ajusta a altura do NO raiz verificando a altura de seus filhos.
void ajustaALTURA(NO *raiz){

	if( raiz != NULL ) {
		if( raiz->esq == NULL && raiz->dir == NULL ){
			// É UM NO FOLHA
			raiz->altura = 0;
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
		} 
	} }

// Função que calcula o fator de balanceamento;
int fatorBALANCEAMENTO(NO *raiz){
	
	int esquerda;
	int direita;
	int resultado = 0;

	if( raiz != NULL ) {
		
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
		}

		resultado = esquerda - direita;
	}
	return resultado; }

// função que faz um giro no sentido funcao horario
void horario(NO **raiz, NO *aux){
	(*raiz)->esq = aux->dir;
	ajustaALTURA(*raiz);
	aux->dir = *raiz;
	ajustaALTURA(aux);
	*raiz = aux;
	}

// função que faz um giro no sentido anti-horario
void antihorario(NO **raiz, NO *aux){
	(*raiz)->dir = aux->esq;
	ajustaALTURA(*raiz);
	aux->esq = *raiz;
	ajustaALTURA(aux);
	*raiz = aux; }

void galho_de_dentro_esquerda(NO **raiz, NO *no) {
	int fb;
	NO *no1;
	no1 = NULL;
	fb = fatorBALANCEAMENTO(no);
	if( fb <= (-1) ) {
		no1 = no->dir;
		(*no).dir = (*no1).esq;
		ajustaALTURA(no);
		no1->esq = no;
		ajustaALTURA(no1);
		(*raiz)->esq = no1;
		ajustaALTURA(*raiz);
		no = no1;		
	} 
}

void galho_de_dentro_direita(NO **raiz, NO *no) {
	int fb;
	NO *no1;
	no1 = NULL;
	fb = fatorBALANCEAMENTO(no);
	if( fb >= 1 ) {
		no1 = no->esq;
		(*no).esq = (*no1).dir;
		ajustaALTURA(no);
		no1->dir = no;
		ajustaALTURA(no1);
		(*raiz)->dir = no1;
		ajustaALTURA(*raiz);
		no = no1;
	} }

// Função que faz a chamada para as funções que realizam o balanceamento;
void gestaoHORARIO(NO **raiz){
	
	NO **aux;
	aux = &(*raiz)->esq;
	int fb;

	galho_de_dentro_esquerda(raiz, *aux);
	ajustaALTURA(*raiz);

	fb = fatorBALANCEAMENTO(*raiz);

	if( fb < -1 || fb > 1){
		aux = &(*raiz)->esq;
		horario(raiz, *aux);
	}
}

// Função que faz a chama para as funções que realizam o balanceamento;
void gestaoANTIHORARIO(NO **raiz) {
	
	NO **aux;
	aux = &(*raiz)->dir;
	int fb;

	galho_de_dentro_direita(raiz, *aux);
	ajustaALTURA(*raiz);

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
	ajustaALTURA(*raiz);

	if( *raiz != NULL ) {
		ajustaALTURA(*raiz);
		fb = fatorBALANCEAMENTO(*raiz);

		if( fb < -1 || fb > 1 ){
			// Está desbalanceado!
			//printf("Houve balanceamento. raiz->altura = %d \n", (*raiz)->altura);
			if( fb > 1 ) {
				// O lado esquerdo está pendendo.
				gestaoHORARIO(raiz); // Rotação horaria.
			} else {
				// O lado direito está pendendo.
				gestaoANTIHORARIO(raiz); // Rotação antihoraria
			}
			ajustaALTURA(*raiz);
			//printf("FINALIZOU e a raiz eh %d! - raiz->altura = %d \n", (*raiz)->info, (*raiz)->altura);
		}
	}
}