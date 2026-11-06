#ifndef ATIVIDADE_H
#define ATIVIDADE_H

#include "lista.h"
#include "fila.h"

typedef struct Atividade {
    int codigo;             // Código único inteiro positivo 
    char titulo[100];       // Título sem espaços
    int capacidade;         // Capacidade total atual 
    int qtdInscritos;       // Quantidade atual de inscritos confirmados 
    int qtdEspera;          // Quantidade atual de alunos na fila de espera 
    
    ListaInscritos inscritos; // Lista encadeada de alunos inscritos 
    FilaEspera espera;       // Fila encadeada FIFO de alunos aguardando vaga 
} Atividade;

Atividade* atividade_criar(int codigo, int capacidade, const char *titulo);

void atividade_destruir(Atividade *act);

int atividade_buscar_aluno(const Atividade *act, int matricula);

#endif 