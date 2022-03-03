#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

// CRIA UMA PILHA, SEU INICIO É VAZIO
Pilha IniciaPilha(void){
   return NULL;
}

// VERIFICA SE A PILHA ESTÁ VAZIA (return 1) OU NÃO (return 0)
int VaziaPilha(Pilha pilha){
    if(pilha == NULL){return 1;}

    return 0;
}

// DEIXA REGISTRADO EM X QUAL É O TOPO DA PILHA, O ÚLTIMO ADICIONADO
Registro Topo(Pilha pilha){
   Registro x;

    // TOPO É O ÚLTIMO VALOR
   x = pilha->vert;
   return x;
}

// ADICIONA UM VALOR A PILHA
int Empilha(Pilha *pilha, Registro x){
    if(pilha == NULL)
        return 0;

    //CIRA O AUX - ELE RECEBE O VALOR QUE VAI SER ADICIONADO
    struct No* aux = (struct No*)malloc(sizeof(struct No));

    // O ÚLTIMO DA PILHA APONTA PARA O X
    aux->vert = x;
    // O PROX APONTA PARA O QUE TAVA NO TOPO ANTES
    aux->prox = *pilha;
    // O TOPO COMEÇA A APONTAR PARA O AUX
    *pilha = aux;
    return 1;
}

// ELIMINA O ELEMENTO DO TOPO
Registro Desempilha(Pilha *pilha){

    Registro x;
    Registro aux2;

    // CRIA UM AUX QUE VAI SER O REGISTRO A SER RETIRADO
    struct No* aux;

    // AUX RECEBE O TOPO DA PILHA
    aux = *pilha;
    // X É O VALOR DO ELEMENTO A SER RETIRADO
    x = aux->vert;
    // O PROX VAI PARA O DEPOIS DO TOPO
    *pilha = aux->prox;

    // PASSA PARA O REGISTRO AUX, PARA PODER RETORNAR ELE
    strcpy(aux2.nome, aux->vert.nome);
    strcpy(aux2.tipo, aux->vert.tipo);
    strcpy(aux2.acao, aux->vert.acao);

    // ELEMINA O ANTIGO TOPO
    free(aux);

   return aux2;
}

// APAGA TODA PILHA
int EsvaziaPilha(Pilha *pilha){
    if(pilha == NULL){return 0;}
    if(VaziaPilha(*pilha)==1){return 0;}

    // PASSA POR TODOS OS ELEMENTOS DA PILHA APAGANDO ELES
    while((*pilha) != NULL){
        Pilha aux = *pilha;
        (*pilha) = (*pilha)->prox;
        free(aux);
    }

    return 1;
}


