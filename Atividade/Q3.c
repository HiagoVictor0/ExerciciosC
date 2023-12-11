#include <stdio.h>
#include <stdlib.h>

int* obtem_produtos_zerados(int *codigo, int *estoque, int num_produtos, int *num_zerados) {
    int *produtos_zerados = NULL;  
    *num_zerados = 0; 

    for (int i = 0; i < num_produtos; i++) {
        if (estoque[i] == 0) {
            
            produtos_zerados = (int *)realloc(produtos_zerados, (*num_zerados + 1) * sizeof(int));

            if (produtos_zerados == NULL) {
                fprintf(stderr, "Erro ao alocar memoria.\n");
                exit(EXIT_FAILURE);
            }

            produtos_zerados[*num_zerados] = codigo[i];
            (*num_zerados)++;
        }
    }

    return produtos_zerados;
}

int main() {
    int num_produtos;

    printf("Digite o numero de produtos: ");
    scanf("%d", &num_produtos);

    int *codigo = (int *)malloc(num_produtos * sizeof(int));
    int *estoque = (int *)malloc(num_produtos * sizeof(int));

    // Solicita ao usuário os códigos e estoques dos produtos
    for (int i = 0; i < num_produtos; i++) {
        printf("Digite o codigo do produto %d: ", i + 1);
        scanf("%d", &codigo[i]);

        printf("Digite o estoque do produto %d: ", i + 1);
        scanf("%d", &estoque[i]);
    }

    int num_zerados;
    int *produtos_zerados = obtem_produtos_zerados(codigo, estoque, num_produtos, &num_zerados);

    printf("Codigos dos produtos com estoque zero: ");
    for (int i = 0; i < num_zerados; i++) {
        printf("%d ", produtos_zerados[i]);
    }
    printf("\n");

    free(codigo);
    free(estoque);
    free(produtos_zerados);

    return 0;
}
