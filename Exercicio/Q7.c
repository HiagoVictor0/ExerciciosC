#include <stdio.h>
#include <stdlib.h>

int* obtem_produtos_zerados(int* codigo, int* estoque, int num_produtos, int* num_zerados) {
  
    *num_zerados = 0;

    for (int i = 0; i < num_produtos; i++) {
        if (estoque[i] == 0) {
            (*num_zerados)++;
        }
    }

    int* codigos_zerados = (int*)malloc(*num_zerados * sizeof(int));

    if (codigos_zerados == NULL) {
        perror("Erro de alocaçao de memoria");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    for (int i = 0; i < num_produtos; i++) {
        if (estoque[i] == 0) {
            codigos_zerados[index++] = codigo[i];
        }
    }

    return codigos_zerados;
}

int main() {
  
    int num_produtos;
    printf("Digite o numero de produtos: ");
    scanf("%d", &num_produtos);

    int* codigo = (int*)malloc(num_produtos * sizeof(int));
    int* estoque = (int*)malloc(num_produtos * sizeof(int));

    if (codigo == NULL || estoque == NULL) {
        perror("Erro de alocaçao de memoria");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_produtos; i++) {
        printf("Digite o codigo do produto %d: ", i + 1);
        scanf("%d", &codigo[i]);

        printf("Digite o estoque do produto %d: ", i + 1);
        scanf("%d", &estoque[i]);
    }

    int num_zerados;
    int* codigos_zerados = obtem_produtos_zerados(codigo, estoque, num_produtos, &num_zerados);

    printf("\nCodigos dos produtos com estoque zero:\n");
    for (int i = 0; i < num_zerados; i++) {
        printf("%d\n", codigos_zerados[i]);
    }

    free(codigo);
    free(estoque);
    free(codigos_zerados);

    return 0;
}
