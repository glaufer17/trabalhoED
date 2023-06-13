#ifndef TRIE_H
#define TRIE_H

#define ALFABETO_SIZE 26

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

No* criarNo();
void inserir(No* raiz, const char* chave);
int buscar(No* raiz, const char* chave);
int temFilhos(No* no);
int remover(No* no, const char* chave, int nivel, int comprimento);
void imprimirArvorePatricia(No* raiz);
void imprimirTrie(No* no, char* prefixo, int nivel);
void liberarTrie(No* no);

#endif  // TRIE_H