#include "no.h"
#include "registro.h"


typedef struct No* Pilha;

Pilha IniciaPilha();
int VaziaPilha(Pilha pilha);
Registro Topo(Pilha pilha);
int Empilha(Pilha *pilha, Registro x);
Registro Desempilha(Pilha *pilha);
int EsvaziaPilha(Pilha *pilha);
