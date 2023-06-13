#include <stdio.h>
#include <string.h>
#include "include/trie.h"

void exibirMenu() {
    printf("=== Menu ===\n");
    printf("1. Inserir palavra\n");
    printf("2. Buscar palavra\n");
    printf("3. Remover palavra\n");
    printf("4. Imprimir árvore\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    No* raiz = criarNo();
    int opcao = 0;

    while (opcao != 5) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char palavra[100];
                printf("Digite a palavra: ");
                scanf("%s", palavra);
                inserir(raiz, palavra);
                printf("Palavra inserida!\n");
                break;
            }
            case 2: {
                char palavra[100];
                printf("Digite a palavra a ser buscada: ");
                scanf("%s", palavra);
                if (buscar(raiz, palavra)) {
                    printf("A palavra esta presente na arvore.\n");
                } else {
                    printf("A palavra nao esta presente na arvore.\n");
                }
                break;
            }
            case 3: {
                char palavra[100];
                printf("Digite a palavra a ser removida: ");
                scanf("%s", palavra);
                if (remover(raiz, palavra, 0, strlen(palavra))) {
                    printf("Palavra removida!\n");
                } else {
                    printf("A palavra nao esta presente na arvore.\n");
                }
                break;
            }
            case 4: {
                printf("=== Arvore Patricia Trie ===\n");
                char palavra[100];
                imprimirTrie(raiz, palavra, 0);
                break;
            }
            case 5: {
                liberarTrie(raiz);
                printf("Programa encerrado.\n");
                break;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
                break;
            }
        }

        printf("\n");
    }

    return 0;
}
