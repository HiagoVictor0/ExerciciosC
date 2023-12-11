#include <stdio.h>

int potencia(int x, int y) {

    if (y == 0) {
        return 1;
    }

    else {
        return x * potencia(x, y - 1);
    }
}

int main() {
    int x, y;

    printf("Digite o valor de x: ");
    scanf("%d", &x);
    printf("Digite o valor de y: ");
    scanf("%d", &y);

    int resultado = potencia(x, y);

    printf("%d^%d = %d\n", x, y, resultado);

    return 0;
}
