#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma etiqueta
typedef struct {
    char etiqueta[50];
} Etiqueta;

// Estrutura para representar o conjunto de etiquetas de um contato
typedef struct {
    Etiqueta* etiquetas;
    int quantidade;
} ConjuntoEtiquetas;

// Estrutura principal para representar um contato
typedef struct {
    char nome[100];
    char telefone[20];
    ConjuntoEtiquetas etiquetas;
} Contato;

// Função para alocar dinamicamente um contato
Contato* criarContato(const char* nome, const char* telefone) {
    Contato* contato = (Contato*)malloc(sizeof(Contato));

    if (contato != NULL) {
        strncpy(contato->nome, nome, sizeof(contato->nome) - 1);
        contato->nome[sizeof(contato->nome) - 1] = '\0';

        strncpy(contato->telefone, telefone, sizeof(contato->telefone) - 1);
        contato->telefone[sizeof(contato->telefone) - 1] = '\0';

        // Inicializar o conjunto de etiquetas
        contato->etiquetas.etiquetas = NULL;
        contato->etiquetas.quantidade = 0;
    }

    return contato;
}

// Função para imprimir os dados de um contato, incluindo etiquetas
void imprimirContato(const Contato* contato) {
    printf("Nome: %s\n", contato->nome);
    printf("Telefone: %s\n", contato->telefone);
    printf("Etiquetas:\n");

    for (int i = 0; i < contato->etiquetas.quantidade; ++i) {
        printf(" - %s\n", contato->etiquetas.etiquetas[i].etiqueta);
    }
}

// Função para adicionar uma etiqueta ao conjunto do contato
void adicionarEtiqueta(Contato* contato, const char* etiqueta) {
    contato->etiquetas.etiquetas = (Etiqueta*)realloc(
        contato->etiquetas.etiquetas, (contato->etiquetas.quantidade + 1) * sizeof(Etiqueta)
    );

    if (contato->etiquetas.etiquetas != NULL) {
        strncpy(contato->etiquetas.etiquetas[contato->etiquetas.quantidade].etiqueta,
                etiqueta, sizeof(contato->etiquetas.etiquetas[0].etiqueta) - 1);
        
        contato->etiquetas.etiquetas[contato->etiquetas.quantidade].etiqueta[
            sizeof(contato->etiquetas.etiquetas[0].etiqueta) - 1] = '\0';

        contato->etiquetas.quantidade++;
    }
}

// Função para buscar contatos por etiqueta
Contato** buscarContatosPorEtiqueta(Contato** agenda, int quantidadeContatos, const char* etiqueta, int* quantidadeResultado) {
    Contato** resultado = NULL;
    *quantidadeResultado = 0;

    for (int i = 0; i < quantidadeContatos; ++i) {
        for (int j = 0; j < agenda[i]->etiquetas.quantidade; ++j) {
            if (strcmp(agenda[i]->etiquetas.etiquetas[j].etiqueta, etiqueta) == 0) {
                resultado = (Contato**)realloc(resultado, (*quantidadeResultado + 1) * sizeof(Contato*));
                resultado[*quantidadeResultado] = agenda[i];
                (*quantidadeResultado)++;
                break;  // Não é necessário verificar o mesmo contato mais de uma vez
            }
        }
    }

    return resultado;
}

// Função para remover um contato da agenda com base no nome
void removerContato(Contato** agenda, int* quantidadeContatos, const char* nome) {
    for (int i = 0; i < *quantidadeContatos; ++i) {
        if (strcmp(agenda[i]->nome, nome) == 0) {
            // Liberar a memória alocada para as etiquetas
            free(agenda[i]->etiquetas.etiquetas);

            // Mover os contatos restantes para preencher a lacuna
            for (int j = i; j < *quantidadeContatos - 1; ++j) {
                agenda[j] = agenda[j + 1];
            }

            // Reduzir a quantidade de contatos
            agenda = (Contato**)realloc(agenda, (*quantidadeContatos - 1) * sizeof(Contato*));
            (*quantidadeContatos)--;
            break;  // Não é necessário verificar os contatos restantes
        }
    }
}

// Função para listar todos os contatos
void listarTodosContatos(Contato** agenda, int quantidadeContatos) {
    for (int i = 0; i < quantidadeContatos; ++i) {
        printf("Contato %d:\n", i + 1);
        imprimirContato(agenda[i]);
        printf("\n");
    }
}

// Função para atualizar o número de telefone de um contato existente
void atualizarNumeroTelefone(Contato* contato, const char* novoTelefone) {
    strncpy(contato->telefone, novoTelefone, sizeof(contato->telefone) - 1);
    contato->telefone[sizeof(contato->telefone) - 1] = '\0';
}

// Função para liberar a memória alocada para o contato, incluindo etiquetas
void liberarContato(Contato* contato) {
    free(contato->etiquetas.etiquetas);
    free(contato);
}

// Função principal para testar o TAD
int main() {
    // Criar uma agenda com alguns contatos
    Contato** agenda = NULL;
    int quantidadeContatos = 0;

    agenda = (Contato**)realloc(agenda, (quantidadeContatos + 1) * sizeof(Contato*));
    agenda[quantidadeContatos++] = criarContato("Alice", "123456789");
    adicionarEtiqueta(agenda[0], "Amigo");

    agenda = (Contato**)realloc(agenda, (quantidadeContatos + 1) * sizeof(Contato*));
    agenda[quantidadeContatos++] = criarContato("Bob", "987654321");
    adicionarEtiqueta(agenda[1], "Família");

    agenda = (Contato**)realloc(agenda, (quantidadeContatos + 1) * sizeof(Contato*));
    agenda[quantidadeContatos++] = criarContato("Charlie", "456789123");
    adicionarEtiqueta(agenda[2], "Trabalho");

    // Imprimir dados dos contatos
    for (int i = 0; i < quantidadeContatos; ++i) {
        printf("Contato %d:\n", i + 1);
        imprimirContato(agenda[i]);
        printf("\n");
    }

    // Adicionar etiqueta e imprimir
    adicionarEtiqueta(agenda[0], "Colega");
    printf("Etiquetas do Contato 1 após adição:\n");
    imprimirContato(agenda[0]);
    printf("\n");

    // Buscar contatos por etiqueta
    const char* etiquetaBuscada = "Trabalho";
    int quantidadeResultado;
    Contato** contatosEncontrados = buscarContatosPorEtiqueta(agenda, quantidadeContatos, etiquetaBuscada, &quantidadeResultado);
    printf("Contatos com a etiqueta '%s':\n", etiquetaBuscada);
    for (int i = 0; i < quantidadeResultado; ++i) {
        imprimirContato(contatosEncontrados[i]);
        printf("\n");
    }
    free(contatosEncontrados);
    printf("\n");

    // Remover contato e listar todos
    const char* nomeRemover = "Bob";
    removerContato(agenda, &quantidadeContatos, nomeRemover);
    printf("Contatos após remoção do contato '%s':\n", nomeRemover);
    listarTodosContatos(agenda, quantidadeContatos);
    printf("\n");

    // Atualizar número de telefone e imprimir
    const char* novoTelefone = "111222333";
    atualizarNumeroTelefone(agenda[0], novoTelefone);
    printf("Contato 1 após atualização do número de telefone:\n");
    imprimirContato(agenda[0]);
    printf("\n");

    // Liberar a memória alocada
    for (int i = 0; i < quantidadeContatos; ++i) {
        liberarContato(agenda[i]);
    }
    free(agenda);

    return 0;
}
