typedef struct NO{
    int altura;
    int info;
    struct NO *esq;
    struct NO *dir;
}NO;

int alturaNO(NO *avr);
int maior(int a, int b);
NO *novoNO(int valor);
void freeARV(NO *aux);
void inserir(NO **aux, NO *novo);
NO *gestaoLER(NO **arvore, int valor);
void etapa1(NO **avr, double *somaTempo);
void etapa2(NO *avr, int *d);
void etapa3(NO *avr, double *somaBusca);
void start();