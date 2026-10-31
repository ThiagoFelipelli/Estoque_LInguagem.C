/* Tarefa 5: Sistema de Estoque (alterar estoque e remover produto)
   main.c: mostra o menu e chama as funcoes de produto e categoria */

#include <stdio.h>
#include "produto.h"
#include "categoria.h"

int main() {
    struct Produto lista[MAX_PRODUTOS];
    struct Categoria categorias[MAX_CATEGORIAS];
    int total = 0;
    int totalCategorias = 0;
    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Pesquisar Produto\n");
        printf("4 - Alterar Estoque de um Produto\n");
        printf("5 - Remover Produto\n");
        printf("6 - Categorias\n");
        printf("7 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            total = cadastrarProduto(lista, total, categorias, totalCategorias);
        } else if (opcao == 2) {
            listarProdutos(lista, total, categorias, totalCategorias);
        } else if (opcao == 3) {
            pesquisarProduto(lista, total, categorias, totalCategorias);
        } else if (opcao == 4) {
            alterarEstoque(lista, total);
        } else if (opcao == 5) {
            removerProduto(lista, total);
        } else if (opcao == 6) {
            totalCategorias = menuCategorias(categorias, totalCategorias);
        } else if (opcao == 7) {
            printf("\nSaindo do sistema...\n");
        } else {
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 7);

    return 0;
}
