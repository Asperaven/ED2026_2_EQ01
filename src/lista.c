#include "lista.h"
#include <stdlib.h>
#include <string.h> // Necessário para strncpy, perguntar ao professor se é considerada uma "biblioteca externa"


// Inicializa a lista vazia
void lista_inicializar(ListaInscritos *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
}

// Libera todos os nós alocados na lista, um por um
void lista_destruir(ListaInscritos *lista) {
  NoEstudante *atual = lista->inicio;
  while (atual != NULL) {
    NoEstudante *prox = atual->prox;
    free(atual);
    atual = prox;
  }
  lista->inicio = NULL;
  lista->fim = NULL;
}

// Insere um estudante no fim da lista. Complexidade esperada: O(1) devido ao uso do ponteiro 'fim' (Seção 9).
int lista_inserir_fim(ListaInscritos *lista, int matricula, const char *nome) {
  NoEstudante *novo = (NoEstudante *)malloc(sizeof(NoEstudante));
  if (novo == NULL)
    return 0; // Falha na alocação de memória

  novo->matricula = matricula;
  strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
  novo->nome[sizeof(novo->nome) - 1] = '\0';
  novo->prox = NULL;

  if (lista->inicio == NULL) {
    // Lista estava vazia, o novo nó é o primeiro e o último
    lista->inicio = novo;
    lista->fim = novo;
  } else {
    // Adiciona no fim e atualiza o ponteiro 'fim'
    lista->fim->prox = novo;
    lista->fim = novo;
  }
  return 1;
}

// Remove um aluno da lista através da matrícula (início, meio ou fim). O ponteiro fim não pode apontar para memória liberada (Seção 4.2).
int lista_remover_por_matricula(ListaInscritos *lista, int matricula) {
  NoEstudante *atual = lista->inicio;
  NoEstudante *anterior = NULL;

  while (atual != NULL) {
    if (atual->matricula == matricula) {
      if (anterior == NULL) {
        // Remoção do início
        lista->inicio = atual->prox;
      } else {
        // Remoção no meio ou no fim
        anterior->prox = atual->prox;
      }

      // Se o elemento removido era o último, atualiza o ponteiro 'fim'
      if (atual == lista->fim) {
        lista->fim = anterior;
      }

      free(atual);
      return 1; // Retorno com sucesso
    }
    anterior = atual;
    atual = atual->prox;
  }
  return 0; // Matrícula não encontrada
}

// Busca sequencialmente um estudante por matrícula
NoEstudante *lista_buscar_matricula(const ListaInscritos *lista,
                                    int matricula) {
  NoEstudante *atual = lista->inicio;
  while (atual != NULL) {
    if (atual->matricula == matricula) {
      return atual;
    }
    atual = atual->prox;
  }
  return NULL;
}