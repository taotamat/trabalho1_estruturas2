typedef struct PALAVRA_ENG {
	char palavra_eng[51]; // palavra inglesa;
	struct PALAVRA_ENG *prox;
} PALAVRA_ENG;

typedef struct LISTA {
	int qnt; // Quantidade de palavras inglesas presentes na lista.
	
	struct PALAVRA_ENG *ini;
	struct PALAVRA_ENG *fim;

} LISTA;


typedef struct PALAVRA {
	char palavra_pot[51]; // Palavra em português;
	struct LISTA *palavras_eng; // Lista de palavras inglesas equivalentes a palavra_pot;
	
	int altura;

	struct PALAVRA *esq;
	struct PALAVRA *dir;

} PALAVRA;


typedef struct arvPALAVRAS {
	int qnt; // Quantidade de palavras presentes na árvore
	struct PALAVRA *raiz;
} arvPALAVRAS;

// Declarações das funções:
PALAVRA_ENG *aloca_PALAVRA_ENG();
LISTA *alocaLISTA();
PALAVRA *alocaPALAVRA();
arvPALAVRAS *aloca_arvPALAVRAS();
void inserir_arvPALAVRA(arvPALAVRAS *arvore, PALAVRA **aux, PALAVRA **nova);
PALAVRA *palavraPOT(char *palavra, arvPALAVRAS **arvore);
int vazia(LISTA *lista);
void inserirLISTA(LISTA *lista, PALAVRA_ENG *nova);
void palavraENG(PALAVRA *palavra_atual, char *palavra);
void separar_palavras(UNIDADE **unidade, char *linha);
void apresentaLISTA(PALAVRA_ENG *palavra);
void preordem_palavra( PALAVRA *palavra );
void inordem_palavra( PALAVRA *palavra );
void posordem_palavra( PALAVRA *palavra );
PALAVRA *buscaPALAVRA(PALAVRA *raiz, char *palavra);
PALAVRA *andar_pelas_unidades(UNIDADE *raiz, char *palavra);
void imprimirPALAVRA(PALAVRA *encontrado, char *palavra);
void gestao_imprimirPALAVRA(UNIDADE *raiz);
int qnt_filhos(PALAVRA *aux);
PALAVRA *remove_pai_um(PALAVRA *raiz);
PALAVRA *maior_da_esquerda(PALAVRA *aux);
void remove_com_dois_filhos(PALAVRA **aux);
void remover(PALAVRA **raiz, char *palavra, int *trava);
void andar_pelas_unidades_remocao(UNIDADE *raiz, char *palavra);
void gestao_removePALAVRA(arvUNIDADE *arvPRINCIPAL);