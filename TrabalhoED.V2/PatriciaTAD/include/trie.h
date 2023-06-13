#ifndef TRIE_H
#define TRIE_H

typedef struct No {
    struct No* filho[ALFABETO_SIZE];
    int ehFimDePalavra;
} No;

No* criarNo();
void inserir(No* raiz, const char* chave);
int buscar(No* raiz, const char* chave);
int temFilhos(No* no);
int remover(No* no, const char* chave, int nivel, int comprimento);
void imprimirTrie(No* no, char* palavra, int nivel);
void liberarTrie(No* no);

#endif  // TRIE_H