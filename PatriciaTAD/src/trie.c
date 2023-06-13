#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALFABETO_SIZE 46

typedef struct No {
    int ehFimDePalavra;
    char caractere;
    union {
        struct {
            struct No* filho;
            struct No* irmao;
        } patricia;
        struct No* filho[ALFABETO_SIZE];
    };
} No;

No* criarNo() {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->ehFimDePalavra = 0;
    for (int i = 0; i < ALFABETO_SIZE; i++) {
        novoNo->filho[i] = NULL;
    }
    return novoNo;
}

void inserir(No* raiz, const char* chave) {
    int comprimento = strlen(chave);
    No* noAtual = raiz;

    for (int nivel = 0; nivel < comprimento; nivel++) {
        int indice = chave[nivel] - 'a';

        if (noAtual->filho[indice] == NULL) {
            noAtual->filho[indice] = criarNo();
        }

        noAtual = noAtual->filho[indice];
    }

    noAtual->ehFimDePalavra = 1;
}

void buscar(No* raiz, const char* chave) {
    int comprimento = strlen(chave);
    No* noAtual = raiz;

    for (int nivel = 0; nivel < comprimento; nivel++) {
        int indice = chave[nivel] - 'a';
        int encontrado = 0;

        for (int i = 0; i < ALFABETO_SIZE; i++) {
            if (noAtual->filho[i] != NULL && noAtual->filho[i]->caractere == indice + 'a') {
                noAtual = noAtual->filho[i];
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("A palavra '%s' nao esta na arvore.\n", chave);
            return;
        }
    }

    if (noAtual != NULL && noAtual->ehFimDePalavra) {
        printf("A palavra '%s' está na arvore.\n", chave);
    } else {
        printf("A palavra '%s' nao esta na arvore.\n", chave);
    }
}

int temFilhos(No* no) {
    for (int i = 0; i < ALFABETO_SIZE; i++) {
        if (no->filho[i] != NULL) {
            return 1;
        }
    }
    return 0;
}

int remover(No* no, const char* chave, int nivel, int comprimento) {
    if (no == NULL) {
        return 0;
    }

    if (nivel == comprimento) {
        if (no->ehFimDePalavra) {
            no->ehFimDePalavra = 0;
            if (!temFilhos(no)) {
                return 1;
            }
            return 0;
        }
    } else {
        int indice = chave[nivel] - 'a';

        if (no->filho[indice] == NULL) {
            return 0;
        }

        if (remover(no->filho[indice], chave, nivel + 1, comprimento)) {
            free(no->filho[indice]);
            no->filho[indice] = NULL;
            return (!temFilhos(no) && !no->ehFimDePalavra);
        }
    }

    return 0;
}

void imprimirTrie(No* no, char* prefixo, int nivel) {
    if (no == NULL) {
        return;
    }

    if (no->ehFimDePalavra) {
        for (int i = 0; i < nivel; i++) {
            printf("  ");
        }
        printf("%s\n", prefixo);
    }

    for (int i = 0; i < ALFABETO_SIZE; i++) {
        if (no->filho[i] != NULL) {
            prefixo[nivel] = 'a' + i;
            prefixo[nivel + 1] = '\0';
            imprimirTrie(no->filho[i], prefixo, nivel + 1);
        }
    }
}

void imprimirArvorePatricia(No* raiz) {
    char prefixo[ALFABETO_SIZE + 1];
    prefixo[0] = '\0';

    imprimirTrie(raiz, prefixo, 0);
}

void liberarTrie(No* no) {
    if (no == NULL) {
        return;
    }

    for (int i = 0; i < ALFABETO_SIZE; i++) {
        liberarTrie(no->filho[i]);
    }

    free(no);
}