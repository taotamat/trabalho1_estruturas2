// Contém as funções que gerenciarão os dados do arquivo.txt;

// Declarações das funções
void ast();
void maiusculo(char *palavra);
void lerLINHA(FILE *arq, char *linha);
void marcar_tempo(FILE *arq, char *nome, int op, clock_t *tempo_inicial);
void gestaoLER(FILE *arq, arvUNIDADE *avrPRINCIPAL);