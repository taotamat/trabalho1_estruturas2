//structs
typedef struct ARVORE{
    int info;
    struct ARVORE *esq;
    struct ARVORE *dir;
}ARVORE;

//declaracao das funções
ARVORE *alocaARV();
void gestaoINSERIR(ARVORE *arvore, int num);
void inserir(ARVORE *arvore, ARVORE *no);
void freeARV(ARVORE *aux);
int busca(ARVORE *aux, int num);
int profundidade(ARVORE *avr, int valor);
void maiorFolha(ARVORE *avr, ARVORE *aux, int *maior, int *prMaior);
void menorFolha(ARVORE *avr,ARVORE *aux, int *menor, int *prMenor);
void etapa1(ARVORE *avr, double *somaTempo);
void etapa2(ARVORE *avr, int *d);
void etapa3(ARVORE *avr,double *somaBusca);
void start();
void inordem(ARVORE *aux);