#include <stdio.h>

int somaIntervalo(int A, int B) {
    if (A == B) {
        return A;
    } else if (A < B) {
        return A + somaIntervalo(A + 1, B);
    } else {
        return B + somaIntervalo(A, B + 1);
    }
}

int main() {
    int A, B;
    printf("Digite o valor de A: ");
    scanf("%d", &A);
    printf("Digite o valor de B: ");
    scanf("%d", &B);

    int resultado;

    if (A <= B) {
        resultado = somaIntervalo(A, B);
    } else {
        resultado = somaIntervalo(B, A);
    }

    printf("%d\n", resultado);

    return 0;
}
