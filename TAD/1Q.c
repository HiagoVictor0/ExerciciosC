#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int jogos;
    int gols;
    int assistencias;
} JogadorFutebol;

// Função para alocar dinamicamente um jogador de futebol
JogadorFutebol* criarJogador(const char* nome, int jogos, int gols, int assistencias) {
    JogadorFutebol* jogador = (JogadorFutebol*)malloc(sizeof(JogadorFutebol));

    if (jogador != NULL) {
        strncpy(jogador->nome, nome, sizeof(jogador->nome) - 1);
        jogador->nome[sizeof(jogador->nome) - 1] = '\0';
        jogador->jogos = jogos;
        jogador->gols = gols;
        jogador->assistencias = assistencias;
    }

    return jogador;
}

// Função para imprimir os dados de um jogador
void imprimirJogador(const JogadorFutebol* jogador) {
    printf("Nome: %s\n", jogador->nome);
    printf("Jogos: %d\n", jogador->jogos);
    printf("Gols: %d\n", jogador->gols);
    printf("Assistencias: %d\n", jogador->assistencias);
}

// Função para somar estatísticas de dois jogadores
JogadorFutebol* somarJogadores(const JogadorFutebol* jogador1, const JogadorFutebol* jogador2) {
    JogadorFutebol* novoJogador = criarJogador("Soma", 0, 0, 0);

    if (novoJogador != NULL) {
        strcpy(novoJogador->nome, "Soma");
        novoJogador->jogos = jogador1->jogos + jogador2->jogos;
        novoJogador->gols = jogador1->gols + jogador2->gols;
        novoJogador->assistencias = jogador1->assistencias + jogador2->assistencias;
    }

    return novoJogador;
}

// Função para testar se o jogador é bom (critério simples: mais gols que jogos)
int ehBom(const JogadorFutebol* jogador) {
    return jogador->gols > jogador->jogos;
}

// Função para liberar a memória alocada para um jogador
void liberarJogador(JogadorFutebol* jogador) {
    free(jogador);
}

// Função principal para testar o TAD
int main() {
    JogadorFutebol* jogador1 = criarJogador("Neymar", 50, 30, 20);
    JogadorFutebol* jogador2 = criarJogador("Messi", 60, 40, 30);

    printf("Dados do jogador 1:\n");
    imprimirJogador(jogador1);

    printf("\nDados do jogador 2:\n");
    imprimirJogador(jogador2);

    JogadorFutebol* jogadorSoma = somarJogadores(jogador1, jogador2);
    printf("\nSoma dos jogadores 1 e 2:\n");
    imprimirJogador(jogadorSoma);

    printf("\nO jogador 1 eh bom? %s\n", ehBom(jogador1) ? "Sim" : "Não");
    printf("O jogador 2 eh bom? %s\n", ehBom(jogador2) ? "Sim" : "Não");

    // Liberar a memória alocada
    liberarJogador(jogador1);
    liberarJogador(jogador2);
    liberarJogador(jogadorSoma);

    return 0;
}
