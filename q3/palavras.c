#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unidades.h"
#include "palavras.h"
#include "arquivo.h"

// Aloca espaço para uma nova palavra inglesa que vai para a LISTA;
PALAVRA_ENG *aloca_PALAVRA_ENG(){
	PALAVRA_ENG *nova;
	nova = (PALAVRA_ENG *) malloc(sizeof(PALAVRA_ENG));
	nova->prox = NULL;
	return nova; }

// Aloca espaço para uma nova lista de palavras em inglês;
LISTA *alocaLISTA(){
	LISTA *nova;
	nova = (LISTA *) malloc(sizeof(LISTA));
	nova->qnt = 0;

	nova->ini = NULL;
	nova->fim = NULL;

	return nova; }

// Aloca espaço para uma nova palavra que possui uma palavra portuguesa e uma lista de palavras em inglês;
PALAVRA *alocaPALAVRA(){
	PALAVRA *nova;
	nova = (PALAVRA *) malloc(sizeof(PALAVRA));
	nova->palavras_eng = NULL;
	nova->esq = NULL;
	nova->dir = NULL;
	return nova; }

// Aloca espaço para uma nova árvore de palavras que fica presente dentro de uma unidade;
arvPALAVRAS *aloca_arvPALAVRAS(){
	arvPALAVRAS *nova;
	nova = (arvPALAVRAS *) malloc(sizeof(arvPALAVRAS));
	nova->raiz = NULL;
	nova->qnt = 0;
	return nova; }

// Função que insere uma nova palavra dentro da árvore de palavras que fica dentro de uma UNIDADE
void inserir_arvPALAVRA(arvPALAVRAS *arvore, PALAVRA **aux, PALAVRA **nova) {
	
	int comparacao = 0;

	if( *aux != NULL ){
		comparacao = strcmp((*aux)->palavra_pot, (*nova)->palavra_pot);
	}

	if( *aux == NULL ){
		// arvore não possue uma raiz, então o novo é a nova raiz.
		*aux = *nova;
		(*arvore).qnt = (*arvore).qnt + 1;

	} else if( comparacao < 0 && (*aux)->esq != NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho esquerdo do NO aux.
		inserir_arvPALAVRA(arvore, &((*aux)->esq), nova);
	} else if( comparacao < 0 && (*aux)->esq == NULL ) {
		// Se o dado de novo NO for menor e o filho esquerdo do NO aux FOR NULL, 
		// Então o novo NO será o novo filho esquerdo do NO aux.
		(*aux)->esq = *nova;
		(*arvore).qnt = (*arvore).qnt + 1;
	} else if( comparacao > 0 && (*aux)->dir != NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux NÃO FOR NULL, 
		// Então o novo NO vai ser comparado ao filho direito do NO aux.
		inserir_arvPALAVRA(arvore, &((*aux)->dir), nova);
	} else if( comparacao > 0 && (*aux)->dir == NULL ) {
		// Se o dado de novo NO for maior e o filho direito do NO aux FOR NULL, 
		// Então o novo NO será o novo filho direito do NO aux.
		(*aux)->dir = *nova;
		(*arvore).qnt = (*arvore).qnt + 1;
	} }

// Salva a palavra portuguesa na estrutura PALAVRA
	// deve alocar um espaço para a nova PALAVRA
	// depois deve passar a *palavra para a estrutura recem alocada;
	// a nova palavra deve ser inserida na árvore que foi alocada em separar_palavras;
	// O endereço da nova palavra deve ser retornado
PALAVRA *palavraPOT(char *palavra, arvPALAVRAS **arvore) {	
	int i;
	PALAVRA *nova;
	PALAVRA *raiz;

	if( *arvore == NULL )
		*arvore = aloca_arvPALAVRAS();

	nova = alocaPALAVRA();
	strcpy(nova->palavra_pot, palavra);
	inserir_arvPALAVRA(*arvore, (&(*arvore)->raiz), &nova );
	return nova; }

// Função que verifica se a LISTA está vazia.
	// retorna 0 caso NÃO esteja vazia.
	// retorna 1 caso SIM estaja vazia.
int vazia(LISTA *lista){
	int vazia = 0;
	if( (*lista).ini == NULL ){
		vazia = 1; }
	return vazia; }

