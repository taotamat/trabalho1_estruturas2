#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#include "sodium.h"

void ast(){

	printf("-------------------------------------------------------------\n");
 
}

//funcao para gerar numeros aleatorios
int numAleatorio(int x){
    int n;
    n = rand()%x;
    return n;
}

int numAleatorio2(int min, int max){
    int num;
    num = ((rand() % (int)(((max) + 1) - (min))) + (min));
    return num;
}

int menorValor(int v[], int tam){
    int menor = v[0];
    int i;
    for(i=0;i<tam;i++){
        if(v[i] < menor){
            menor = v[i];
        }
    }
    return menor;
}

int maiorValor(int v[], int tam){
    int maior = v[0];
    int i;
    for(i=0;i<tam;i++){
        if(v[i] > maior){
            maior = v[i];
        }
    }
    return maior;
}

int contador(int v[], int n, int id, int tam){
    int c=0;
    if(id < tam){
        if(v[id]==n){
            c = 1 + contador(v,n,++id,tam);
        }
        else{
            c = 0 + contador(v,n,++id,tam);
        }
    }

    return c;
}

void contabilizar(int v[], int tam){
    int i, cont;
    int menor = menorValor(v,tam);
    int maior = maiorValor(v,tam);
    for(i=menor;i<=maior;i++){
        cont = contador(v,i,0,tam);
        if(cont != 0){
            printf("%d aparece %d vezes \n",i,cont);
        }      
    }
}