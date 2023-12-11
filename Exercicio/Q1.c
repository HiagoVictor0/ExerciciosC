#include <stdio.h>

int main() {
    int x, soma = 0, contagem = 0, menor, maior;
    float media;

    scanf("%d", &x);

    if(x == -1) {
        printf("Nenhum  numerofoi inserido. Encerrando o programa.\n");
        return 0;
    }

    menor = maior = x;
    soma += x;
    contagem++;

    while (1) {
        scanf("%d", &x);

        if(x == -1) {
            break;
        }

        soma += x;
        contagem++;

        if (x < menor) {
            menor = x;
        }

        if (x > maior) {
            maior = x;
        }
    }
    if (contagem > 0) {
        media = (float)soma / contagem;

        printf("Somatorio: %d\n", soma);
        printf("Media: %.2f\n", media);
        printf("Menor numero: %d\n", menor);
        printf("Maior numero: %d\n", maior);
    } else {
        printf("Nenhum numero foi inserido.\n");
    }

    return 0;
}
