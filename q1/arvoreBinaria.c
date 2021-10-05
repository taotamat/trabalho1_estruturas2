#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvoreBinaria.h"
#include "funcoes.h"

ARVORE *alocaARV(){
	ARVORE *novo;
	novo = (ARVORE *) malloc(sizeof(ARVORE));
	if(novo != NULL) {
		(*novo).esq = NULL;
		(*novo).dir = NULL;
	} else printf("Erro!\n");
	return novo; 
}


void gestaoINSERIR(ARVORE *arvore, int num) {
	ARVORE *novo;
	novo = alocaARV();
	novo->info = num;
	inserir(arvore,novo); 
}

void inserir (ARVORE *avr, ARVORE *no){
    if (avr == NULL){
        avr = no;
    }

    else if (no->info < avr->info){
        if(avr->esq == NULL){
            avr->esq = no;
        }
        else{
            inserir(avr->esq,no);
        }
    }

    else if (no->info >= avr->info){
        if(avr->dir == NULL){
            avr->dir = no;
        }
        else{
            inserir(avr->dir,no);
        }
        
    }
 
}

int busca(ARVORE *aux, int num) {

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

void freeARV(ARVORE *aux){
	if(aux != NULL){
		freeARV(aux->esq); // libera sae  
		freeARV(aux->dir); // libera sad  
		free(aux); 
	}
}


int profundidade(ARVORE *avr, int valor){
    int resultado=0;
    if(avr != NULL){
		if( avr->info == valor )
			resultado = 0;
		else if( valor < avr->info )
			resultado = 1 + profundidade(avr->esq, valor);
		else if( valor > avr->info )
			resultado = 1 + profundidade(avr->dir,valor);
    }
	return resultado;
}

void maiorFolha(ARVORE *avr, ARVORE *aux, int *maior, int *prMaior){
	int pr;
	if(avr!=NULL){
		maiorFolha(avr->esq, aux, maior, prMaior);
		maiorFolha(avr->dir, aux,maior, prMaior);
		if((avr->esq == NULL) && (avr->dir == NULL)){
			pr = profundidade(aux, avr->info);
			if(pr > *prMaior){
				*prMaior = pr;
				*maior = avr->info;
			}
		}
		
	}
}

void menorFolha(ARVORE *avr,ARVORE *aux, int *menor, int *prMenor){	
	int pr;
	if(avr!=NULL){
		menorFolha(avr->esq,aux,menor,prMenor);
		menorFolha(avr->dir, aux, menor,prMenor);
		if((avr->esq==NULL) && (avr->dir==NULL)){
			pr = profundidade(aux, avr->info);
			if(pr < *prMenor){	
				*menor = avr->info;
				*prMenor = pr;
			}
		}
	}
}

//inserir os valores na arvore
void etapa1(ARVORE *avr, double *somaTempo){
    int i, num;
	clock_t tempo;
	double tempo_final;

	tempo = clock();
	
    for(i=1;i<=1000;i++){
		if(i%2==0){
			num = numAleatorio(20000);
		}
		else{
			num = numAleatorio2(1000,60000);
		}
        gestaoINSERIR(avr,num);
    }
	tempo = clock() - tempo;
	tempo_final = (((double)tempo)/((CLOCKS_PER_SEC/1000)));
	*somaTempo += tempo_final;
	printf("Tempo de inserção = %lf ms\n",tempo_final);
}


//calcular a diferenca da profundidade
void etapa2(ARVORE *avr, int *d){
    int maior, prMaior=0;
    int menor, prMenor=100000;
    maiorFolha(avr,avr,&maior,&prMaior);
    menorFolha(avr,avr,&menor,&prMenor);
    *d = prMaior - prMenor;
	printf("FOLHAS:\n");
    printf("nivel de maior profundidade: %d (%d)\n",prMaior,maior);
    printf("nivel de menor profundidade: %d (%d)\n",prMenor,menor);
    printf("Diferenca: %d - %d = %d\n",prMaior,prMenor,*d);
}

//buscar os valores
void etapa3(ARVORE *avr, double *somaBusca){
	int nums[5] = {100,500,1000,5000,10000};
	int i,r;
	clock_t tempo;
	double tempo_final;
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
	ARVORE *avrPRINCIPAL;
	tempo = clock();
	double somaTempo=0, somaBusca=0, tempo_final;
	srand(time(NULL));
	for(i=0;i<30;i++){
		ast();
		avrPRINCIPAL = alocaARV();
		printf("ARVORE [ %d ]\n",i+1);
		etapa1(avrPRINCIPAL,&somaTempo);
		//inordem(avrPRINCIPAL);
		etapa2(avrPRINCIPAL,&v[i]);
		etapa3(avrPRINCIPAL,&somaBusca);
		freeARV(avrPRINCIPAL);
		ast();
	}
	ast();
	printf("RESULTADOS:\n");
	contabilizar(v,30); // Contabiliza qnts vezes a diferença entre -3,-2,-1,0,1,2,3
	tempo = clock() - tempo;
	tempo_final = (((double)tempo)/((CLOCKS_PER_SEC/1000)));
	ast();
	printf("Tempo médio de inserçao = %lf ms\n",somaTempo/30);
	printf("Tempo medio de busca = %lf ms\n",(somaBusca)/(30*5));
	printf("Execucao = %lf ms\n",tempo_final);
	ast();
}

