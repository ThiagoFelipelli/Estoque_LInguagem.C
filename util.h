#ifndef UTIL_H
#define UTIL_H

/* Validacoes genericas: nenhuma depende da lista de produtos.
   Todas devolvem 1 se o valor e valido e 0 se nao e. */

int validarNumeroPositivo(int valor);      /* valor > 0  (ex.: codigo)      */
int validarNumeroNaoNegativo(int valor);   /* valor >= 0 (ex.: quantidade)  */
int validarPrecoPositivo(float valor);     /* valor > 0  (ex.: preco)       */
int validarTextoPreenchido(char texto[]);  /* tem pelo menos 1 caractere    */
int validarPrateleira(char prateleira);    /* apenas A, B, C ou D           */

#endif
