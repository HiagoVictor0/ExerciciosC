#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* subtrai(const char* s1, const char* s2) {

    char* resultado = (char*)malloc(strlen(s1) + 1); 
    if (resultado == NULL) {
        perror("Erro de alocaçao de memoria");
        exit(EXIT_FAILURE);
    }

    resultado[0] = '\0';

    for (size_t i = 0; i < strlen(s1); i++) {

        if (strchr(s2, s1[i]) == NULL) {
           
            resultado = (char*)realloc(resultado, strlen(resultado) + 2); 
            if (resultado == NULL) {
                perror("Erro de realocaçao de memoria");
                exit(EXIT_FAILURE);
            }
            resultado[strlen(resultado) + 1] = '\0';
            resultado[strlen(resultado)] = s1[i];
        }
    }

    return resultado;
}

int main() {
  
    char s1[100], s2[100];

    printf("Digite a primeira string: ");
    fgets(s1, sizeof(s1), stdin);
    s1[strcspn(s1, "\n")] = '\0'; 

    printf("Digite a segunda string: ");
    fgets(s2, sizeof(s2), stdin);
    s2[strcspn(s2, "\n")] = '\0'; 

    char* resultado = subtrai(s1, s2);

    printf("Resultado: %s\n", resultado);

    free(resultado);

    return 0;
}
