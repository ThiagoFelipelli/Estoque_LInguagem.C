#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

int buscarCategoriaPorCodigo(struct Categoria categorias[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (categorias[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void exibirCategoria(struct Categoria categoria) {
    printf("Codigo: %d\n", categoria.codigo);
    printf("Nome: %s\n", categoria.nome);
}

int cadastrarCategoria(struct Categoria categorias[], int total) {
    struct Categoria categoria;

    if (total >= MAX_CATEGORIAS) {
        printf("\nLista de categorias cheia! Limite de %d categorias atingido.\n", MAX_CATEGORIAS);
        return total;
    }

    do {
        printf("\nCodigo da categoria: ");
        scanf("%d", &categoria.codigo);
        if (categoria.codigo <= 0) {
            printf("Digite o codigo da categoria:");
        } else if (buscarCategoriaPorCodigo(categorias, total, categoria.codigo) != -1) {
            printf("Ja existe uma categoria com esse codigo! Digite outro.\n");
            categoria.codigo = -1;
        }
    } while (categoria.codigo <= 0);

    do {
        printf("Nome da categoria: ");
        scanf(" %49[^\n]", categoria.nome);
        if (strlen(categoria.nome) == 0) {
            printf("Nome invalido! Nao pode ficar em branco.\n");
        }
    } while (strlen(categoria.nome) == 0);

    categorias[total] = categoria;
    printf("\nCategoria cadastrada com sucesso.\n");
    return total + 1;
}

void listarCategorias(struct Categoria categorias[], int total) {
    int i;

    if (total == 0) {
        printf("\nNenhuma categoria cadastrada.\n");
        return;
    }

    printf("\n===== LISTA DE CATEGORIAS =====\n");
    for (i = 0; i < total; i++) {
        printf("\n--- Categoria %d ---\n", i + 1);
        exibirCategoria(categorias[i]);
    }
}

/* ---------- Submenu de categorias ----------
   Devolve o novo total de categorias. */
int menuCategorias(struct Categoria categorias[], int total) {
    int opcao;

    do {
        printf("\n===== CATEGORIAS =====\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Listar Categorias\n");
        printf("3 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            total = cadastrarCategoria(categorias, total);
        } else if (opcao == 2) {
            listarCategorias(categorias, total);
        } else if (opcao == 3) {
            printf("\nVoltando ao menu principal...\n");
        } else {
            printf("\nOpcao invalida!\n");
        }
    } while (opcao != 3);

    return total;
}
