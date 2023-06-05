#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int bit;
    struct No* esq;
    struct No* dir;
} Interno;

typedef struct {
    char chave[50];
    int indice;
} Folha;

typedef union {
    Interno interno;
    Folha folha;
} Dados;

typedef struct No No;

No* criarFolha(char* chave, int indice);

No* criarInterno(int bit, No* esq, No* dir);

int encontrarBitDiferente(char* chave1, char* chave2);

No* inserir(No* raiz, char* chave, int indice);

int buscar(No* raiz, char* chave);