// Função que insere uma palavra inglesa na lista presente na palavra_atual;
void inserirLISTA(LISTA *lista, PALAVRA_ENG *nova){
	
	/*  strcmp(string1, string2);

		Possíveis valores de retorno:
		0: conteúdo das strings são iguais
		< 0: conteúdo da string1 é menor do que string2
		> 0: conteúdo da string1 é maior do que string2 */

	int comparacao;
	int trava = 0;
	PALAVRA_ENG *ant, *aux;

	if( vazia(lista) == 1 ){ // Se a Lista tá vazia
		// No vai ser o primeiro e o último item da lista;
		(*lista).ini = nova;
		(*lista).fim = nova;

	} else if( strcmp(nova->palavra_eng, lista->ini->palavra_eng) < 0 ){ 

		// Se o novo elemento tem que ficar na primeira posição.
		(*nova).prox = (*lista).ini;
		(*lista).ini = nova;

	} else if( strcmp(nova->palavra_eng, lista->fim->palavra_eng) > 0 ){ 

		// Se a info do no for maior que a do último item da lista
		lista->fim->prox = nova;
		(*lista).fim = nova;

	} else { // Se ele tem que ir para o meio da fila

		aux = (*lista).ini;
		ant = NULL;

		while( aux != NULL){

			if(trava == 0){

				if( strcmp(nova->palavra_eng, aux->palavra_eng) < 0 ) {
					// Informação do no é menor ou igual a informação de aux;

					(*ant).prox = nova; // O proximo do anterior recebe o endereço do novo elemento.
					(*nova).prox = aux; // O proximo do novo elemento recebe o endereço do elemento aux.
					trava = 1; 		  // Trava recebe 1 e evita que outras comparações sejam feitas;
				}
			}

			ant = aux;
			aux = (*aux).prox;
		}
	} 

	(*lista).qnt++;
}

// Salva a palavra inglesa na LISTA presente em uma estrutura de uma PALAVRA;
	// Uma nova PALAVRA_ENG deve ser alocada
	// Em seguida os dados que estão presentes em *palavra deve ser passada para essa nova PALAVRA_ENG
	// Depois essa PALAVRA_ENG deve ser inserida na lista presente na *palavra_atual;
void palavraENG(PALAVRA *palavra_atual, char *palavra) {
	PALAVRA_ENG *nova;
	
	nova = aloca_PALAVRA_ENG();
	strcpy(nova->palavra_eng, palavra);

	if( palavra_atual->palavras_eng == NULL )
		palavra_atual->palavras_eng = alocaLISTA();

	inserirLISTA(palavra_atual->palavras_eng, nova);
	palavra[0] = '\0'; }

// Função que separa as palavras presentes em *linha e mandam para a UNIDADE atual;
	// Deve ser alocado um espaço para o NO da árvore de palavras presente na UNIDADE; - OK
	// Função deve ir andando pela a string *linha e ir armazendo os caracteres em *palavra
	// Quando for encontrado ':', ',' ou '\n', deve se fazer as seguintes operações;
		// Caso seja encontrado ':': *palavra deve ser armazenado como nome de um NO;
		// Caso seja encontrado ',': *palavra deve ser armazenado como um NO presente na lista da palavra_atual
void separar_palavras(UNIDADE **unidade, char *linha) {
	int i;
	int j = 0;
	int auxPOT = 0; // Será 0 quando a palavra portuguesa não tiver sido salva; 1 quando já tiver sido.
	int tam; // Tamanho da string *linha;
	PALAVRA *palavra_atual;
	char palavra[51];

	tam = strlen(linha);

	for(i=0; i<tam; i++){

		if( linha[i] == ':' ){
			palavra[j] = '\0';
			palavra_atual = palavraPOT(palavra, ( &(*unidade)->arvorePALAVRAS ) );
			j = 0;
			auxPOT = 1;
		} else if( linha[i] == ',' || linha[i] == '.' ){
			palavra[j] = '\0';
			palavraENG(palavra_atual, palavra);
			j = 0;
		} else {
			palavra[j] = linha[i];
			j++;
			// printf("palavra = %s \n\n\n", palavra);
		}
	} }


