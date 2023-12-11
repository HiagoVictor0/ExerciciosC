#include <stdio.h>
#include <ctype.h>

void calcularEstatisticas(char vetor[], int tamanho) {

    int contagem[256] = {0}; 

    for (int i = 0; i < tamanho; i++) {
        char caractere = vetor[i];
        contagem[(unsigned char)caractere]++;
    }

    printf("Estatisticas:\n");
    for (int i = 0; i < 256; i++) {
        if (contagem[i] > 0 && isprint(i)) {
            printf("'%c' = %d\n", i, contagem[i]);
        }
    }
}

int main() {

    printf("Digite um vetor de caracteres: ");

    #define TAMANHO_MAX 100
    char vetor[TAMANHO_MAX];

    fgets(vetor, sizeof(vetor), stdin);

    int tamanho = 0;
    while (vetor[tamanho] != '\0' && vetor[tamanho] != '\n') {
        tamanho++;
    }

    calcularEstatisticas(vetor, tamanho);

    return 0;
}
