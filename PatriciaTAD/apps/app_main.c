#include <stdio.h>
#include <string.h>
#include "trie.h"

int main() {
    No* raiz = criarNo();

    // Inserindo palavras na árvore
    inserir(raiz, "plan");
    inserir(raiz, "play");
    inserir(raiz, "post");
    inserir(raiz, "poll");

    // Imprimindo a árvore Patricia
    printf("Arvore Patricia:\n");
    imprimirArvorePatricia(raiz);
    printf("\n");

    // Buscando palavras na árvore
    buscar(raiz, "plan");
    buscar(raiz, "play");
    buscar(raiz, "post");
    buscar(raiz, "poll");
    buscar(raiz, "test");

    // Removendo uma palavra da árvore
    remover(raiz, "play", 0, strlen("play"));

    // Imprimindo a árvore Patricia após a remoção
    printf("Arvore Patricia apos remocao:\n");
    imprimirArvorePatricia(raiz);
    printf("\n");

    // Buscando palavras na árvore novamente
    buscar(raiz, "plan");
    buscar(raiz, "play");
    buscar(raiz, "post");
    buscar(raiz, "poll");
    buscar(raiz, "test");

    // Liberando a memória da árvore
    liberarTrie(raiz);

    return 0;
}