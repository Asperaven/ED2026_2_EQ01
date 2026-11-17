#include "abb.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializa Árvore Binária de Busca com raiz nula
void abb_inicializar(ArvoreABB *arvore) {
  if (arvore != NULL) {
    arvore->raiz = NULL;
  }
}

// Função auxiliar recursiva para destruir todos os nós da Árvore em pos-ordem
static void destruir_nos_rec(NoABB *no) {
  if (no == NULL)
    return;

  destruir_nos_rec(no->esq);
  destruir_nos_rec(no->dir);

  // Libera a atividade contida no nó e depois o nó em si
  atividade_destruir(no->atividade);
  free(no);
}

// Destrói a ABB inteira liberando todos os nós e atividades
void abb_destruir(ArvoreABB *arvore) {
  if (arvore != NULL) {
    destruir_nos_rec(arvore->raiz);
    arvore->raiz = NULL;
  }
}

// Auxiliar recursivo de inserção por código
static int inserir_rec(NoABB **no, Atividade *act) {
  if (*no == NULL) {
    NoABB *novo = (NoABB *)malloc(sizeof(NoABB));
    if (novo == NULL)
      return 0;

    novo->atividade = act;
    novo->esq = NULL;
    novo->dir = NULL;
    *no = novo;
    return 1;
  }

  if (act->codigo < (*no)->atividade->codigo) {
    return inserir_rec(&(*no)->esq, act);
  } else if (act->codigo > (*no)->atividade->codigo) {
    return inserir_rec(&(*no)->dir, act);
  } else {
    // Código duplicado rejeitado (Seção 4.1 e 5.1)
    return 0;
  }
}

// Insere uma nova atividade na ABB
int abb_inserir(ArvoreABB *arvore, Atividade *act) {
  if (arvore == NULL || act == NULL)
    return 0;
  return inserir_rec(&arvore->raiz, act);
}

// Auxiliar recursivo de busca por código
static Atividade *buscar_rec(const NoABB *no, int codigo) {
  if (no == NULL)
    return NULL;

  if (codigo == no->atividade->codigo) {
    return no->atividade;
  } else if (codigo < no->atividade->codigo) {
    return buscar_rec(no->esq, codigo);
  } else {
    return buscar_rec(no->dir, codigo);
  }
}

// Busca uma atividade pelo código único
Atividade *abb_buscar(const ArvoreABB *arvore, int codigo) {
  if (arvore == NULL)
    return NULL;
  return buscar_rec(arvore->raiz, codigo);
}

// Auxiliar recursivo para percurso em ordem
static void listar_em_ordem_rec(const NoABB *no) {
  if (no == NULL)
    return;

  listar_em_ordem_rec(no->esq);

  // Imprime no formato exato exigido pelo comando LISTAR (Seção 6.4)
  printf("ATIVIDADE %d %s %d %d %d\n", no->atividade->codigo,
         no->atividade->titulo, no->atividade->capacidade,
         no->atividade->qtdInscritos, no->atividade->qtdEspera);

  listar_em_ordem_rec(no->dir);
}

// Realiza o percurso em ordem na ABB (código crescente)
void abb_listar_em_ordem(const ArvoreABB *arvore) {
  if (arvore != NULL) {
    listar_em_ordem_rec(arvore->raiz);
  }
}

// Auxiliar recursivo de contagem de nós
static int contar_nos_rec(const NoABB *no) {
  if (no == NULL)
    return 0;
  return 1 + contar_nos_rec(no->esq) + contar_nos_rec(no->dir);
}

// Retorna a quantidade total de nós (atividades) na árvore
int abb_contar_nos(const ArvoreABB *arvore) {
  if (arvore == NULL)
    return 0;
  return contar_nos_rec(arvore->raiz);
}

// Auxiliar recursivo para cálculo da altura
static int calcular_altura_rec(const NoABB *no) {
  if (no == NULL)
    return -1;

  int alt_esq = calcular_altura_rec(no->esq);
  int alt_dir = calcular_altura_rec(no->dir);

  return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

// Retorna a altura da ABB (-1 para vazia, 0 para apenas a raiz)
int abb_calcular_altura(const ArvoreABB *arvore) {
  if (arvore == NULL)
    return -1;
  return calcular_altura_rec(arvore->raiz);
}