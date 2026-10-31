#include <stdio.h>
#include <string.h>
#include "util.h"

/* ---------- Numero maior que zero ---------- */
int validarNumeroPositivo(int valor) {
    if (valor > 0) {
        return 1;
    }
    return 0;
}

/* ---------- Numero maior ou igual a zero ----------
   Funcao diferente da anterior: quantidade em estoque aceita zero. */
int validarNumeroNaoNegativo(int valor) {
    if (valor >= 0) {
        return 1;
    }
    return 0;
}

/* ---------- Preco maior que zero ---------- */
int validarPrecoPositivo(float valor) {
    if (valor > 0) {
        return 1;
    }
    return 0;
}

/* ---------- Texto com pelo menos um caractere ---------- */
int validarTextoPreenchido(char texto[]) {
    if (strlen(texto) > 0) {
        return 1;
    }
    return 0;
}

/* ---------- Prateleira: apenas A, B, C ou D ---------- */
int validarPrateleira(char prateleira) {
    if (prateleira == 'A' || prateleira == 'B' ||
        prateleira == 'C' || prateleira == 'D') {
        return 1;
    }
    return 0;
}
