    #include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma palavra-chave
typedef struct {
    char palavra[50];
} PalavraChave;

// Estrutura para representar a lista de palavras-chave de um livro
typedef struct {
    PalavraChave* palavras;
    int quantidade;
} ListaPalavrasChave;

// Estrutura principal para representar um livro
typedef struct {
    char titulo[100];
    char autor[50];
    int anoPublicacao;
    ListaPalavrasChave palavrasChave;
} Livro;

// Função para alocar dinamicamente um livro
Livro* criarLivro(const char* titulo, const char* autor, int anoPublicacao) {
    Livro* livro = (Livro*)malloc(sizeof(Livro));

    if (livro != NULL) {
        strncpy(livro->titulo, titulo, sizeof(livro->titulo) - 1);
        livro->titulo[sizeof(livro->titulo) - 1] = '\0';

        strncpy(livro->autor, autor, sizeof(livro->autor) - 1);
        livro->autor[sizeof(livro->autor) - 1] = '\0';

        livro->anoPublicacao = anoPublicacao;

        // Inicializar a lista de palavras-chave
        livro->palavrasChave.palavras = NULL;
        livro->palavrasChave.quantidade = 0;
    }

    return livro;
}

// Função para imprimir os dados de um livro, incluindo palavras-chave
void imprimirLivro(const Livro* livro) {
    printf("Título: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Ano de Publicação: %d\n", livro->anoPublicacao);
    printf("Palavras-Chave:\n");

    for (int i = 0; i < livro->palavrasChave.quantidade; ++i) {
        printf(" - %s\n", livro->palavrasChave.palavras[i].palavra);
    }
}

// Função para adicionar uma palavra-chave à lista do livro
void adicionarPalavraChave(Livro* livro, const char* palavra) {
    livro->palavrasChave.palavras = (PalavraChave*)realloc(
        livro->palavrasChave.palavras, (livro->palavrasChave.quantidade + 1) * sizeof(PalavraChave)
    );

    if (livro->palavrasChave.palavras != NULL) {
        strncpy(livro->palavrasChave.palavras[livro->palavrasChave.quantidade].palavra,
                palavra, sizeof(livro->palavrasChave.palavras[0].palavra) - 1);
        
        livro->palavrasChave.palavras[livro->palavrasChave.quantidade].palavra[
            sizeof(livro->palavrasChave.palavras[0].palavra) - 1] = '\0';

        livro->palavrasChave.quantidade++;
    }
}

// Função para verificar se uma palavra-chave está presente na lista do livro
int buscarPalavraChave(const Livro* livro, const char* palavra) {
    for (int i = 0; i < livro->palavrasChave.quantidade; ++i) {
        if (strcmp(livro->palavrasChave.palavras[i].palavra, palavra) == 0) {
            return 1; // Encontrou a palavra-chave
        }
    }

    return 0; // Não encontrou a palavra-chave
}

// Função para liberar a memória alocada para o livro, incluindo a lista de palavras-chave
void liberarLivro(Livro* livro) {
    free(livro->palavrasChave.palavras);
    free(livro);
}

// Função para criar uma lista de livros de um autor específico
Livro** listaLivrosPorAutor(Livro** biblioteca, int quantidadeLivros, const char* autor, int* quantidadeResultado) {
    Livro** resultado = NULL;
    *quantidadeResultado = 0;

    for (int i = 0; i < quantidadeLivros; ++i) {
        if (strcmp(biblioteca[i]->autor, autor) == 0) {
            resultado = (Livro**)realloc(resultado, (*quantidadeResultado + 1) * sizeof(Livro*));
            resultado[*quantidadeResultado] = biblioteca[i];
            (*quantidadeResultado)++;
        }
    }

    return resultado;
}

// Função para remover uma palavra-chave da lista do livro
void removerPalavraChave(Livro* livro, const char* palavra) {
    for (int i = 0; i < livro->palavrasChave.quantidade; ++i) {
        if (strcmp(livro->palavrasChave.palavras[i].palavra, palavra) == 0) {
            // Move as palavras-chave restantes para preencher a lacuna
            for (int j = i; j < livro->palavrasChave.quantidade - 1; ++j) {
                strcpy(livro->palavrasChave.palavras[j].palavra, livro->palavrasChave.palavras[j + 1].palavra);
            }

            // Reduz a quantidade de palavras-chave
            livro->palavrasChave.palavras = (PalavraChave*)realloc(
                livro->palavrasChave.palavras, (livro->palavrasChave.quantidade - 1) * sizeof(PalavraChave)
            );

            livro->palavrasChave.quantidade--;
            break; // A palavra-chave foi removida, não é necessário continuar
        }
    }
}

// Função principal para testar o TAD
int main() {
    // Criar uma biblioteca com alguns livros
    Livro* biblioteca[3];

    biblioteca[0] = criarLivro("Livro A", "Autor 1", 2000);
    adicionarPalavraChave(biblioteca[0], "Ficção");
    adicionarPalavraChave(biblioteca[0], "Aventura");

    biblioteca[1] = criarLivro("Livro B", "Autor 2", 2010);
    adicionarPalavraChave(biblioteca[1], "Romance");

    biblioteca[2] = criarLivro("Livro C", "Autor 1", 2005);
    adicionarPalavraChave(biblioteca[2], "Ficção");

    // Imprimir dados dos livros
    for (int i = 0; i < 3; ++i) {
        printf("Livro %d:\n", i + 1);
        imprimirLivro(biblioteca[i]);
        printf("\n");
    }

    // Adicionar e imprimir palavra-chave
    adicionarPalavraChave(biblioteca[1], "Suspense");
    printf("Palavras-Chave do Livro B após adição:\n");
    imprimirLivro(biblioteca[1]);
    printf("\n");

    // Buscar palavra-chave
    const char* palavraBuscada = "Ficção";
    printf("A palavra-chave '%s' está presente no Livro A? %s\n", palavraBuscada,
           buscarPalavraChave(biblioteca[0], palavraBuscada) ? "Sim" : "Não");
    printf("\n");

    // Listar livros de um autor
    const char* autorDesejado = "Autor 1";
    int quantidadeLivrosAutor;
    Livro** livrosAutor = listaLivrosPorAutor(biblioteca, 3, autorDesejado, &quantidadeLivrosAutor);
    printf("Livros do Autor %s:\n", autorDesejado);
    for (int i = 0; i < quantidadeLivrosAutor; ++i) {
        imprimirLivro(livrosAutor[i]);
        printf("\n");
    }
    free(livrosAutor);
    printf("\n");

    // Remover palavra-chave e imprimir
    const char* palavraRemover = "Romance";
    removerPalavraChave(biblioteca[1], palavraRemover);
    printf("Palavras-Chave do Livro B após remoção de '%s':\n", palavraRemover);
    imprimirLivro(biblioteca[1]);
    printf("\n");

    // Liberar a memória alocada
    for (int i = 0; i < 3; ++i) {
        liberarLivro(biblioteca[i]);
    }

    return 0;
}
