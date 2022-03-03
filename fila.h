#include "no.h"

typedef struct Fila{
   No *inicio, *fim;
   int tamanho;
} TipoFila;


void IniciaFila(TipoFila *fila);
int Vazia(TipoFila *fila);
void Enfileira(Registro x, TipoFila *fila);
Registro Desenfileira(TipoFila *fila);
