#include <stdio.h>

int inverterNumero(int x, int invertido) {

    if (x == 0) {
        return invertido;
    }

    int ultimoDigito = x % 10;

    int numeroRestante = x / 10;

    invertido = invertido * 10 + ultimoDigito;

    return inverterNumero(numeroRestante, invertido);
}

int main() {
    int numeroOriginal, numeroInvertido;

    printf("Digite um numero inteiro: ");
    scanf("%d", &numeroOriginal);

    numeroInvertido = inverterNumero(numeroOriginal, 0);

    printf("O numero invertido e: %d\n", numeroInvertido);

    return 0;
}
