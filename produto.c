#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "produto.h"
#include "util.h"

/* ---------- Exibe os dados de um unico produto ---------- */
void exibirProduto(struct Produto p, struct Categoria categorias[], int totalCategorias) {
    int pos;

    printf("Codigo: %d\n", p.codigo);
    printf("Nome: %s\n", p.nome);

    pos = buscarCategoriaPorCodigo(categorias, totalCategorias, p.categoriaCodigo);
    if (pos != -1) {
        printf("Categoria: %s\n", categorias[pos].nome);
    } else {
        printf("Categoria: desconhecida\n");
    }

    printf("Prateleira: %c\n", p.prateleira);
    printf("Preco unitario: %.2f\n", p.preco);
    printf("Quantidade em estoque: %d\n", p.quantidade);
    printf("Disponivel para venda: %d\n", p.disponivel);
}

/* ---------- Busca por codigo: devolve a posicao ou -1 ---------- */
int buscarPorCodigo(struct Produto lista[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* ---------- Busca por nome: devolve a posicao ou -1 ---------- */
int buscarPorNome(struct Produto lista[], int total, char nome[]) {
    int i;
    for (i = 0; i < total; i++) {
        if (strcmp(lista[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/* ---------- Cadastra um produto na proxima posicao livre ----------
   Devolve o novo total de produtos cadastrados. */
int cadastrarProduto(struct Produto lista[], int total, struct Categoria categorias[], int totalCategorias) {
    struct Produto p;

    if (total >= MAX_PRODUTOS) {
        printf("\nLista cheia! Limite de %d produtos atingido.\n", MAX_PRODUTOS);
        return total;
    }

    if (totalCategorias == 0) {
        printf("\nCadastre uma categoria antes de cadastrar produtos.\n");
        return total;
    }

    do {
        printf("\nCodigo do produto: ");
        scanf("%d", &p.codigo);
        if (validarNumeroPositivo(p.codigo) == 0) {
            printf("Codigo invalido! Digite um numero positivo.\n");
        } else if (buscarPorCodigo(lista, total, p.codigo) != -1) {
            printf("Ja existe um produto com esse codigo! Digite outro.\n");
            p.codigo = 0;
        }
    } while (validarNumeroPositivo(p.codigo) == 0);

    do {
        printf("Nome do produto: ");
        scanf(" %49[^\n]", p.nome);
        if (validarTextoPreenchido(p.nome) == 0) {
            printf("Nome invalido! Nao pode ficar em branco.\n");
        }
    } while (validarTextoPreenchido(p.nome) == 0);

    do {
        printf("Codigo da categoria: ");
        scanf("%d", &p.categoriaCodigo);
        if (buscarCategoriaPorCodigo(categorias, totalCategorias, p.categoriaCodigo) == -1) {
            printf("Categoria inexistente! Digite um codigo ja cadastrado.\n");
        }
    } while (buscarCategoriaPorCodigo(categorias, totalCategorias, p.categoriaCodigo) == -1);

    do {
        printf("Prateleira (A, B, C ou D): ");
        scanf(" %c", &p.prateleira);
        if (validarPrateleira(p.prateleira) == 0) {
            printf("Prateleira invalida! Use apenas A, B, C ou D.\n");
        }
    } while (validarPrateleira(p.prateleira) == 0);

    do {
        printf("Preco unitario: ");
        scanf("%f", &p.preco);
        if (validarPrecoPositivo(p.preco) == 0) {
            printf("Preco invalido! Digite um valor maior que zero.\n");
        }
    } while (validarPrecoPositivo(p.preco) == 0);

    do {
        printf("Quantidade em estoque: ");
        scanf("%d", &p.quantidade);
        if (validarNumeroNaoNegativo(p.quantidade) == 0) {
            printf("Quantidade invalida! Nao pode ser negativa.\n");
        }
    } while (validarNumeroNaoNegativo(p.quantidade) == 0);

    if (p.quantidade > 0) {
        p.disponivel = 1;
    } else {
        p.disponivel = 0;
    }

    p.ativo = 1;

    lista[total] = p;

    printf("\n===== RESUMO DO PRODUTO =====\n");
    exibirProduto(lista[total], categorias, totalCategorias);

    return total + 1;
}

/* ---------- Lista todos os produtos ativos ---------- */
void listarProdutos(struct Produto lista[], int total, struct Categoria categorias[], int totalCategorias) {
    int i, cont = 0;

    for (i = 0; i < total; i++) {
        if (lista[i].ativo == 1) {
            if (cont == 0) {
                printf("\n===== LISTA DE PRODUTOS =====\n");
            }
            cont++;
            printf("\n--- Produto %d ---\n", cont);
            exibirProduto(lista[i], categorias, totalCategorias);
        }
    }

    if (cont == 0) {
        printf("\nNenhum produto cadastrado.\n");
    }
}

/* ---------- Pesquisa: escolhe o tipo, busca e exibe ---------- */
void pesquisarProduto(struct Produto lista[], int total, struct Categoria categorias[], int totalCategorias) {
    int tipo, codigo, pos;
    char nome[50];

    printf("\n===== PESQUISAR PRODUTO =====\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
    printf("Escolha: ");
    scanf("%d", &tipo);

    if (tipo == 1) {
        printf("Codigo do produto: ");
        scanf("%d", &codigo);
        pos = buscarPorCodigo(lista, total, codigo);
    } else if (tipo == 2) {
        printf("Nome do produto: ");
        scanf(" %49[^\n]", nome);
        pos = buscarPorNome(lista, total, nome);
    } else {
        printf("\nOpcao invalida!\n");
        return;
    }

    if (pos != -1 && lista[pos].ativo == 0) {
        pos = -1;   /* produto removido nao aparece na pesquisa */
    }

    if (pos == -1) {
        printf("\nNenhum produto encontrado.\n");
    } else {
        printf("\n===== PRODUTO ENCONTRADO =====\n");
        exibirProduto(lista[pos], categorias, totalCategorias);
    }
}

/* ---------- Altera o estoque: entrada ou saida ----------
   A disponibilidade e sempre recalculada a partir da quantidade. */
void alterarEstoque(struct Produto lista[], int total) {
    int codigo, pos, tipo, qtd;

    printf("\n===== ALTERAR ESTOQUE =====\n");
    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    pos = buscarPorCodigo(lista, total, codigo);
    if (pos == -1 || lista[pos].ativo == 0) {
        printf("\nProduto nao encontrado. Voltando ao menu.\n");
        return;
    }

    printf("Produto: %s | Estoque atual: %d\n", lista[pos].nome, lista[pos].quantidade);

    do {
        printf("1 - Entrada\n");
        printf("2 - Saida\n");
        printf("Escolha: ");
        scanf("%d", &tipo);
        if (tipo != 1 && tipo != 2) {
            printf("Opcao invalida! Digite 1 ou 2.\n");
        }
    } while (tipo != 1 && tipo != 2);

    do {
        printf("Quantidade: ");
        scanf("%d", &qtd);
        if (validarNumeroPositivo(qtd) == 0) {
            printf("Quantidade invalida! Digite um numero maior que zero.\n");
        }
    } while (validarNumeroPositivo(qtd) == 0);

    if (tipo == 1) {
        lista[pos].quantidade = lista[pos].quantidade + qtd;
    } else {
        if (qtd > lista[pos].quantidade) {
            printf("\nSaida maior que o estoque atual (%d). Operacao nao realizada.\n", lista[pos].quantidade);
            return;
        }
        lista[pos].quantidade = lista[pos].quantidade - qtd;
    }

    /* recalcula a disponibilidade com a mesma regra do cadastro */
    if (lista[pos].quantidade > 0) {
        lista[pos].disponivel = 1;
    } else {
        lista[pos].disponivel = 0;
    }

    printf("\nEstoque atualizado com sucesso!\n");
    printf("Quantidade em estoque: %d\n", lista[pos].quantidade);
    printf("Disponivel para venda: %d\n", lista[pos].disponivel);
}

/* ---------- Remove um produto (exclusao logica) ----------
   O registro continua na lista, so muda ativo para 0. */
void removerProduto(struct Produto lista[], int total) {
    int codigo, pos;

    printf("\n===== REMOVER PRODUTO =====\n");
    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    pos = buscarPorCodigo(lista, total, codigo);
    if (pos == -1 || lista[pos].ativo == 0) {
        printf("\nProduto nao encontrado. Voltando ao menu.\n");
        return;
    }

    lista[pos].ativo = 0;
    printf("\nProduto \"%s\" removido com sucesso.\n", lista[pos].nome);
}
