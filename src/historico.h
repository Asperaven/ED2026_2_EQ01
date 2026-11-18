#ifndef HISTORICO_H
#define HISTORICO_H

// Tipos de eventos reconhecidos pelo sistema. Atende à lista obrigatória da Seção 4.4.
typedef enum {
    EV_CADASTRO,
    EV_INSCRICAO,
    EV_ENTRADA_ESPERA,
    EV_CANCEL_INSCRICAO,
    EV_CANCEL_ESPERA,
    EV_PROMOCAO,
    EV_AUMENTO_CAPACIDADE
} TipoEvento;

// Nó do histórico contendo cópias dos valores de um evento. NUNCA armazena ponteiros para nós externos de estudantes ou atividades.

typedef struct NoEvento {
    int seq;                // Número sequencial iniciando em 1
    TipoEvento tipo;        // Tipo do evento registrado
    int codigo;             // Código da atividade (a)
    int matricula;          // Matrícula do aluno (m), ou 0 quando N/A
    struct NoEvento *prox;  // Ponteiro para o próximo evento no tempo
} NoEvento;

// Estrutura gerenciadora da lista encadeada de histórico global.
typedef struct Historico {
    NoEvento *inicio;
    NoEvento *fim;
    int qtdEventos;         // Contador total de eventos registrados 
} Historico;

// Inicializa o histórico global definindo ponteiros como NULL e contador em 0.
void historico_inicializar(Historico *h);

// Libera toda a memória alocada pelos nós de evento do histórico.
void historico_destruir(Historico *h);

// Registra um novo evento no fim da lista encadeada. A sequência (seq) é incrementada automaticamente. Retorna 1 em caso de sucesso ou 0 em caso de erro de alocação.
int historico_registrar(Historico *h, TipoEvento tipo, int codigo, int matricula);

// Imprime o histórico completo na saída padrão conforme o comando HISTORICO (Seção 6.4).
void historico_imprimir(const Historico *h);

// Função auxiliar para converter o enum TipoEvento na string formatada correspondente.
const char* historico_tipo_para_string(TipoEvento tipo);

#endif 