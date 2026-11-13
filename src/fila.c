#include <stdlib.h>
#include <string.h> // Necessário para strncpy, perguntar ao professor se é considerada uma biblioteca externa.
#include "fila.h"

// Inicializa a fila vazia.
void fila_inicializar(FilaEspera *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Libera todos os nós alocados na fila, um por um.
void fila_destruir(FilaEspera *fila) {
    NoEstudante *atual = fila->inicio;
    while (atual != NULL) {
        NoEstudante *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Enfileira um estudante (insere no fim). O parâmetro posicao_out armazena a posição em que o aluno entrou.
int fila_enfileirar(FilaEspera *fila, int matricula, const char *nome, int *posicao_out) {
    NoEstudante *novo = (NoEstudante*) malloc(sizeof(NoEstudante));
    if (novo == NULL) return 0; // Falha de alocação de memória.

    novo->matricula = matricula;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->prox = NULL;

    int pos = 1;
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        // Conta os elementos existentes apenas para definir a posição (posicao_out)
        NoEstudante *temp = fila->inicio;
        while (temp != NULL) {
            pos++;
            temp = temp->prox;
        }
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    
    if (posicao_out != NULL) {
        *posicao_out = pos;
    }
    return 1;
}

// Desenfileira o primeiro estudante (para promoção). Complexidade esperada: O(1) (Seção 9).
int fila_desenfileirar(FilaEspera *fila, int *matricula_out, char *nome_out) {
    if (fila->inicio == NULL) return 0; // Fila vazia, não é possível remover.

    NoEstudante *removido = fila->inicio;
    
    if (matricula_out != NULL) *matricula_out = removido->matricula;
    if (nome_out != NULL) strcpy(nome_out, removido->nome);

    fila->inicio = removido->prox;
    
    // Se a fila esvazia após a remoção, zera o ponteiro 'fim' também.
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(removido);
    return 1;
}

// Remove da fila por matrícula em qualquer posição (cancelamento de espera), preserva a ordem FIFO (Seção 4.3)
int fila_remover_por_matricula(FilaEspera *fila, int matricula) {
    NoEstudante *atual = fila->inicio;
    NoEstudante *anterior = NULL;

    while (atual != NULL) {
        if (atual->matricula == matricula) {
            if (anterior == NULL) {
                fila->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            if (atual == fila->fim) {
                fila->fim = anterior;
            }

            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

// Busca sequencialmente um estudante na fila por matrícula
NoEstudante* fila_buscar_matricula(const FilaEspera *fila, int matricula) {
    NoEstudante *atual = fila->inicio;
    while (atual != NULL) {
        if (atual->matricula == matricula) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}