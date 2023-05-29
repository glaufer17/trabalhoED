#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAVE 50

struct No {
    char chave[MAX_CHAVE];
    struct No* esquerda;
    struct No* direita;
};

/*#include <stdio.h>: Inclui a biblioteca padrão de entrada e saída em C.
#include <stdlib.h>: Inclui a biblioteca padrão de funções utilitárias em C.
#include <string.h>: Inclui a biblioteca padrão de manipulação de strings em C.
#define MAX_CHAVE 50: Define uma constante MAX_CHAVE com valor 50.
struct No: Define uma estrutura No para representar um nó da árvore Patricia.
char chave[MAX_CHAVE]: Armazena a chave do nó (uma string).
struct No* esquerda: Ponteiro para o filho esquerdo do nó.
struct No* direita: Ponteiro para o filho direito do nó.*/

struct No* criarNo(const char* chave) {
    struct No* novo_no = (struct No*)malloc(sizeof(struct No));
    strcpy(novo_no->chave, chave);
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

/*struct No* criarNo(const char* chave): Cria um novo nó com a chave especificada.
struct No* novo_no = (struct No*)malloc(sizeof(struct No)): Aloca memória para um novo nó usando malloc.
strcpy(novo_no->chave, chave): Copia a chave para o campo chave do novo nó.
novo_no->esquerda = NULL e novo_no->direita = NULL: Define os filhos esquerdo e direito como NULL.
return novo_no: Retorna o novo nó criado.*/

void inserir(const char* chave, struct No** raiz) {
    if (*raiz == NULL) {
        *raiz = criarNo(chave);
        return;
    }

/*void inserir(const char* chave, struct No** raiz): Insere uma chave na árvore Patricia.
if (*raiz == NULL): Verifica se a raiz é NULL (ou seja, a árvore está vazia).
*raiz = criarNo(chave): Cria um novo nó usando a função criarNo e atribui à raiz.
return: Retorna ao chamador.*/

    int indice = 0;
    while (indice < strlen(chave) && indice < strlen((*raiz)->chave) && chave[indice] == (*raiz)->chave[indice]) {
        indice++;
    }

/*int indice = 0: Variável para acompanhar o índice da comparação entre as chaves.
while (indice < strlen(chave) && indice < strlen((*raiz)->chave) && chave[indice] == (*raiz)->chave[indice]): Enquanto os índices estiverem dentro dos limites das chaves e os caracteres forem iguais:
indice++: Incrementa o índice para comparar o próximo caractere.
*/

    if (indice == strlen((*raiz)->chave)) {
        if (indice < strlen(chave)) {
            if ((*raiz)->direita == NULL) {
                (*raiz)->direita = criarNo(chave + indice);
            } else {
                inserir(chave + indice, &((*raiz)->direita));
            }
        }
    } else {
        struct No* novo_no = criarNo((*raiz)->chave + indice);
        strcpy((*raiz)->chave, chave);
        novo_no->esquerda = (*raiz)->esquerda;
        novo_no->direita = (*raiz)->direita;
        (*raiz)->esquerda = novo_no;
        (*raiz)->direita = NULL;
    }
}

/*if (indice == strlen((*raiz)->chave)): Se o índice for igual ao comprimento da chave do nó atual:
if (indice < strlen(chave)): Verifica se há mais caracteres na chave a serem inseridos.
if ((*raiz)->direita == NULL): Se o filho direito do nó atual for NULL, cria um novo nó à direita com a parte restante da chave.
else: Caso contrário, chama recursivamente a função inserir para o filho direito.
else: Caso contrário, significa que há uma diferença na chave atual.
struct No* novo_no = criarNo((*raiz)->chave + indice): Cria um novo nó com a parte da chave diferente.
strcpy((*raiz)->chave, chave): Copia a nova chave para o nó atual.
novo_no->esquerda = (*raiz)->esquerda e novo_no->direita = (*raiz)->direita: Atribui os filhos esquerdo e direito do nó atual ao novo nó.
(*raiz)->esquerda = novo_no e (*raiz)->direita = NULL: Define o novo nó como o filho esquerdo do nó atual e o filho direito como NULL.*/

struct No* buscar(const char* chave, struct No* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

/*struct No* buscar(const char* chave, struct No* raiz): Busca por uma chave na árvore Patricia.
if (raiz == NULL): Se a raiz for NULL (ou seja, a árvore está vazia ou a chave não foi encontrada):
return NULL: Retorna NULL indicando que a chave não foi encontrada.*/

    int indice = 0;
    while (indice < strlen(chave) && indice < strlen(raiz->chave) && chave[indice] == raiz->chave[indice]) {
        indice++;
    }

/*int indice = 0: Variável para acompanhar o índice da comparação entre as chaves.
while (indice < strlen(chave) && indice < strlen(raiz->chave) && chave[indice] == raiz->chave[indice]): Enquanto os índices estiverem dentro dos limites das chaves e os caracteres forem iguais:
indice++: Incrementa o índice para comparar o próximo caractere.*/

    if (indice == strlen(raiz->chave)) {
        if (indice == strlen(chave)) {
            return raiz;
        } else {
            return buscar(chave + indice, raiz->direita);
        }
    } else {
        return NULL;
    }
}

/*if (indice == strlen(raiz->chave)): Se o índice for igual ao comprimento da chave do nó atual:
if (indice == strlen(chave)): Verifica se o índice também é igual ao comprimento da chave a ser buscada.
return raiz: Retorna o nó atual, pois a chave foi encontrada.
else: Caso contrário, chama recursivamente a função buscar para o filho direito.
else: Caso contrário, significa que há uma diferença na chave atual.
return NULL: Retorna NULL indicando que a chave não foi encontrada.*/

void remover(const char* chave, struct No** raiz) {
    if (*raiz == NULL) {
        return;
    }

/*void remover(const char* chave, struct No** raiz): Remove uma chave da árvore Patricia.
if (*raiz == NULL): Verifica se a raiz é NULL (ou seja, a árvore está vazia ou a chave não existe).
return: Retorna ao chamador.*/

    int indice = 0;
    while (indice < strlen(chave) && indice < strlen((*raiz)->chave) && chave[indice] == (*raiz)->chave[indice]) {
        indice++;
    }

/*int indice = 0: Variável para acompanhar o índice da comparação entre as chaves.
while (indice < strlen(chave) && indice < strlen((*raiz)->chave) && chave[indice] == (*raiz)->chave[indice]): Enquanto os índices estiverem dentro dos limites das chaves e os caracteres forem iguais:
indice++: Incrementa o índice para comparar o próximo caractere.*/

    if (indice == strlen((*raiz)->chave)) {
        if (indice == strlen(chave)) {
            if ((*raiz)->esquerda == NULL && (*raiz)->direita == NULL) {
                free(*raiz);
                *raiz = NULL;
            } else if ((*raiz)->esquerda != NULL) {
                struct No* max_esquerda = (*raiz)->esquerda;
                while (max_esquerda->direita != NULL) {
                    max_esquerda = max_esquerda->direita;
                }
                strcpy((*raiz)->chave, max_esquerda->chave);
                remover(max_esquerda->chave, &((*raiz)->esquerda));
            } else {
                struct No* temp = *raiz;
                *raiz = (*raiz)->direita;
                free(temp);
            }
        } else {
            remover(chave + indice, &((*raiz)->direita));
        }
    }
}

/*if (indice == strlen((*raiz)->chave)): Se o índice for igual ao comprimento da chave do nó atual:
if (indice == strlen(chave)): Verifica se o índice também é igual ao comprimento da chave a ser removida.
if ((*raiz)->esquerda == NULL && (*raiz)->direita == NULL): Se o nó atual não tiver filhos, ele pode ser removido diretamente.
free(*raiz): Libera a memória alocada para o nó atual.
*raiz = NULL: Define a raiz como NULL.
else if ((*raiz)->esquerda != NULL): Se o nó atual tiver um filho esquerdo:
struct No* max_esquerda = (*raiz)->esquerda: Encontra o nó com a chave máxima na subárvore esquerda.
while (max_esquerda->direita != NULL): Percorre os filhos direitos até encontrar o máximo.
max_esquerda = max_esquerda->direita: Atualiza o nó com a chave máxima.
strcpy((*raiz)->chave, max_esquerda->chave): Copia a chave máxima para o nó atual.
remover(max_esquerda->chave, &((*raiz)->esquerda)): Remove o nó com a chave máxima da subárvore esquerda.
else: Caso contrário, o nó atual tem apenas um filho direito:
struct No* temp = *raiz: Cria um nó temporário para armazenar o nó atual.
*raiz = (*raiz)->direita: Atualiza a raiz para o filho direito do nó atual.
free(temp): Libera a memória alocada para o nó atual.*/

void destruir_arvore(struct No* raiz) {
    if (raiz == NULL) {
        return;
    }

    destruir_arvore(raiz->esquerda);
    destruir_arvore(raiz->direita);
    free(raiz);
}

/*void destruir_arvore(struct No* raiz): Destroi a árvore Patricia liberando a memória alocada.
if (raiz == NULL): Se a raiz for NULL, significa que a árvore está vazia.
return: Retorna ao chamador.
destruir_arvore(raiz->esquerda): Chama recursivamente a função destruir_arvore para liberar a memória da subárvore esquerda.
destruir_arvore(raiz->direita): Chama recursivamente a função destruir_arvore para liberar a memória da subárvore direita.
free(raiz): Libera a memória alocada para o nó atual.*/

void imprimir_arvore(struct No* raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%s\n", raiz->chave);
    imprimir_arvore(raiz->esquerda);
    imprimir_arvore(raiz->direita);
}

/*void imprimir_arvore(struct No* raiz): Imprime a árvore Patricia.
if (raiz == NULL): Se a raiz for NULL, significa que a árvore está vazia.
return: Retorna ao chamador.
printf("%s\n", raiz->chave): Imprime a chave do nó atual.
imprimir_arvore(raiz->esquerda): Chama recursivamente a função imprimir_arvore para imprimir a subárvore esquerda.
imprimir_arvore(raiz->direita): Chama recursivamente a função imprimir_arvore para imprimir a subárvore direita.*/
