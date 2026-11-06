#ifndef LISTA_H
#define LISTA_H

// Nó de estudante compartilhado por listas e filas, já que filas são um subtipo de listas.
typedef struct NoEstudante {
    int matricula;             // Matrícula do aluno 
    char nome[100];            // Nome sem espaços 
    struct NoEstudante *prox;  // Ponteiro para o próximo nó 
} NoEstudante;

// Lista encadeada de inscritos com ponteiro para início e fim 
typedef struct ListaInscritos {
    NoEstudante *inicio;
    NoEstudante *fim;
} ListaInscritos;

void lista_inicializar(ListaInscritos *lista);
void lista_destruir(ListaInscritos *lista);
int lista_inserir_fim(ListaInscritos *lista, int matricula, const char *nome);
int lista_remover_por_matricula(ListaInscritos *lista, int matricula);
NoEstudante* lista_buscar_matricula(const ListaInscritos *lista, int matricula);

#endif 