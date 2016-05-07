#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define TAM_ITEM 4
#define MB 1000 * 1000

typedef struct nodo { //no da pilha
    int32_t valor;
    int32_t index;
}nodo;
typedef struct Pilha{
    int32_t tamanho;
    nodo *heap;
}Pilha;
typedef struct executar {
    size_t tamanho;
} executar;
typedef struct KFile {
    int32_t id;
    char *nome;
    FILE *fp;
    executar linhaAtual;
    unsigned long tamAtual;
} KFile;

void trocaAnterior(nodo *heap, int32_t tamanho, int32_t idx);
void inserir (nodo a_node, nodo *heap, int32_t tamanho);
void iniciarPilhar(Pilha *q, int32_t n);
nodo remover (nodo *heap, int32_t tamanho);
void pilhaDinamica(nodo node, Pilha *q);
KFile* geraArquivos (const int32_t K);
KFile* geraLinhas (FILE *fp, const int32_t MEMORIADISPONIVEL, const int32_t K);
unsigned long getTamArquivo (FILE* fp);
nodo desempilhar(Pilha *q);
int32_t interpola(KFile *arquivos, unsigned long arquivoEntradaTAM, const unsigned long MEMORIADISPONIVEL, const int32_t K);
int32_t comparaFuncao (const void * a, const void * b);
int32_t getNumLinhas (unsigned long arquivoTAM, const int32_t MEMORIADISPONIVEL);
int32_t getLog (double base, double x);