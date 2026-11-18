#include <stdio.h>
#include <stdlib.h>
#include "historico.h"

// Inicializa o histórico global definindo ponteiros nulos e zerando o contador
void historico_inicializar(Historico *h) {
    if (h != NULL) {
        h->inicio = NULL;
        h->fim = NULL;
        h->qtdEventos = 0;
    }
}

// Libera a memória de todos os nós de eventos registrados
void historico_destruir(Historico *h) {
    if (h != NULL) {
        NoEvento *atual = h->inicio;
        while (atual != NULL) {
            NoEvento *prox = atual->prox;
            free(atual);
            atual = prox;
        }
        h->inicio = NULL;
        h->fim = NULL;
        h->qtdEventos = 0;
    }
}

// Processa o enum TipoEvento e retorna a string correspondente
const char* historico_tipo_para_string(TipoEvento tipo) {
    switch (tipo) {
        case EV_CADASTRO: return "CADASTRO";
        case EV_INSCRICAO: return "INSCRICAO";
        case EV_ENTRADA_ESPERA: return "ENTRADA_ESPERA";
        case EV_CANCEL_INSCRICAO: return "CANCEL_INSCRICAO";
        case EV_CANCEL_ESPERA: return "CANCEL_ESPERA";
        case EV_PROMOCAO: return "PROMOCAO";
        case EV_AUMENTO_CAPACIDADE: return "AUMENTO_CAPACIDADE";
        default: return "TIPO_DESCONHECIDO";
    }
}

int historico_registrar(Historico *h, TipoEvento tipo, int codigo, int matricula) {
    if (h == NULL) {
        return 0; // Falha: erro na inicialização do histórico
    }

    NoEvento *novoEvento = (NoEvento*)malloc(sizeof(NoEvento));
    if (novoEvento == NULL) {
        return 0; // Falha: erro na alocação de memória para onó de evento
    }

    h->qtdEventos++;
    novoEvento->seq = h->qtdEventos;
    novoEvento->tipo = tipo;
    novoEvento->codigo = codigo;
    novoEvento->matricula = matricula;
    novoEvento->prox = NULL;

    if (h->inicio == NULL) {
        h->inicio = novoEvento;
        h->fim = novoEvento;
    } else {
        h->fim->prox = novoEvento;
        h->fim = novoEvento;
    }
    return 1; // Sucesso evento registrado
}

void historico_imprimir(const Historico *h) {
    if (h == NULL) {
        return; // Falha: histórico não inicializado
    }

    NoEvento *atual = h->inicio;
    while (atual != NULL) {
        printf("%d %s %d %d\n", atual->seq, historico_tipo_para_string(atual->tipo), atual->codigo, atual->matricula);
        atual = atual->prox;
    }
    printf("\n");
}