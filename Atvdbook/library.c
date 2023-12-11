#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titulo[50];
    char autor[50];
    int anoPublicacao;
    int id;
} Livro;

typedef struct No {
    Livro livro;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
} ListaEncadeada;

void inicializarLista(ListaEncadeada* lista) {
    lista->inicio = NULL;
}

void inserirLivro(ListaEncadeada* lista, Livro novoLivro) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->livro = novoLivro;
    novoNo->proximo = NULL;

    if (lista->inicio == NULL || novoLivro.id < lista->inicio->livro.id) {
        novoNo->proximo = lista->inicio;
        lista->inicio = novoNo;
        return;
    }

    No* atual = lista->inicio;
    No* anterior = NULL;

    while (atual != NULL && novoLivro.id > atual->livro.id) {
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = novoNo;
    novoNo->proximo = atual;
}

void removerLivro(ListaEncadeada* lista, int id) {
    No* atual = lista->inicio;
    No* anterior = NULL;

    while (atual != NULL && atual->livro.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (anterior != NULL) {
            anterior->proximo = atual->proximo;
        } else {
            lista->inicio = atual->proximo;
        }
        free(atual);
    }
}

ListaEncadeada listarLivrosPorAutor(ListaEncadeada* lista, char autor[]) {
    ListaEncadeada resultado;
    inicializarLista(&resultado);

    No* atual = lista->inicio;

    while (atual != NULL) {
        if (strcmp(atual->livro.autor, autor) == 0) {
            inserirLivro(&resultado, atual->livro);
        }
        atual = atual->proximo;
    }

    return resultado;
}

void atualizarAnoPublicacao(ListaEncadeada* lista, int id, int novoAno) {
    No* atual = lista->inicio;

    while (atual != NULL && atual->livro.id != id) {
        atual = atual->proximo;
    }

    if (atual != NULL) {
        atual->livro.anoPublicacao = novoAno;
    }
}

int quantidadeLivrosPorAutor(ListaEncadeada* lista, char autor[]) {
    int quantidade = 0;
    No* atual = lista->inicio;

    while (atual != NULL) {
        if (strcmp(atual->livro.autor, autor) == 0) {
            quantidade++;
        }
        atual = atual->proximo;
    }

    return quantidade;
}

void imprimirLivro(Livro livro) {
    printf("ID: %d\n", livro.id);
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Ano de Publicacao: %d\n\n", livro.anoPublicacao);
}

void imprimirLista(ListaEncadeada* lista) {
    No* atual = lista->inicio;

    while (atual != NULL) {
        imprimirLivro(atual->livro);
        atual = atual->proximo;
    }
}

int main() {
    ListaEncadeada lista;
    inicializarLista(&lista);

    Livro livro1 = { "Livro A", "Autor 1", 2000, 1 };
    Livro livro2 = { "Livro B", "Autor 2", 1995, 2 };
    Livro livro3 = { "Livro C", "Autor 1", 2010, 3 };
    Livro livro4 = { "Livro D", "Autor 3", 2005, 4 };

    inserirLivro(&lista, livro1);
    inserirLivro(&lista, livro2);
    inserirLivro(&lista, livro3);
    inserirLivro(&lista, livro4);

    printf("Lista de Livros:\n");
    imprimirLista(&lista);

    int idRemover;
    printf("Digite o ID do livro a ser removido: ");
    scanf("%d", &idRemover);
    removerLivro(&lista, idRemover);
    printf("Lista de Livros apos a remocao do livro com ID %d:\n", idRemover);
    imprimirLista(&lista);

    char autorBuscar[50];
    printf("Digite o nome do autor para buscar os livros: ");
    scanf("%s", autorBuscar);
    ListaEncadeada livrosAutor = listarLivrosPorAutor(&lista, autorBuscar);
    printf("Lista de Livros do Autor %s:\n", autorBuscar);
    imprimirLista(&livrosAutor);

    int idAtualizar, novoAno;
    printf("Digite o ID do livro a ser atualizado: ");
    scanf("%d", &idAtualizar);
    printf("Digite o novo ano de publicacao: ");
    scanf("%d", &novoAno);
    atualizarAnoPublicacao(&lista, idAtualizar, novoAno);
    printf("Lista de Livros apos a atualizacao do ano de publicacao do livro com ID %d:\n", idAtualizar);
    imprimirLista(&lista);

    char autorContar[50];
    printf("Digite o nome do autor para contar os livros: ");
    scanf("%s", autorContar);
    int quantidadeAutor = quantidadeLivrosPorAutor(&lista, autorContar);
    printf("Quantidade de Livros do Autor %s: %d\n", autorContar, quantidadeAutor);

    return 0;
}
