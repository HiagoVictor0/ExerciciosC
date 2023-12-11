#include <stdio.h>
#include <stdlib.h>

void imprimirMatriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {

    int linhas = 100;
    int colunas = 100;

    int **matriz = (int **)calloc(linhas, sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)calloc(colunas, sizeof(int));
    }

    int inicioLinha = linhas / 4;
    int fimLinha = 3 * linhas / 4;
    int inicioColuna = colunas / 4;
    int fimColuna = 3 * colunas / 4;

    for (int i = inicioLinha; i < fimLinha; i++) {
        for (int j = inicioColuna; j < fimColuna; j++) {
            matriz[i][j] = 1;
        }
    }

    int centroLinha = (inicioLinha + fimLinha) / 2;
    int centroColuna = (inicioColuna + fimColuna) / 2;

    int raio = (fimLinha - inicioLinha) / 4;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int distanciaAoCentro = (i - centroLinha) * (i - centroLinha) + (j - centroColuna) * (j - centroColuna);
            if (distanciaAoCentro <= raio * raio) {
                matriz[i][j] = 2;
            }
        }
    }

    imprimirMatriz(matriz, linhas, colunas);

    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
