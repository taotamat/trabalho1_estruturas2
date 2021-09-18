## Códigos do Primeiro Trabalho da disciplina de Estruturas de Dados II

<b>Questão 01:</b> Faça um programa em C que gere 1000 números aleatórios, insira-os em uma árvore binária de busca, incialmente vazia. Os valores para compor a árvore devem ser gerados aleatoriamente utilizando 2 métodos para garantir a aleatoriedade. Depois imprima o nível da folha de maior profundidade e o nível da folha de menor profundidade. Repita o processo 30 vezes. Depois mostre quantas das 30 vezes a diferença entre a profundidade máxima e mínima foram de 0, 1, 2 , 3 e assim por diante. Também contabilize o tempo gasto para inserir todos os elementos na árvore. E depois em cada uma das inserções faça experimento de verificar o tempo de busca de elementos, use sempre os mesmo elementos em todos os experimentos. **Obs**. 1: Todas as vezes que for criar uma nova árvore, você deve liberar a anterior, para que você tenha memória disponível.
<br>
<b>Questão 02:</b> Repita o exercício 1 utilizando árvores AVL. Compare os resultados obtidos entre as árvores binárias e as árvores AVL.
<br>
<b>Questão 03:</b> Cada unidade em um livro-texto inglês contém um vocabulário Inglês-Português de palavras que são usadas pela primeira vez em uma unidade em particular. Faça um programa que converta um conjunto de tais vocabulários armazenados em um arquivo Inglês em um conjunto de vocabulários Português-Inglês. Para isso considere que:
	- a) Os nomes das unidades são precedidos por um símbolo de porcentagem.
	- b) Há somente uma entrada por linha.
	- c) Uma palavra em Inglês é separada por dois pontos de sua(s) equivalente(s) portuguesa(s); se há mais de uma equivalente, elas são separadas por vírgula.
Para produzir as palavras em ordem alfabética, crie uma árvore binária de busca para cada unidade que contenha as palavras em português, e listas ligadas das equivalentes inglesas. Assegure-se de que exista apenas um nó para cada palavra portuguesa na árvore. Além disso, permita o usuário informar uma unidade e então imprima todas as palavras da unidade em português seguida das equivalentes em inglês. Depois. imprima todas as palavras em inglês equivalentes a uma palavra em português dada, pesquisando para isso em todas as árvores das unidades cadastradas. Por fim permita o usuário remover uma determinada palavra em português de uma unidade, e consequentemente as palavras em inglês equivalentes a ela.
<br>
<b>Questão 04:</b> Repita o exercício 3 para uma árvore AVL. E depois compare o tempo de inserção e de busca na árvore do exercício 3 e do exercício 4.
<br>