#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int matricula;
    float nota1;
    float nota2;
    float nota3;
} Aluno;

// Função para alocar dinamicamente um aluno
Aluno* criarAluno(const char* nome, int matricula, float nota1, float nota2, float nota3) {
    Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));

    if (aluno != NULL) {
        strncpy(aluno->nome, nome, sizeof(aluno->nome) - 1);
        aluno->nome[sizeof(aluno->nome) - 1] = '\0';
        aluno->matricula = matricula;
        aluno->nota1 = nota1;
        aluno->nota2 = nota2;
        aluno->nota3 = nota3;
    }

    return aluno;
}

// Função para imprimir os dados de um aluno
void imprimirAluno(const Aluno* aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Matrícula: %d\n", aluno->matricula);
    printf("Nota1: %.2f\n", aluno->nota1);
    printf("Nota2: %.2f\n", aluno->nota2);
    printf("Nota3: %.2f\n", aluno->nota3);
}

// Função para calcular a média das notas de um aluno
float calcularMedia(const Aluno* aluno) {
    return (aluno->nota1 + aluno->nota2 + aluno->nota3) / 3.0;
}

// Função para verificar se um aluno foi aprovado ou reprovado
int aprovacao(const Aluno* aluno) {
    return calcularMedia(aluno) >= 6.0;
}

// Função para liberar a memória alocada para um aluno
void liberarAluno(Aluno* aluno) {
    free(aluno);
}

// Função principal para testar o TAD
int main() {
    // Criar alunos
    Aluno* aluno1 = criarAluno("Joao", 12345, 7.5, 8.0, 6.5);
    Aluno* aluno2 = criarAluno("Maria", 67890, 5.0, 6.0, 4.5);

    // Imprimir dados dos alunos
    printf("Dados do aluno 1:\n");
    imprimirAluno(aluno1);

    printf("\nDados do aluno 2:\n");
    imprimirAluno(aluno2);

    // Calcular média e verificar aprovação
    printf("\nMédia do aluno 1: %.2f\n", calcularMedia(aluno1));
    printf("Situação do aluno 1: %s\n", aprovacao(aluno1) ? "Aprovado" : "Reprovado");

    printf("\nMédia do aluno 2: %.2f\n", calcularMedia(aluno2));
    printf("Situação do aluno 2: %s\n", aprovacao(aluno2) ? "Aprovado" : "Reprovado");

    // Liberar a memória alocada
    liberarAluno(aluno1);
    liberarAluno(aluno2);

    return 0;
}
