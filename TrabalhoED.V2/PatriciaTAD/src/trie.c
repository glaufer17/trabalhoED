#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

#define ALFABETO_SIZE 26

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

int buscar(No* raiz, const char* chave) {
    int comprimento = strlen(chave);
    No* noAtual = raiz;

    for (int nivel = 0; nivel < comprimento; nivel++) {
        int indice = chave[nivel] - 'a';
        if (noAtual->filho[indice] == NULL) {
            return 0;
        }
        noAtual = noAtual->filho[indice];
    }

    return (noAtual != NULL && noAtual->ehFimDePalavra);
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
        if (remover(no->filho[indice], chave, nivel + 1, comprimento)) {
            free(no->filho[indice]);
            no->filho[indice] = NULL;
            return (!temFilhos(no) && !no->ehFimDePalavra);
        }
    }
    return 0;
}

void imprimirTrie(No* no, char* palavra, int nivel) {
    if (no->ehFimDePalavra) {
        palavra[nivel] = '\0';
        printf("%s\n", palavra);
    }

    for (int i = 0; i < ALFABETO_SIZE; i++) {
        if (no->filho[i] != NULL) {
            palavra[nivel] = i + 'a';
            imprimirTrie(no->filho[i], palavra, nivel + 1);
        }
    }
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
