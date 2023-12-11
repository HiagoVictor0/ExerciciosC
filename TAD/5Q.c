#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma tarefa
typedef struct {
    char descricao[100];
    int concluida; // 0 para em andamento, 1 para concluída
} Tarefa;

// Estrutura para representar um membro da equipe
typedef struct {
    char nome[50];
} MembroEquipe;

// Estrutura principal para representar um projeto
typedef struct {
    char nome[100];
    char dataInicio[20];
    char dataConclusao[20];
    Tarefa* tarefas;
    int quantidadeTarefas;
    MembroEquipe* equipe;
    int quantidadeMembros;
} Projeto;

// Função para alocar dinamicamente um projeto
Projeto* criarProjeto(const char* nome, const char* dataInicio, const char* dataConclusao) {
    Projeto* projeto = (Projeto*)malloc(sizeof(Projeto));

    if (projeto != NULL) {
        strncpy(projeto->nome, nome, sizeof(projeto->nome) - 1);
        projeto->nome[sizeof(projeto->nome) - 1] = '\0';

        strncpy(projeto->dataInicio, dataInicio, sizeof(projeto->dataInicio) - 1);
        projeto->dataInicio[sizeof(projeto->dataInicio) - 1] = '\0';

        strncpy(projeto->dataConclusao, dataConclusao, sizeof(projeto->dataConclusao) - 1);
        projeto->dataConclusao[sizeof(projeto->dataConclusao) - 1] = '\0';

        projeto->tarefas = NULL;
        projeto->quantidadeTarefas = 0;

        projeto->equipe = NULL;
        projeto->quantidadeMembros = 0;
    }

    return projeto;
}

// Função para imprimir os dados do projeto, incluindo tarefas e membros da equipe
void imprimirProjeto(const Projeto* projeto) {
    printf("Nome do Projeto: %s\n", projeto->nome);
    printf("Data de Início: %s\n", projeto->dataInicio);
    printf("Data de Conclusão: %s\n", projeto->dataConclusao);

    printf("Tarefas:\n");
    for (int i = 0; i < projeto->quantidadeTarefas; ++i) {
        printf(" - Descrição: %s, Status: %s\n", projeto->tarefas[i].descricao,
               projeto->tarefas[i].concluida ? "Concluída" : "Em Andamento");
    }

    printf("Membros da Equipe:\n");
    for (int i = 0; i < projeto->quantidadeMembros; ++i) {
        printf(" - %s\n", projeto->equipe[i].nome);
    }
}

// Função para adicionar uma tarefa ao projeto
void adicionarTarefa(Projeto* projeto, const char* descricao) {
    projeto->tarefas = (Tarefa*)realloc(
        projeto->tarefas, (projeto->quantidadeTarefas + 1) * sizeof(Tarefa)
    );

    if (projeto->tarefas != NULL) {
        strncpy(projeto->tarefas[projeto->quantidadeTarefas].descricao,
                descricao, sizeof(projeto->tarefas[0].descricao) - 1);
        
        projeto->tarefas[projeto->quantidadeTarefas].descricao[
            sizeof(projeto->tarefas[0].descricao) - 1] = '\0';

        projeto->tarefas[projeto->quantidadeTarefas].concluida = 0; // Tarefa inicia como "em andamento"

        projeto->quantidadeTarefas++;
    }
}

// Função para adicionar um membro à equipe do projeto
void adicionarMembroEquipe(Projeto* projeto, const char* nome) {
    projeto->equipe = (MembroEquipe*)realloc(
        projeto->equipe, (projeto->quantidadeMembros + 1) * sizeof(MembroEquipe)
    );

    if (projeto->equipe != NULL) {
        strncpy(projeto->equipe[projeto->quantidadeMembros].nome,
                nome, sizeof(projeto->equipe[0].nome) - 1);
        
        projeto->equipe[projeto->quantidadeMembros].nome[
            sizeof(projeto->equipe[0].nome) - 1] = '\0';

        projeto->quantidadeMembros++;
    }
}

// Função para remover uma tarefa do projeto com base na descrição
void removerTarefa(Projeto* projeto, const char* descricao) {
    for (int i = 0; i < projeto->quantidadeTarefas; ++i) {
        if (strcmp(projeto->tarefas[i].descricao, descricao) == 0) {
            // Move as tarefas restantes para preencher a lacuna
            for (int j = i; j < projeto->quantidadeTarefas - 1; ++j) {
                strcpy(projeto->tarefas[j].descricao, projeto->tarefas[j + 1].descricao);
                projeto->tarefas[j].concluida = projeto->tarefas[j + 1].concluida;
            }

            // Reduz a quantidade de tarefas
            projeto->tarefas = (Tarefa*)realloc(
                projeto->tarefas, (projeto->quantidadeTarefas - 1) * sizeof(Tarefa)
            );

            projeto->quantidadeTarefas--;
            break; // A tarefa foi removida, não é necessário continuar
        }
    }
}

