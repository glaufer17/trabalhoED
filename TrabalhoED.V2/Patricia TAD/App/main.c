#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    No* raiz = NULL;

    raiz = inserir(raiz, "amor", 1);
    raiz = inserir(raiz, "amora", 2);
    raiz = inserir(raiz, "amado", 3);
    raiz = inserir(raiz, "adorar", 4);
    raiz = inserir(raiz, "dado", 5);
    raiz = inserir(raiz, "casa", 6);



    imprimirArvore(raiz);
    remover(&raiz, "casa");
    printf("\n");

    int indice = buscar(raiz, "amora");
    if (indice != -1) {
        printf("Chave encontrada no índice: %d\n", indice);
    } else {
        printf("Chave não encontrada.\n");
    }
    imprimirArvore(raiz);

    liberar(raiz);

    imprimirArvore(raiz);

    return 0;
}