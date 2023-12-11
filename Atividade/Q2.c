#include <stdio.h>
#include <stdlib.h>

void imprimirVetor(int *vetor, int tamanho) {
    printf("Valores no vetor: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int *vetor = NULL;
    int tamanho = 0;
    int valor;

    printf("Digite os valores inteiros (para encerrar, digite -1):\n");

    while (1) {
        scanf("%d", &valor);

        if (valor == -1) {
            break;
        }

        vetor = (int *)realloc(vetor, (tamanho + 1) * sizeof(int));

        if (vetor == NULL) {
            fprintf(stderr, "Erro ao alocar memoria.\n");
            exit(EXIT_FAILURE);
        }

        vetor[tamanho] = valor;
        tamanho++;
    }

    if (tamanho == 0) {
        printf("Nenhum valor foi inserido.\n");
        free(vetor);
        return 0;
    }

    int somatorio = 0;
    int menor = vetor[0];
    int maior = vetor[0];

    for (int i = 0; i < tamanho; i++) {
        somatorio += vetor[i];

        if (vetor[i] < menor) {
            menor = vetor[i];
        }

        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }

    float media = (float)somatorio / tamanho;

    printf("Somatorio: %d\n", somatorio);
    printf("Media: %.2f\n", media);
    printf("Menor valor: %d\n", menor);
    printf("Maior valor: %d\n", maior);
    imprimirVetor(vetor, tamanho);

    free(vetor);

    return 0;
}
