#ifndef ABB_H
#define ABB_H

#include "atividade.h"

// Nó da Árvore Binária de Busca
typedef struct NoABB {
    Atividade *atividade;
    struct NoABB *esq;
    struct NoABB *dir;
} NoABB;

// Estrutura da Árvore Binária de Busca
typedef struct ArvoreABB {
    NoABB *raiz;
} ArvoreABB;

// Inicialização da Árvore Binária de Busca
void abb_inicializar(ArvoreABB *arvore);

// Destruição da Árvore Binária de Busca
void abb_destruir(ArvoreABB *arvore);

// Insere uma atividade na Árvore Binária de Busca
int abb_inserir(ArvoreABB *arvore, Atividade *act);

// Busca uma atividade na Árvore Binária de Busca
Atividade* abb_buscar(const ArvoreABB *arvore, int codigo);

// Lista as atividades em ordem
void abb_listar_em_ordem(const ArvoreABB *arvore);

// Retorna a quantidade de nós (atividades) na Árvore
int abb_contar_nos(const ArvoreABB *arvore);

// Retorna a altura da Árvore
int abb_calcular_altura(const ArvoreABB *arvore);

#endif 