#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAVE 50

struct No {
    char chave[MAX_CHAVE];
    struct No* esquerda;
    struct No* direita;
};

// Cria um novo nó com a chave especificada
struct No* criarNo(const char* chave) {
    struct No* novo_no = (struct No*)malloc(sizeof(struct No));
    strcpy(novo_no->chave, chave);
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

// Insere uma chave na árvore Patricia
void inserir(const char* chave, struct No** raiz) {
    if (*raiz == NULL) {
        *raiz = criarNo(chave);
        return;
    }

    int indice = 0;
    while (indice < strlen(chave) && indice < strlen((*raiz)->chave) && chave[indice] == (*raiz)->chave[indice]) {
        indice++;
    }

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

// Busca por uma chave na árvore Patricia
struct No* buscar(const char* chave, struct No* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    int indice = 0;
    while (indice < strlen(chave) && indice < strlen(raiz->chave) && chave[indice] == raiz->chave[indice]) {
        indice++;
    }

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

// Remove uma chave da árvore Patricia
void remover(const char* chave, struct No** raiz) {
    if (*raiz == NULL) {
        return;
    }

    int indice = 0;
    while (indice < strlen(chave) && indice < strlen((*raiz)->chave) && chave[indice] == (*raiz)->chave[indice]) {
        indice++;
    }

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

// Destroi a árvore Patricia liberando a memória alocada
void destruir_arvore(struct No* raiz) {
    if (raiz == NULL) {
        return;
    }

    destruir_arvore(raiz->esquerda);
    destruir_arvore(raiz->direita);
    free(raiz);
}

// Imprime a árvore Patricia
void imprimir_arvore(struct No* raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%s\n", raiz->chave);
    imprimir_arvore(raiz->esquerda);
    imprimir_arvore(raiz->direita);
}

int main() {
    struct No* raiz = NULL;

    inserir("casa", &raiz);
    inserir("carro", &raiz);
    inserir("cadeira", &raiz);
    inserir("caneta", &raiz);

    printf("Árvore Patricia:\n");
    imprimir_arvore(raiz);

    struct No* no_encontrado = buscar("carro", raiz);
    if (no_encontrado != NULL) {
        printf("Carro encontrado!\n");
    } else {
        printf("Carro não encontrado!\n");
    }

    remover("carro", &raiz);

    printf("Árvore Patricia após remover 'carro':\n");
    imprimir_arvore(raiz);

    destruir_arvore(raiz);

    return 0;
}
