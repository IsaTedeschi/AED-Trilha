#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/*
void IniciaFila(TipoFila *fila){
   fila->inicio = NULL;
   fila->fim = NULL;
   fila->tamanho=0;
}

int Vazia(TipoFila *fila){
   return (fila->inicio == NULL);
}

void Enfileira(Registro x, TipoFila *fila){
   No *aux;
   aux = (No *) malloc(sizeof(No));
   aux->vert = x;
   aux->prox=NULL;
   if (Vazia(fila)){
      fila->inicio=aux;
      fila->fim=aux;
   }
   else {
      fila->fim->prox = aux;
      fila->fim = aux;
   }
   fila->tamanho++;
}

Registro Desenfileira(TipoFila *fila){
   No *q;
   Registro v;

   q = fila->inicio;
   v = fila->inicio->valor;
   fila->inicio = fila->inicio->prox;
   free(q);
   fila->tamanho--;
   return v;
}*/
