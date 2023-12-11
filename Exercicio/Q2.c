#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int M, N, x;

    printf("(linhas): ");
    scanf("%d", &M);
    printf("(colunas): ");
    scanf("%d", &N);
    printf("(x): ");
    scanf("%d", &x);

    if (M <= 0 || N <= 0 || x <= 0) {
        printf("Valores inválidos para M, N ou x. Certifique-se de que todos sejam maiores que zero.\n");
        return 1;
    }

    srand(time(NULL));
  
    int matriz[M][N];

    int ocorrencias[x + 1]; 
    for (int i = 0; i <= x; i++) {
        ocorrencias[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = rand() % (x + 1);
            ocorrencias[matriz[i][j]]++;
        }
    }

    for (int i = 0; i <= x; i++) {
        if(ocorrencias[i] == 1){
            printf("O numero %d ocorreu %d vez na matriz.\n", i, ocorrencias[i]);
        }
        else if(ocorrencias[i] > 1){
            printf("O numero %d ocorreu %d vezes na matriz.\n", i, ocorrencias[i]);
        }

    }

    return 0;
}