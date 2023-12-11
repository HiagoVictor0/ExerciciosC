#include <stdio.h>
#include <math.h>

double calcularJurosCompostos(double valorInicial, int meses, double taxaJurosPercentagem) {
    if (meses == 0) {
        return valorInicial;
    } else {
        double taxaJurosDecimal = taxaJurosPercentagem / 100.0;
        double montante = calcularJurosCompostos(valorInicial, meses - 1, taxaJurosPercentagem);
        return montante * (1.0 + taxaJurosDecimal);
    }
}

int main() {
    double valorInicial, taxaJurosPercentagem;
    int meses;

    printf("Digite o valor inicial: ");
    scanf("%lf", &valorInicial);

    printf("Digite o numero de meses: ");
    scanf("%d", &meses);

    printf("Digite a taxa de juros mensal: ");
    scanf("%lf", &taxaJurosPercentagem);

    double montante = calcularJurosCompostos(valorInicial, meses, taxaJurosPercentagem);

    printf("%.2lf\n", montante);

    return 0;
}
