typedef struct UNIDADE {
	char nome[51];
	int qnt; // Quantidade de palavras presentes na unidade;
	struct arvPALAVRAS *arvorePALAVRAS;

	struct UNIDADE *esq;
	struct UNIDADE *dir;
	
} UNIDADE;

typedef struct arvUNIDADE {
	int qnt; // Quantidade de unidades presentes nessa árvore;
	struct UNIDADE *raiz;
} arvUNIDADE;

// Declarações das funções
UNIDADE *alocaUNIDADE();
arvUNIDADE *aloca_arvUNIDADE();
void nomeaUNIDADE(UNIDADE *nova, char *linha);
void inserir_arvUNIDADE(arvUNIDADE *avrPRINCIPAL, UNIDADE **aux, UNIDADE *nova);
UNIDADE *nova_unidade(arvUNIDADE *avrPRINCIPAL, char *linha);
void preordem_unidade(UNIDADE *unidade);
void inordem_unidade(UNIDADE *unidade);
void posordem_unidade(UNIDADE *unidade);
UNIDADE *buscaUNIDADE(UNIDADE *unidade, char *palavra);
void imprimirUNIDADE(UNIDADE *encontrado, char *palavra);
void gestao_imprimirUNIDADE(arvUNIDADE *arvPRINCIPAL);