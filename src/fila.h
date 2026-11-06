#ifndef FILA_H
#define FILA_H

#include "lista.h"

// Fila FIFO encadeada com ponteiros para início e fim 
typedef struct FilaEspera {
    NoEstudante *inicio;
    NoEstudante *fim;
} FilaEspera;

void fila_inicializar(FilaEspera *fila);
void fila_destruir(FilaEspera *fila);
int fila_enfileirar(FilaEspera *fila, int matricula, const char *nome, int *posicao_out);
int fila_desenfileirar(FilaEspera *fila, int *matricula_out, char *nome_out);
int fila_remover_por_matricula(FilaEspera *fila, int matricula);
NoEstudante* fila_buscar_matricula(const FilaEspera *fila, int matricula);

#endif 