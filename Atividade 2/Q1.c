#include <stdio.h>

int exp(int b, int p){

    if (p == 0) {
        return 1;
    }

    else {
        return b * exp(b, p - 1);
    }
}

int main() {
    int b, p;

    printf("Digite o valor de b: ");
    scanf("%d", &b);
    printf("Digite o valor de p: ");
    scanf("%d", &p);

    int resultado = exp(b, p);

    printf("%d^%d = %d\n", b, p, resultado);

    return 0;
}