// Apresenta todas as palavras presentes na lista de palavras inglesas
void apresentaLISTA(PALAVRA_ENG *palavra) {
	if(palavra != NULL){
		printf("|\t|\t| %s \n", palavra->palavra_eng);
		apresentaLISTA(palavra->prox);
	} }

// Apresentar em ordem pre-ordem
void preordem_palavra( PALAVRA *palavra ){
	if( palavra != NULL ){
		printf("|\t| %s\n", palavra->palavra_pot );
		apresentaLISTA( palavra->palavras_eng->ini ); // Apresentar a lista de palavras inglesas.
		printf("|\t|\t---------------------------- \n");
		printf("|\t------------------------------------ \n");
		preordem_palavra( palavra->esq );
		preordem_palavra( palavra->dir );
	} }

// Apresentar em ordem in-ordem
void inordem_palavra( PALAVRA *palavra ) {
	if( palavra != NULL ){
		inordem_palavra( palavra->esq );

		printf("\tPALAVRA PORTUGUES = %s \n", palavra->palavra_pot);
		apresentaLISTA(palavra->palavras_eng->ini); // Apresentar a lista de palavras inglesas.

		inordem_palavra( palavra->dir );
	} }

// Apresentar em ordem pos-ordem
void posordem_palavra( PALAVRA *palavra ) {
	if( palavra != NULL ){
		posordem_palavra( palavra->esq );		
		posordem_palavra( palavra->dir );

		printf("\tPALAVRA PORTUGUES = %s \n", palavra->palavra_pot);
		apresentaLISTA(palavra->palavras_eng->ini); // Apresentar a lista de palavras inglesas.
	} }

// Função que busca uma palavra em uma unidade;
PALAVRA *buscaPALAVRA(PALAVRA *raiz, char *palavra){
	PALAVRA *encontrado;
	encontrado = NULL;
	if( raiz != NULL ){
		if ( strcmp( raiz->palavra_pot, palavra ) == 0 ) {
			// Eles são iguais; Raiz é a unidade que armazena a palavra buscada;
			encontrado = raiz;
		} else {
			encontrado = buscaPALAVRA(raiz->esq, palavra); // Busca pelo o lado esquerdo
			if( encontrado == NULL ) // Senão ele fará outra busca pelo o lado direito;
				encontrado = buscaPALAVRA(raiz->dir, palavra); // Caso a palavra não for encontrada pelo o lado esquerdo, então deverá ser buscado pelo o lado direito.
		}
	}// Fim do if
	return encontrado; }

// Função que irá passando pelas as unidades mandando para a função buscaPALAVRA
	// retornará o que for encontrado na função buscaPALAVRA;
PALAVRA *andar_pelas_unidades(UNIDADE *raiz, char *palavra){
	PALAVRA *encontrado;
	
	encontrado = NULL;

	if( raiz != NULL ){
		encontrado = buscaPALAVRA(raiz->arvorePALAVRAS->raiz, palavra);

		if( encontrado == NULL ){
			encontrado = andar_pelas_unidades(raiz->esq, palavra); /* busque no lado esquerdo. */

			if (encontrado == NULL) /* Caso não seja encontrado no lado esquerdo, busque no lado direito. */
				encontrado = andar_pelas_unidades(raiz->dir, palavra);
		}
	}

	return encontrado; }

// Imprime os dados de uma palavra;
void imprimirPALAVRA(PALAVRA *encontrado, char *palavra){
	if( encontrado != NULL ){
		printf("\n-------------------------------------------- \n");
		printf("| %s \n", encontrado->palavra_pot);
		apresentaLISTA(encontrado->palavras_eng->ini);
		printf("-------------------------------------------- \n");
	} else printf("A palavra %s nao foi encontrada! \n", palavra); }


// Função que solicita que o usuário digite a palavra que deseja buscar
// Em seguida, ele realiza a busca da palavra
// E por fim, chama a função que apresenta o que foi encontrado.
void gestao_imprimirPALAVRA(UNIDADE *raiz){

	PALAVRA *encontrado;
	char palavra[51];

	printf("Digite a palavra que deseja buscar: ");
	scanf(" %[^\n]s", palavra );
	setbuf(stdin, NULL);
	maiusculo(palavra);
	encontrado = andar_pelas_unidades(raiz, palavra);
	imprimirPALAVRA(encontrado, palavra); }


