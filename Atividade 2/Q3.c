#include <stdio.h>

int somaInteirosPositivos(int K) {
    if (K <= 0) {
        return 0;
    } else {
        return K + somaInteirosPositivos(K - 1);
    }
}

int main() {
    int K;

    scanf("%d", &K);

    int resultado = somaInteirosPositivos(K);

    printf("%d\n", resultado);

    return 0;
}