// Função para marcar uma tarefa como concluída com base em sua descrição
void concluirTarefa(Projeto* projeto, const char* descricao) {
    for (int i = 0; i < projeto->quantidadeTarefas; ++i) {
        if (strcmp(projeto->tarefas[i].descricao, descricao) == 0) {
            projeto->tarefas[i].concluida = 1; // Tarefa marcada como concluída
            break; // A tarefa foi encontrada e concluída, não é necessário continuar
        }
    }
}

// Função para listar projetos por membro da equipe
Projeto** listarProjetosPorMembroEquipe(const Projeto** projetos, int quantidadeProjetos, const char* nomeMembro, int* quantidadeResultado) {
    Projeto** resultado = NULL;
    *quantidadeResultado = 0;

    for (int i = 0; i < quantidadeProjetos; ++i) {
        for (int j = 0; j < projetos[i]->quantidadeMembros; ++j) {
            if (strcmp(projetos[i]->equipe[j].nome, nomeMembro) == 0) {
                resultado = (Projeto**)realloc(resultado, (*quantidadeResultado + 1) * sizeof(Projeto*));
                resultado[*quantidadeResultado] = projetos[i];
                (*quantidadeResultado)++;
                break; // O membro está envolvido em pelo menos um projeto, não é necessário continuar
            }
        }
    }

    return resultado;
}

// Função para liberar a memória alocada para o projeto, incluindo tarefas e membros da equipe
void liberarProjeto(Projeto* projeto) {
    free(projeto->tarefas);
    free(projeto->equipe);
    free(projeto);
}

// Função principal para testar o TAD
int main() {
    // Criar e gerenciar projetos
    Projeto** projetos = NULL;
    int quantidadeProjetos = 0;

    projetos = (Projeto**)realloc(projetos, (quantidadeProjetos + 1) * sizeof(Projeto*));
    projetos[quantidadeProjetos++] = criarProjeto("Projeto A", "01/01/2023", "31/12/2023");
    adicionarTarefa(projetos[0], "Implementar funcionalidade X");
    adicionarMembroEquipe(projetos[0], "Alice");

    projetos = (Projeto**)realloc(projetos, (quantidadeProjetos + 1) * sizeof(Projeto*));
    projetos[quantidadeProjetos++] = criarProjeto("Projeto B", "15/02/2023", "30/11/2023");
    adicionarTarefa(projetos[1], "Testar aplicação");
    adicionarMembroEquipe(projetos[1], "Bob");

    // Imprimir dados dos projetos
    for (int i = 0; i < quantidadeProjetos; ++i) {
        printf("Projeto %d:\n", i + 1);
        imprimirProjeto(projetos[i]);
        printf("\n");
    }

    // Adicionar tarefa e imprimir
    adicionarTarefa(projetos[0], "Revisar documentação");
    printf("Tarefas do Projeto 1 após adição:\n");
    imprimirProjeto(projetos[0]);
    printf("\n");

    // Remover tarefa e listar todos os projetos
    const char* descricaoRemover = "Implementar funcionalidade X";
    removerTarefa(projetos[0], descricaoRemover);
    printf("Projeto 1 após remoção da tarefa '%s':\n", descricaoRemover);
    imprimirProjeto(projetos[0]);
    printf("\n");

    // Concluir tarefa e imprimir
    const char* descricaoConcluir = "Revisar documentação";
    concluirTarefa(projetos[0], descricaoConcluir);
    printf("Projeto 1 após conclusão da tarefa '%s':\n", descricaoConcluir);
    imprimirProjeto(projetos[0]);
    printf("\n");

    // Listar projetos por membro da equipe
    const char* membroDesejado = "Alice";
    int quantidadeProjetosMembro;
    Projeto** projetosMembro = listarProjetosPorMembroEquipe(projetos, quantidadeProjetos, membroDesejado, &quantidadeProjetosMembro);
    printf("Projetos em que %s está envolvido:\n", membroDesejado);
    for (int i = 0; i < quantidadeProjetosMembro; ++i) {
        imprimirProjeto(projetosMembro[i]);
        printf("\n");
    }
    free(projetosMembro);
    printf("\n");

    // Liberar a memória alocada
    for (int i = 0; i < quantidadeProjetos; ++i) {
        liberarProjeto(projetos[i]);
    }
    free(projetos);

    return 0;
}
