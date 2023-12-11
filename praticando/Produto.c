#include "produto.h"
#include <stdio.h>
#include <stdlib.h>


struct Produto{
    int id;
    char nome[100];
    float valor;
};

Produto cadastrar();
void PrintProduto(p p);
Produto alterar (Produto p);
Produto cadastrar();
void PrintProduto(Produto p);
Produto alterar(Produto p);

Produto* cadtastrar(){
    Produto *p=(Produto*) malloc (sizeof(produto));

    scanf("%d", &P->id);
    scanf("%f", &P->valor);
    scanf("%s", P->nome, stdin);

    return P;
}

int main(){
    Produto *p=cadastrar();

    return 0;
}