// Função que retorna a quantidade de filhos que o NO possui.
int qnt_filhos(PALAVRA *aux) {
	printf("qnt_filhos\n");
	int qnt;
	if( aux->esq != NULL && aux->dir != NULL )
		qnt = 2;
	else if( aux->esq == NULL && aux->dir == NULL  )
		qnt = 0;
	else
		qnt = 1;
	return qnt; }

// Remover um NO que possui 1 filho.
	// Ele realiza a troca dos valores
	// E em seguida remove a folha;
PALAVRA *remove_pai_um(PALAVRA *raiz){
	printf("remove_pai_um\n");
	PALAVRA *aux;
	PALAVRA *copia;
	
	copia = alocaPALAVRA();

	if( raiz->esq != NULL )
		aux = raiz->esq;
	else
		aux = raiz->dir;

	*copia = *raiz;
	*raiz = *aux;
	*aux = *copia;

	raiz->esq = aux->esq;
	raiz->dir = aux->dir;

	free(aux);
	free(copia);
	aux = NULL;

	return raiz; }

// Função que retorna o NO que possui o maior valor que se encontra na esquerda do NO aux;
PALAVRA *maior_da_esquerda(PALAVRA *aux){
	PALAVRA *resultado;
	resultado = NULL;
	if( aux != NULL ){
		if( aux->dir == NULL )
			resultado = aux;
		else
			resultado = maior_da_esquerda(aux->dir); }
	return resultado; }

// Função que remove um NO que possui dois filhos;
void remove_com_dois_filhos(PALAVRA **aux){
	
	PALAVRA *maior;
	PALAVRA *aux2; // Tem que ser do tipo do conteudo do NO.

	aux2 = alocaPALAVRA();

	// Procurar o maior da esquerda:
	maior = maior_da_esquerda((*aux)->esq);

	if(maior != NULL) {
		// Tirar as ligações
		(*aux)->esq = maior->esq;

		// Troca dos dados:
		*aux2 = **aux;
		**aux = *maior;
		*maior = *aux2;
		
		free(maior);
		free(aux2);
		maior = NULL;
	} }

// Função que chama as funções de remover
	// trava 1 - Foi encontrado e removido
	// trava 0 - Não foi encontrado e não foi removido.
void remover(PALAVRA **raiz, char *palavra, int *trava){
	
	int comparacao;
	PALAVRA *aux;
	int qnt;

	if( *raiz != NULL ) {
		comparacao = strcmp(palavra, (*raiz)->palavra_pot);
	}

	if( *raiz == NULL ){
		// raiz é nula. o valor não foi encontrado.
		 printf("Valor %s nao foi encontrado! \n", palavra);
	} else if( comparacao == 0 ){
		// é o mesmo valor!
		qnt = qnt_filhos(*raiz);
		*trava = 1;

		if(qnt == 0){
			free(*raiz);
			*raiz = NULL;
		} else if(qnt == 1)
			*raiz = remove_pai_um(*raiz);
		else
			remove_com_dois_filhos(raiz);

	} else if( comparacao > 0 ) {
		remover(&(*raiz)->esq, palavra, trava);

	} else if( comparacao < 0 ) {
		remover(&(*raiz)->dir, palavra, trava);
	} }

void andar_pelas_unidades_remocao(UNIDADE *raiz, char *palavra){

	int trava = 0;

	printf("andar_pelas_unidades_remocao\n");

	if( raiz != NULL ) {
		remover(&raiz->arvorePALAVRAS->raiz, palavra, &trava);

		if( trava == 0 ) {
			andar_pelas_unidades_remocao(raiz->esq, palavra); /* busque no lado esquerdo. */

			if ( trava == 0 ) /* Caso não seja encontrado no lado esquerdo, busque no lado direito. */
				andar_pelas_unidades_remocao(raiz->dir, palavra); } } }

void gestao_removePALAVRA(arvUNIDADE *arvPRINCIPAL) {
	char palavra[51];
	printf("Digite o PALAVRA que deseja REMOVER: ");
	scanf(" %[^\n]s", palavra );
	setbuf(stdin, NULL); // Limpesa do buffer
	maiusculo(palavra); // Deixa tudo em maiusculos.
	andar_pelas_unidades_remocao( arvPRINCIPAL->raiz, palavra ); }
