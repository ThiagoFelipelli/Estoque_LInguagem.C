#ifndef CATEGORIA_H
#define CATEGORIA_H

#include "produto.h"

int buscarCategoriaPorCodigo(struct Categoria categorias[], int total, int codigo);
void exibirCategoria(struct Categoria categoria);
int cadastrarCategoria(struct Categoria categorias[], int total);
void listarCategorias(struct Categoria categorias[], int total);
int menuCategorias(struct Categoria categorias[], int total);

#endif
