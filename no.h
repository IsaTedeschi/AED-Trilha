#ifndef __NO_H_INCLUDED__
#define __NO_H_INCLUDED__

#include "registro.h"

typedef struct No{
   Registro vert;
   struct No *prox;
} No;

#endif
