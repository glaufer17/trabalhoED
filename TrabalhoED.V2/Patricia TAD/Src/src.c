#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include.h"

struct No {
    int ehFolha;
    Dados dados;
}

No* criarFolha(char* chave, int indice) {
    No* folha = (No*)malloc(sizeof(No));
    folha->ehFolha = 1;
    strcpy(folha->dados.folha.chave, chave);
    folha->dados.folha.indice = indice;
    return folha;
}

No* criarInterno(int bit, No* esq, No* dir) {
    No* interno = (No*)malloc(sizeof(No));
    interno->ehFolha = 0;
    interno->dados.interno.bit = bit;
    interno->dados.interno.esq = esq;
    interno->dados.interno.dir = dir;
    return interno;
}

int encontrarBitDiferente(char* chave1, char* chave2) {
    int i = 0;
    while (chave1[i] == chave2[i]) {
        i++;
    }
    return i;
}

No* inserir(No* raiz, char* chave, int indice) {
    if (raiz == NULL) {
        return criarFolha(chave, indice);
    }

    if (raiz->ehFolha) {
        int bitDiferente = encontrarBitDiferente(chave, raiz->dados.folha.chave);
        if (bitDiferente == 0 && strcmp(chave, raiz->dados.folha.chave) == 0) {
            return raiz; // chave já existe na árvore
        }

        int i = 0;
        while (chave[i] == raiz->dados.folha.chave[i]) {
            i++;
        }

        if (i == strlen(raiz->dados.folha.chave)) {
            if (chave[i] == '\0') {
                return raiz; // chave já existe na árvore
            } else {
                No* noInterno = criarInterno(i, NULL, NULL);
                noInterno->dados.interno.esq = raiz;
                noInterno->dados.interno.dir = criarFolha(chave, indice);
                return noInterno;
            }
        } else {
            No* noInterno = criarInterno(i, NULL, NULL);
            No* noFolha1 = criarFolha(raiz->dados.folha.chave + i, raiz->dados.folha.indice);
            No* noFolha2 = criarFolha(chave + i, indice);

            if (chave[i] == '\0') {
                noInterno->dados.interno.esq = noFolha2;
                noInterno->dados.interno.dir = noFolha1;
            } else {
                noInterno->dados.interno.esq = noFolha1;
                noInterno->dados.interno.dir = noFolha2;
            }

            raiz->dados.folha.chave[i] = '\0';
            raiz->dados.folha.indice = -1;
            raiz->ehFolha = 0;
            raiz->dados.interno.bit = i;
            raiz->dados.interno.esq = noInterno;
            raiz->dados.interno.dir = NULL;

            return raiz;
        }
    }

    int bitDiferente = encontrarBitDiferente(chave, raiz->dados.interno.esq->dados.folha.chave);
    if (bitDiferente == strlen(raiz->dados.interno.esq->dados.folha.chave)) {
        raiz->dados.interno.esq = inserir(raiz->dados.interno.esq, chave, indice);
    } else {
        No* noInterno = criarInterno(bitDiferente, NULL, NULL);
        noInterno->dados.interno.esq = raiz->dados.interno.esq;
        raiz->dados.interno.esq = noInterno;
        raiz->dados.interno.dir = criarFolha(chave, indice);
        raiz->dados.interno.bit = bitDiferente;
        raiz->ehFolha = 0;
    }

    return raiz;
}

int buscar(No* raiz, char* chave) {
    if (raiz == NULL) {
        return -1;
    }

    if (raiz->ehFolha) {
        if (strcmp(chave, raiz->dados.folha.chave) == 0) {
            return raiz->dados.folha.indice;
        }
    } else {
        int bitDiferente = encontrarBitDiferente(chave, raiz->dados.interno.esq->dados.folha.chave);
        if (bitDiferente == strlen(raiz->dados.interno.esq->dados.folha.chave)) {
            return buscar(raiz->dados.interno.esq, chave);
        }
    }

    return buscar(raiz->dados.interno.dir, chave);
}

void imprimirArvoreRecursivo(No* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    if (raiz->ehFolha) {
        for (int i = 0; i < nivel; i++) {
            printf("\t");
        }
        printf("%s (Índice: %d)\n", raiz->dados.folha.chave, raiz->dados.folha.indice);
        return;
    }

    imprimirArvoreRecursivo(raiz->dados.interno.esq, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("\t");
    }
    printf("Bit %d\n", raiz->dados.interno.bit);

    imprimirArvoreRecursivo(raiz->dados.interno.dir, nivel + 1);
}

void imprimirArvore(No* raiz) {
    printf("Árvore Patricia:\n");
    imprimirArvoreRecursivo(raiz, 0);
}

void liberar(No* raiz) {
    if (raiz == NULL)
        return;

    if (raiz->ehFolha) {
        free(raiz->dados.folha.chave);
        free(raiz);
    } else {
        liberar(raiz->dados.interno.esq);
        liberar(raiz->dados.interno.dir);
        free(raiz);
    }
}

void liberarNo(No* no) {
    if (no == NULL)
        return;

    if (no->ehFolha) {
        free(no->dados.folha.chave);
    } else {
        liberarNo(no->dados.interno.esq);
        liberarNo(no->dados.interno.dir);
    }

    free(no);
}

void remover(No** raiz, char* chave) {
    if (*raiz == NULL)
        return;

    if ((*raiz)->ehFolha) {
        if (strcmp(chave, (*raiz)->dados.folha.chave) == 0) {
            free((*raiz)->dados.folha.chave);
            free(*raiz);
            *raiz = NULL;
        }
    } else {
        int bitDiferente = encontrarBitDiferente(chave, (*raiz)->dados.interno.esq->dados.folha.chave);

        if (bitDiferente == strlen((*raiz)->dados.interno.esq->dados.folha.chave)) {
            remover(&((*raiz)->dados.interno.esq), chave);
        } else {
            return;
        }

        // Verifica se o caminho possui apenas um filho que é outra palavra
        if ((*raiz)->dados.interno.esq == NULL && (*raiz)->dados.interno.dir != NULL && (*raiz)->dados.interno.dir->ehFolha) {
            No* noRemover = *raiz;
            *raiz = (*raiz)->dados.interno.dir;
            free(noRemover->dados.interno.esq);
            free(noRemover);
        }
    }

    // Desaloca a memória da árvore se não houver mais nós
    if (*raiz == NULL)
        return;

    // Verifica se o caminho possui apenas um filho que é outra palavra
    if ((*raiz)->ehFolha)
        return;

    // Verifica se a raiz é um nó interno sem filhos
    if ((*raiz)->dados.interno.esq == NULL && (*raiz)->dados.interno.dir == NULL) {
        free(*raiz);
        *raiz = NULL;
    }
}
