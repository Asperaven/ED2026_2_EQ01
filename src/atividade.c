#include <stdlib.h>
#include <string.h> // Necessário para strncpy, perguntar ao professor se é considerada uma "biblioteca externa".
#include "atividade.h"

// Cria e aloca dinamicamente uma nova estrutura Atividade.
// Conforme a Seção 5.1, inicializa a lista de inscritos e a fila de espera vazias.
Atividade* atividade_criar(int codigo, int capacidade, const char *titulo) {
    Atividade *nova_act = (Atividade*) malloc(sizeof(Atividade));
    if (nova_act == NULL) {
        return NULL; // Check de falha de alocação de memória
    }

    nova_act->codigo = codigo;
    nova_act->capacidade = capacidade;
    nova_act->qtdInscritos = 0;
    nova_act->qtdEspera = 0;

    // Copia o título garantindo que não exceda o limite do buffer e termine com '\0'
    strncpy(nova_act->titulo, titulo, sizeof(nova_act->titulo) - 1);
    nova_act->titulo[sizeof(nova_act->titulo) - 1] = '\0';

    // Inicializa as estruturas de dados dependentes 
    lista_inicializar(&nova_act->inscritos);
    fila_inicializar(&nova_act->espera);

    return nova_act;
}

// Libera toda a memória associada à atividade.
void atividade_destruir(Atividade *act) {
    if (act != NULL) {
        // Libera todos os nós da lista e da fila um por um antes de liberar a struct
        lista_destruir(&act->inscritos);
        fila_destruir(&act->espera);
        free(act);
    }
}

// Verifica se a matrícula já aparece na lista ou na fila.
// Retorna 1 se encontrar a matrícula, 0 caso contrário.
// Isso atende à regra da Seção 3.2, onde uma matrícula não pode repetir na mesma atividade. 
int atividade_buscar_aluno(const Atividade *act, int matricula) {
    if (act == NULL) return 0;

    // Busca na lista de inscritos
    if (lista_buscar_matricula(&act->inscritos, matricula) != NULL) {
        return 1;
    }

    // Busca na fila de espera 
    if (fila_buscar_matricula(&act->espera, matricula) != NULL) {
        return 1;
    }

    return 0;
}