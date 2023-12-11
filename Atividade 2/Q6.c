#include <stdio.h>

int buscaSequencial(int vetor[], int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == valor) {
            return i; // Retorna a posição se o valor for encontrado
        }
    }
    return -1; // Retorna -1 se o valor não for encontrado
}

int main() {
    int tamanho, valor;
    
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    
    int vetor[tamanho];
    
    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }
    
    printf("Digite o valor a ser procurado: ");
    scanf("%d", &valor);
    
    int posicao = buscaSequencial(vetor, tamanho, valor);
    
    if (posicao != -1) {
        printf("O valor %d foi encontrado na posicao %d do vetor.\n", valor, posicao);
    } else {
        printf("O valor %d nao foi encontrado no vetor.\n", valor);
    }
    
    return 0;
}
