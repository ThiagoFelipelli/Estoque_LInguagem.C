#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 50
#define MAX_CATEGORIAS 20

struct Categoria {
    int codigo;
    char nome[50];
};

struct Produto {
    int codigo;
    int categoriaCodigo;
    char nome[50];
    char prateleira;
    float preco;
    int quantidade;
    int disponivel;
    int ativo;          /* 1 = normal, 0 = removido (exclusao logica) */
};

void exibirProduto(struct Produto p, struct Categoria categorias[], int totalCategorias);
int cadastrarProduto(struct Produto lista[], int total, struct Categoria categorias[], int totalCategorias);
void listarProdutos(struct Produto lista[], int total, struct Categoria categorias[], int totalCategorias);
int buscarPorCodigo(struct Produto lista[], int total, int codigo);
int buscarPorNome(struct Produto lista[], int total, char nome[]);
void pesquisarProduto(struct Produto lista[], int total, struct Categoria categorias[], int totalCategorias);
void alterarEstoque(struct Produto lista[], int total);
void removerProduto(struct Produto lista[], int total);

#endif
