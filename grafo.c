#include "grafo.h"
#include "pilha.h"
#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// CRIAÇÃO DO GRAFO
Grafo criarGrafo() {

   Grafo G;
   G = (Grafo) malloc(sizeof (Grafo));
   if (G!=NULL){
     G->NumArco = 0; // NÚMERO DE ARESTAS
     G->NumVert = 0; // NÚMERO DE VÉRTICES
     G->vertices = NULL;
   }
   return G;
}

// CRIAÇÃO DO GRAFO TRANSPOSTO
Grafo criarGrafoTransposto(Grafo G){
    Grafo Gt;
    Gt = (Grafo) malloc(sizeof (Grafo));
    if (Gt!=NULL){
        Gt->NumArco = 0;
        Gt->NumVert = 0;
        Gt->vertices = NULL;
    }

    Registro aux;
    struct noVert *nv;
    struct noAdj *na;

    Registro aux1;
    Registro aux2;
    int pesoAux;

    // OS VÉRTICES SÃO IGUAIS DO GRAFO TRANSPOSTO E GRAFO
    // ELES SÃO COPIADOS DO GRAFO PARA O TRANSPOSTO
    for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
        strcpy(aux.nome, nv->vert.nome);
        strcpy(aux.tipo, nv->vert.tipo);
        strcpy(aux.acao, nv->vert.acao);
        inserirNovoVertice(Gt, aux);
    }

    // TROCA A DIREÇÃO DAS ARESTAS PARA FAZER UM GRAFO TRANSPOSTO
    for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
        if(nv->ladj == NULL)
            continue;
        // AUX1 É O VERT QUE ATUALMENTE É A PRIMEIRA PONTA DA ARESTA
        strcpy(aux1.nome, nv->vert.nome);
        strcpy(aux1.tipo, nv->vert.tipo);
        strcpy(aux1.acao, nv->vert.acao);
        for (na = nv->ladj; na != NULL; na = na->prox){
            // AUX2 É O VERT QUE FICA DO OUTRO LADO DA PONTA DA ARESTA
            strcpy(aux2.nome, na->vert.nome);
            strcpy(aux2.tipo, na->vert.tipo);
            strcpy(aux2.acao, na->vert.acao);
            pesoAux = na->peso;
            // O ARCO É CRIADO COM A DIREÇÃO OPOSTA QUE ERA ANTES
            inserirArco(Gt, aux2, aux1, pesoAux);
        }
    }

    //GRAFO TRANSPOSTO É CRIADO
    return Gt;
}



// VERIFICA SE O VÉRTICE QUANDO ADICIONADO JÁ EXISTE
int verificaVertice(Grafo G, Registro x){
   if (G == NULL)
      return -1;

   struct noVert* confere;

   for(confere = G->vertices; confere != NULL; confere = confere->prox){
      if(strcmp(confere->vert.nome, x.nome)==0 && strcmp(confere->vert.tipo, x.tipo)==0 && strcmp(confere->vert.acao, x.acao)==0)
         return 0; //ENCONTROU UM IGUAL - JÁ EXISTE
   }

   return 1; // NÃO TEM IGUAL - É NOVO
}

// CONFERE SE O ID DO VÉRTICE JÁ EXISTE
int confere_id(Grafo G, int x){
    if (G == NULL)
      return -1;

    int num;
    num = G->NumVert - 1;

    // ID NÃO PODE SER MAIOR QUE A QUANTIDADE DE VÉRTICES OU NEGATIVO
    if(x > num || x < 0)
        return 0; // ID ERRADO
    else
        return 1; // ID EXISTE

}

// QUANDO É REMOVIDO UM VÉRTICE, É NECESSÁRIO ARRUMAR OS ID'S
int arruma_id(Grafo G, int id){
    if (G == NULL)
      return -1;

    struct noVert* aux;
    struct noAdj* aux2;

    // PASSA POR TODOD VERTS DA LISTA NOVERT PARA ARRUMAR OS ID'S
    for(aux = G->vertices; aux != NULL; aux = aux->prox){
        if(aux->id > id)
            aux->id--;
        for(aux2 = aux->ladj; aux2 != NULL; aux2 = aux2->prox ){
            if(aux2->id > id)
                aux2->id --;
        }
    }

    return 1;
}

// ACHA AS INFORMAÇÕES DO VÉRTICE DE ACORDO COM O NÚMERO DO ID DADO
Registro acha_vertice(Grafo G, int x){

    Registro vert;
    struct noVert *aux;

    aux = G->vertices;
    while(aux->prox != NULL){
        if(aux->id == x){
            // PASSA PELA LISTA NOVERT ATÉ ACHAR O ID, VERT RECEBE AS INFORMAÇÕES DO VÉRTICE DESSE ID
            strcpy(vert.nome, aux->vert.nome);
            strcpy(vert.tipo, aux->vert.tipo);
            strcpy(vert.acao, aux->vert.acao);
            break;
        }
        aux = aux->prox;
    }
    if(aux->prox == NULL && aux->id == x){
        strcpy(vert.nome, aux->vert.nome);
        strcpy(vert.tipo, aux->vert.tipo);
        strcpy(vert.acao, aux->vert.acao);
    }

    //RETORNA AS INFORMAÇÕES DO VÉRTICE
    return vert;
}

// RECEBE UM VÉRTICE E RETORNA SEU ID
int acha_id(Grafo G, Registro x){
    if(G == NULL)
        return -1;

    struct noVert* aux;

    // PASSA PELOS VÉRTICES E QUANDO ACHA, RETORNA SEU ID
    for(aux = G->vertices; aux != NULL; aux = aux->prox){
        if(strcmp(aux->vert.nome, x.nome)==0 && strcmp(aux->vert.tipo, x.tipo)==0 && strcmp(aux->vert.acao, x.acao)==0)
            return aux->id;
    }

    return -5;
}



// INSERE VÉRTICE E ALOCA ELE
struct noVert* inserirVertice(struct noVert *ini, Registro x, int num){
  struct noVert* novoVertice;
  novoVertice = (struct noVert*) malloc (sizeof(struct noVert));
  novoVertice->vert = x;
  novoVertice->prox = ini;
  novoVertice->id = num;
  novoVertice->ladj = NULL;
  return novoVertice;
}

// INSERE NOVO VÉRTICE
int inserirNovoVertice(Grafo G, Registro nv){
    if (G == NULL)
      return -1;

    //CONFIRMA QUE ELE AINDA NÃO EXISTE
    if(verificaVertice(G, nv) == 0)
      return 0;

    // SE É O PRIMEIRO VÉRTICE ALOCADO, ELE TEM ID = 0
    int id;
    if(G->vertices == NULL)
        id = 0;
    else // G->VERTICES->ID CONTÉM O ÚLTIMO NÚMERO ADICIONADO - TEM QUE SEMPRE ADICIONAR UM
        id = G->vertices->id + 1;

    G->vertices = inserirVertice(G->vertices,nv,id);
    G->NumVert++;

    return 1;
}

// REMOVE VÉRTICE
int removerVertice(Grafo G, Registro x, int id){
    if (G == NULL)
      return -1;

    if(verificaVertice(G, x) == 1){
      return 5;
    }

    struct noVert *nv;
    struct noVert *aux;
    struct noVert *aux2;

    struct noAdj *aux3;
    struct noAdj *aux4;

    // CASO1: O PRIMEIRO VÉRTICE É O QUE TEM QUE SER RETIRADO
    if(strcmp(G->vertices->vert.nome, x.nome)==0 && strcmp(G->vertices->vert.tipo, x.tipo)==0 && strcmp(G->vertices->vert.acao, x.acao)==0){
        aux = G->vertices;
        G->vertices = aux->prox;

        // É REMOVIDO TODOS SEUS ADJACENTES
        while(aux->ladj != NULL){
            aux3 = aux->ladj;
            aux->ladj = aux3->prox;
            free(aux3);
            G->NumArco--;
        }

        free(aux);
        G->NumVert--;
    }
    else{
        // CASO2: VÉRTICE NÃO É O PRIMEIRO A SER RETIRADO
        aux = G->vertices;
        while(aux->prox != NULL){
            // PROCURA O QUE VAI SER RETIRADO
            if(strcmp(aux->prox->vert.nome, x.nome)==0 && strcmp(aux->prox->vert.tipo, x.tipo)==0 && strcmp(aux->prox->vert.acao, x.acao)==0){
                aux2 = aux->prox;
                // OS ADJACENTES TAMBÉM SÃO RETIRADOS
                 while(aux2->ladj != NULL){
                    aux3 = aux2->ladj;
                    aux2->ladj = aux3->prox;
                    free(aux3);
                    G->NumArco--;
                }
                aux->prox = aux2->prox;
                free(aux2);
                G->NumVert--;
            }
            else{
                aux = aux->prox;
            }
        }
    }

    // RETIRA TODA APARIÇÃO DELE NA LISTA NOADJ
    for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
        if(nv->ladj == NULL)
            continue;

        // CASO1: ELE SEJA O PRIMEIRO DA LISTA DE ADJACENCIA
        if(strcmp(nv->ladj->vert.nome, x.nome)==0 && strcmp(nv->ladj->vert.tipo, x.tipo)==0 && strcmp(nv->ladj->vert.acao, x.acao)==0){
            aux3 = nv->ladj;
            nv->ladj = aux3->prox;
            free(aux3);
            G->NumArco--;
        }
        else{
            // CASO2: SE ELE NÃO FOR O PRIMEIRO
            aux3 = nv->ladj;
            while(aux3->prox != NULL){
                // QUANDO É ACHADO, RETIRA O VÉRTICE
                if(strcmp(aux3->prox->vert.nome, x.nome)==0 && strcmp(aux3->prox->vert.tipo, x.tipo)==0 && strcmp(aux3->prox->vert.acao, x.acao)==0){
                    aux4 = aux3->prox;
                    aux3->prox = aux4->prox;
                    free(aux4);
                    G->NumArco--;
                }
                else{
                    aux3 = aux3->prox;
                }
            }
        }
    }

    // COMO FOI RETIRADO UM ID, A LISTA TEM QUE SER ARRUMADA
    arruma_id(G, id);
    return 1;
}

// REMOVE VÉRTICE AUXILIAR - QUANDO É PASSADO UM ID E QUER APAGAR UM VÉRTICE
Registro removerVertice2(Grafo G, int x){

    Registro vert;
    //DE ACORDO COM O ID CONSEGUE ACHAR O VÉRTICE ADEQUADO
    vert = acha_vertice(G, x);

    //É LEVADO PARA A FUNÇÃO PRINCIPAL PARA SER REMOVIDO
    removerVertice(G, vert, x);

    //RETORNA O VÉRTICE REMOVIDO
    return vert;
}



// ADICIONA ARESTA
int inserirArco(Grafo G, Registro v1, Registro v2, int peso) {

   if (G == NULL)
      return -1;

    // CONFIRMA QUE OS VÉRTICES EXISTEM
    if(verificaVertice(G, v1) == 1)
        return 5;
    if(verificaVertice(G, v2) == 1)
        return 5;

    int id = acha_id(G, v2);


    struct noVert *v;
    struct noAdj *z;
    // PASSA POR TODOS DA LISTA NOVERT ATÉ ACHAR A PRIMEIRA PONTA DA ARESTA
    for (v = G->vertices; v != NULL; v = v->prox){
        //QUANDO ACHA A PRIMEIRA PONTA, TEM QUE PASSAR POR SUAS ADJACENCIAS PARA TER CERTEZA QUE O ARCO NÃO EXISTE
        if (strcmp(v->vert.nome, v1.nome) == 0 && strcmp(v->vert.tipo, v1.tipo) == 0 && strcmp(v->vert.acao, v1.acao) == 0) { // achou o vértice para inserir a adjacência
            for(z = v->ladj; z!= NULL; z = z->prox){
                if (strcmp(z->vert.nome, v2.nome)==0 && strcmp(z->vert.tipo, v2.tipo)==0 && strcmp(z->vert.acao, v2.acao)==0)
                    return 0;  // o arco já existe, retornar!
            }
            //CASO NÃO EXISTA, ELE ADICIONA NO INICIO A OUTRA PONTA DA ARESTA
            struct noAdj *novo = (struct noAdj*) malloc(sizeof (struct noAdj));
            if(novo == NULL) return 0;

            novo->prox = v->ladj;
            v->ladj = novo;
            novo->peso = peso;
            novo->vert = v2;
            novo->id = id;
            G->NumArco++;


            return 1;
        }
    }

   return 10;
}

// ADICIONA ARESTA AUXILIAR - RECEBE DOIS ID'S E CRIA A ARESTA
int inserirArco2(Grafo G, int v1, int v2, int peso){
    if(G == NULL)
        return -1;

    Registro vert1;
    Registro vert2;

    // DADO UM ID PROCURA QUAL É O VÉRTICE REFERIDO
    vert1 = acha_vertice(G, v1);
    vert2 = acha_vertice(G, v2);

    //MANDA PARA FUNÇÃO PRINCIPAL, PARA ADICIONAR O ARCO
    inserirArco(G, vert1, vert2, peso);

    //IMPRIME QUAIS VÉRTICES FORAM CONECTADOS
    printf("%s foi conectado a %s!", vert2.nome, vert1.nome);
    return 1;

}

// REMOVE ARCO
int removerArco(Grafo G, Registro x, Registro y){
    if (G == NULL)
        return -1;

    struct noVert *nv;
    struct noAdj *na;
    struct noAdj *aux;
    struct noAdj *aux2;

    // PASSA PELA LISTA DO NOVERT PROCURANDO O PRIMEIRO VÉRTICE
    for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
        // CASO ACHE QUAL É A PRIMEIRA DA ARESTA, PASSA PELAS ADJACENCIAS PROCURANDO O SEGUNDO VÉRTICE
        if (strcmp(nv->vert.nome, x.nome)==0 && strcmp(nv->vert.tipo, x.tipo)==0 && strcmp(nv->vert.acao, x.acao)==0){
            // CASO O SEGUNDO VÉRTICE SEJA LOGO O PRIMEIRO - É RETIRADO
            if(strcmp(nv->ladj->vert.nome, y.nome)==0 && strcmp(nv->ladj->vert.tipo, y.tipo)==0 && strcmp(nv->ladj->vert.acao, y.acao)==0){
                aux = nv->ladj;
                nv->ladj = aux->prox;
                free(aux);
                G->NumArco--;
                return 1;
            }
            // CASO O SEGUNDO VÉRTICE ESTEJA NO MEIO/FIM DA LISTA - É FEITA AS ALTERAÇÕES E É RETIRADO
            for (na = nv->ladj; na != NULL; na = na->prox){
                if(strcmp(na->prox->vert.nome, y.nome)==0 && strcmp(na->prox->vert.tipo, y.tipo)==0 && strcmp(na->prox->vert.acao, y.acao)==0){
                    aux2 = na->prox;
                    na->prox = aux2->prox;
                    free(aux2);
                    G->NumArco--;
                    // RETORNA 1 PARA CASO DE SUCESSO EM RETIRAR A ARESTA
                    return 1;
                }
            }
            return 0;
        }

    }
    //RETORNA 0 EM CASO DE FALHA
    return 0;
}

// REMOVE ARCO AUXILIAR - RECEBE DOIS ID'S E REMOVE A ARESTA
int removerArco2(Grafo G, int v1, int v2){
    if(G == NULL)
        return -1;

    int retorno;

    Registro vert1;
    Registro vert2;

    // PROCURA PELOS VÉRTICES RESPECTIVOS, DADO O ID
    vert1 = acha_vertice(G, v1);
    vert2 = acha_vertice(G, v2);

    retorno = removerArco(G, vert1, vert2);

    if (retorno == 1){
        printf("\n%s foi desconectado a %s!\n", vert2.nome, vert1.nome);
        return 1;
    }

    return 0;

}



// FUNÇÃO QUE DADO AS INFORMAÇÕES DE UM VÉRTICE RETORNA QUAL SEU GRAU
int grauVertice(Grafo G, Registro v) {
    if(G == NULL)
      return 0;


    struct noVert *nv;
    struct noAdj *na;
    int cont = 0;

    // PASSA PELOS VÉRTICES DA LISTA NOVERT
    for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
        // QUANDO ACHAR O VÉRTICE QUE QUER, PASSA PELOS VÉRTICES DE ADJACENCIA E CONTA ELES - GRAU DE SAÍDA
        if(strcmp(v.nome, nv->vert.nome)==0 && strcmp(v.tipo, nv->vert.tipo)==0 && strcmp(v.acao, nv->vert.acao)==0){
            for (na = nv->ladj; na != NULL; na = na->prox){
                cont = cont + 1;  // GRAU DE SAÍDA
            }
        }
        // PASSA POR TODAS AS ADJACENCIAS PARA SABER ONDE ELE APARECE, QUANTAS VEZES ELE APARECER É O GRAU DE ENTRADA
        else{
            for (na = nv->ladj; na != NULL; na = na->prox)
                if(strcmp(v.nome, nv->vert.nome) == 0 && strcmp(v.tipo, nv->vert.tipo) == 0 && strcmp(v.acao, nv->vert.acao) == 0)
                cont = cont + 1; // GRAU DE ENTRADA
        }
    }
    // RETORNA O GRAU
    return cont;
}

// RETORNA UM DOS VÉRTICES COM MAIOR GRAU
Registro maior_grau(Grafo G){

    struct noVert *nv;
    Registro aux;
    int maior = -1;
    int num_grau;

    //PASSA POR TODOS OS VÉRTICES E ANALISA SEU MAIOR FAZENDO AS COMPARAÇÕES ENTRE ELES
    for(nv = G->vertices; nv!=NULL; nv = nv->prox) {
        num_grau = grauVertice(G, nv->vert);
        if(num_grau > maior){
            maior = num_grau;
            aux = nv->vert;
        }
    }

    //IMPRIME O VALOR DO MAIOR GRAU
    printf("%d", maior);
    //RETORNA UM DOS REGISTROS COM MAIOR GRAU
    return aux;
}



// IMPRIME A LISTA
void imprimirListaAdj(Grafo G) {
    if (G == NULL) return;

    struct noVert *nv;
    struct noAdj *na;

    // PASSA POR TODOS OS VÉRTICES E ADJACENCIAS, IMPRIMINDO TODOS
    printf("\n\nLista de Adjacencias:");
    for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
      printf("\n(id = %d) Nome: %s - Tipo: %s - Acao: %s:  ",nv->id, nv->vert.nome, nv->vert.tipo, nv->vert.acao);
      for (na = nv->ladj; na != NULL; na = na->prox){
          printf("(Nome: %s - id:%d)",na->vert.nome, na->id);

      }
      printf("\n");
    }
}



// MARCA SE O VÉRTICE JÁ FOI VISITADO, PARA AUXILIAR NA BUSCA EM PROFUNDIDADE
int FoiVisitado(Pilha pilha, Registro v){
    struct No* aux;

    // SE O VÉRTICE JÁ TIVER SIDO VISITADO, RETORNA 1
    for (aux = pilha; aux != NULL; aux = aux->prox){
        if(strcmp(v.nome, aux->vert.nome)==0 && strcmp(v.tipo, aux->vert.tipo)==0 && strcmp(v.acao, aux->vert.acao)==0)
            return 1;
    }
    //CASO CONTRÁRIO RETORNA 0
    return 0;
}

// FUNÇÃO PRINCIPAL, QUE DADO DOIS REGISTROS, DESCOBRE SE TEM CAMINHO ENTRE ELES
int BuscaEmProfundidade (Grafo G, Registro v1, Registro v2) {
    if(G == NULL)
      return 0;

    struct noVert *nv;
    struct noAdj *na;

    int cont = 0;

    // VAI TER DUAS PILHAS
    Pilha pilha = IniciaPilha();
    Pilha visitados = IniciaPilha();

    Registro vt;

    if(Empilha(&pilha, v1)==0){
      return 0;
   }

    while(!VaziaPilha(pilha)){
        vt = Desempilha(&pilha);
        if (FoiVisitado(visitados, vt)==0){
            if(Empilha(&visitados, vt)==0){
               EsvaziaPilha(&pilha);
               EsvaziaPilha(&visitados);
               return 0;
            }
        }

        cont++;
        for (nv = G->vertices; nv!=NULL; nv = nv->prox){
            if(strcmp(vt.nome, nv->vert.nome)==0){
                for (na = nv->ladj; na != NULL; na = na->prox){
                    if(strcmp(v2.nome, na->vert.nome)==0 && strcmp(v2.tipo, na->vert.tipo)==0 && strcmp(v2.acao, na->vert.acao)==0){
                        return 1;
                    }
                    if (FoiVisitado(visitados, na->vert)==0){
                        if(!Empilha(&pilha, na->vert)){
                            EsvaziaPilha(&pilha);
                            EsvaziaPilha(&visitados);
                            return 0;
                        }
                    }
                continue;
                }
            }
        }
   }

   return 0;
}

// FUNÇÃO AUXILIAR - DADO DOIS ID'S CHAMA A FUNÇÃO PRINCIPAL PARA SABER SE EXISTE CAMINHO ENTRE ELES
int ExisteCaminho(Grafo G, int v1, int v2){
    if(G == NULL)
        return -1;

    int retorno;

    Registro vert1;
    Registro vert2;

    // PROCURA PELOS VÉRTICES RESPECTIVOS, DADO O ID
    vert1 = acha_vertice(G, v1);
    vert2 = acha_vertice(G, v2);

    retorno = BuscaEmProfundidade(G, vert1, vert2);

    if (retorno == 1){
        return 1;
    }

    return 0;
}



// FUNÇÃO QUE IMPRIME OS ELEMENTOS FORTEMENTE CONECTADOS
int BuscaEmProfundidade2 (Grafo Gt, Registro v, int vetor[]) {

    struct noVert *nv;
    struct noAdj *na;

    Pilha pilha = IniciaPilha();
    Pilha visitados = IniciaPilha();

    int cont = 0;
    int id;

    Registro vt;

    id = acha_id(Gt, v);
    if(vetor[id]==1)
        return 0;
    else
        vetor[id]=1;

   //Iniciar a fila e inserir o vértice de origem
   if(Empilha(&pilha, v)==0){
      return 0;
   }

   // POR MEIO DO GRAFO TRANSPOSTO E A FUNÇÃO DE BUSCA EM PROFUNDIDADE, É ENCONTRADO OS ELEMENTOS FORTEMENTE CONECTADOS
    while(!VaziaPilha(pilha)){
        vt = Desempilha(&pilha);
        if (FoiVisitado(visitados, vt)==0){
            if(Empilha(&visitados, vt)==0){
               EsvaziaPilha(&pilha);
               EsvaziaPilha(&visitados);
               return 0;
            }
        }

        cont++;
        for (nv = Gt->vertices; nv!=NULL; nv = nv->prox){
            if(strcmp(vt.nome, nv->vert.nome)==0 && strcmp(vt.tipo, nv->vert.tipo)==0 && strcmp(vt.acao, nv->vert.acao)==0){
                for (na = nv->ladj; na != NULL; na = na->prox){
                    id = acha_id(Gt, na->vert);
                    if(vetor[id]==0){
                        if (FoiVisitado(visitados, na->vert)==0){
                            Empilha(&pilha, na->vert);

                            if(!Empilha(&pilha, na->vert)){
                                EsvaziaPilha(&pilha);
                                EsvaziaPilha(&visitados);
                                return 0;
                            }
                        }
                        vetor[id] = 1;
                    }
                    else
                        continue;
                continue;
                }
            }
        }
   }


    Pilha aux2;
    printf("\n\n");


    // IMPRESSÃO DOS CONJUNTOS
    for (aux2 = visitados; aux2 != NULL; aux2 = aux2->prox){
        printf("(%s) ", aux2->vert.nome);
    }

    free(pilha);
    return 1;
}

// O VETOR FORMADO PELA FUNÇÃO BUSCA EM PROFUNDIDADE TEMPO É ORDENADO DE FORMA CRESCENTE E COLOCADO EM UMA PILHA
Pilha OrdenaTempo(Grafo G, struct visitaTempo *vet, int tam){
    int i,j;
    int indice;
    Registro aux;

    Pilha pilha;
    pilha = IniciaPilha();

    /*
        // IMPRIME AS DESCOBERTAS DOS VÉRTICES
    int id;
    for (i = 0; i<tam; i++){
        printf("\n(%s) Descoberta: %d, Finalizacao: %d",
        vet[i].vert.nome , vet[i].tempoDescoberta, vet[i].tempoFinalizacao);
        strcpy(aux.nome, vet[i].vert.nome);strcpy(aux.tipo, vet[i].vert.tipo);strcpy(aux.acao, vet[i].vert.acao);
        id = acha_id(G, aux);
        vet[i].id = id;
    }
    */

    // ORDENAÇÃO DO VETOR, POR ORDEM CRESCENTE
    int menor;
    for(i=0; i<tam; i++){
        menor = 999999;
        for(j=0; j<tam; j++){
            if(vet[j].tempoFinalizacao < menor){
                menor = vet[j].tempoFinalizacao;
                indice = j;
            }
        }
        strcpy(aux.nome, vet[indice].vert.nome);strcpy(aux.tipo, vet[indice].vert.tipo);strcpy(aux.acao, vet[indice].vert.acao);
        Empilha(&pilha, aux);
        vet[indice].tempoFinalizacao = 999999;
    }



    return pilha;
}

// MOSTRA SE O VÉRTICE JÁ FOI VISITADO - RETORNANDO 1 CASO SIM
int FoiVisitadoTempo(Registro vert, struct visitaTempo *vet, int tam){
  int i;
  for (i = 0; i<tam; i++){
    if(strcmp(vet[i].vert.nome, vert.nome)==0 && strcmp(vet[i].vert.tipo, vert.tipo)==0 && strcmp(vet[i].vert.acao, vert.acao )==0 && (vet[i].tempoDescoberta != -1))
       return 1;
  }
  return 0;
}

 // AJEITA O VETOR VET DE ACORDO COM SEU TEMPO DE FINALIZAÇÃO E DE DESCOBERTA
int MarcaVisitaTempo(Registro vt, int pos, char tipo, struct visitaTempo *vet, int tam){
  int i;
  for (i = 0; i<tam; i++){
    if(strcmp(vet[i].vert.nome, vt.nome)==0 && strcmp(vet[i].vert.tipo, vt.tipo)==0 && strcmp(vet[i].vert.acao, vt.acao)==0){
         if (tipo == 'D'){
             vet[i].tempoDescoberta = pos;
             return 1;
         }
         else{
             if (vet[i].tempoFinalizacao == -1){
                 vet[i].tempoFinalizacao = pos;
                 return 1;
             }
             else return 0;
         }
    }
  }
  return 0;
}

// INICIALIZA O VETOR VISITADOS, QUE DEPOIS VAI CONTER OS TEMPOS DE FINALIZAÇÃO E DE DESCOBERTA
void InicializaVisitados(Grafo G, struct visitaTempo** visitados){
    (*visitados) = (struct visitaTempo *) malloc (G->NumVert * sizeof (struct visitaTempo));
    int tam =0;

    struct noVert *nv;

    for (nv=G->vertices; nv!=NULL; nv=nv->prox){
        (*visitados)[tam].vert = nv->vert;
        (*visitados)[tam].tempoDescoberta = -1;
        (*visitados)[tam].tempoFinalizacao = -1;
        tam++;
    }
}

// REALIZA O PERCURSO PROFUNDIDADE TEMPO EM TODOS OS VÉRTICES PARA SABER QUAIS SÃO SEUS TEMPOS DE FINALIZAÇÃO
int PercursoProfundidadeTempo (Grafo G, Registro v, struct visitaTempo** visitados) {

    if(G == NULL)
        return 0;

    struct noVert *nv;
    struct noAdj *na;

    Pilha pilha;
    int finaliza, r;
    int tam = G->NumVert;

    Registro vt;

    int cont = 0;
    int i;

    // GARANTE QUE TODOS OS TEMPOS DE FINALIZAÇÃO ESTEJAM CORRETOS
    for(i=0; i<tam; i++){
        if((*visitados)[i].tempoDescoberta != -1){
            if((*visitados)[i].tempoFinalizacao > cont){
                cont = (*visitados)[i].tempoFinalizacao; // PEGAR O MAIOR TEMPO DE FINALIZAÇÃO
            }
        }
    }

    cont++;

    //INICIAR A FILA E INSERIR O VÉRTICE DE ORIGEM
    pilha = IniciaPilha();
    Empilha(&pilha,v);

    while(VaziaPilha(pilha)==0){
        vt = Topo(pilha);
        if (FoiVisitadoTempo(vt,(*visitados),tam)==0){
            MarcaVisitaTempo(vt, cont++, 'D', (*visitados),tam);
            //cont++;
            for (nv = G->vertices; nv!=NULL; nv = nv->prox)
                if(strcmp(vt.nome, nv->vert.nome)==0 && strcmp(vt.tipo, nv->vert.tipo)==0 && strcmp(vt.acao, nv->vert.acao)==0){
                    finaliza = 1;
                    for (na = nv->ladj; na != NULL; na = na->prox)
                        if (FoiVisitadoTempo(na->vert,(*visitados),tam)==0){
                            Empilha(&pilha, na->vert);
                            finaliza = 0;
                        }
                    if (finaliza == 1){
                        r = MarcaVisitaTempo(vt,cont,'F',(*visitados),tam);
                        if (r == 1) cont++;
                        vt = Desempilha(&pilha);
                    }
                }
        }
        else {
            r = MarcaVisitaTempo(vt,cont,'F',(*visitados),tam);
            if (r == 1) cont++;
            vt = Desempilha(&pilha);
        }
    }

    Registro novo;

    //GARANTE QUE TODOS OS VÉRTICES TENHAM SIDO COLOCADOS NO VETOR DE PROFUNDIDE TEMPO
    for(i=0; i<tam; i++){
        if((*visitados)[i].tempoDescoberta == -1){
            novo = (*visitados)[i].vert;
            PercursoProfundidadeTempo(G, novo, &(*visitados));
            break;
        }

    }

    return 1;
}

// FUNÇÃO DOS CONJUNTOS FORTEMENTE CONECTADOS
void Kosaraju(Grafo G){
    if(G == NULL)
        return;

    Registro v;
    struct visitaTempo *visitados;
    int vetor[G->NumVert];
    int i;

    Grafo Gt; // CRIAÇÃO DO GRAFO TRANSPOSTO
    Gt = criarGrafoTransposto(G);

    v = G->vertices->vert;

    //INICIALIZA OS VISITADOS
    InicializaVisitados(G, &visitados);

    // EM VISITADOS É COLOCADOS OS TEMPOS DE FINALIZAÇÃO DE TODOS OS VÉRTICES DO GRAFO
    PercursoProfundidadeTempo (G, v, &visitados);

    Pilha p, aux;
    p = IniciaPilha(); aux = IniciaPilha();

    // É FEITO UMA PILHA ORDENADA A PARTIR DOS TEMPOS DE FINALIZAÇÃO DO VETOR VISITADOS
    p = OrdenaTempo(G, visitados, G->NumVert);

    for(i=0; i<G->NumVert; i++){
        vetor[i] = 0;
    }

    // É FEITO UMA BUSCA EM PROFUNDIDADE NO GRAFO TRANSPOSTO USANDO A PILHA COM OS TEMPOS ORDENADOS
    for(aux = p; aux != NULL; aux = aux->prox){
        strcpy(v.nome, aux->vert.nome);strcpy(v.tipo, aux->vert.tipo);strcpy(v.acao, aux->vert.acao);
        BuscaEmProfundidade2 (Gt, v, vetor);
    }

    // O RESULTADO SÃO OS ELEMENTOS FORTEMENTE CONECTADOS

}



// CAMINHO MAIS CURTO
void caminhoMaisCurto(Grafo G, int origem){
    if(origem + 1 > G -> NumVert)
    {
        printf("\nVertice nao existe!");
        return;
    }

    int i,v,w,minimo,posmin,S;
    int *M, *L;
    //VETORES DE INTEIROS DO TAMANHO DO GRAFO
    M = (int *)malloc(G->NumVert*sizeof(int));
    L = (int *)malloc(G->NumVert*sizeof(int));

    struct noVert *aux = G -> vertices; // AUXILIAR PARA AJUDAR A TRAÇAR OS CAMINHOS ADJACENTES E O QUE MAIS PRECISAR

    while(aux->prox != NULL) // ACHA O ID DA ORIGEM
    {
        if(aux->id == origem)
            break;

        aux = aux->prox;
    }
    if(aux->prox == NULL && aux->id == origem)
    {
        aux = aux;
    }


    if (aux -> ladj == NULL) //SE NÃO TIVER ADJACENCIA RETURNA VAZIO - NÃO HÁ MENOR CAMINHO
    {
        printf("\nVertice nao se liga a ninguem!");
        return;
    }

    // PREENCHIMENTO PRELIMINAR DOS VÉRTICES
    for (i=0; i < G->NumVert; i++)
    {
        M[i] = 0;      // COLOCA VÉRTICES COMO NÃO VISITADOS
        L[i] = 999999; // VALOR INICIAL PARA OS CUSTOS
    }

    M[origem] = 1; //ORIGEM COMEÇA COMO VISITADO
    for (v = aux->ladj->id; v < G->NumVert; aux->ladj = aux->ladj->prox) // PARA TODOS OS VÉRTICES
    {
        L[v] = aux -> ladj -> peso;

        if(aux -> ladj -> prox == NULL)
            break;

        v = aux->ladj->prox->id;
    }

    for (i = 0; i < G->NumVert; i++) // PASSA POR TODOS OS VÉRTICES
    {
        w = 0;
        minimo = 999999; // BUSCANDO O MÍNIMO

        for (v = aux->ladj->id; v < G->NumVert; aux->ladj = aux->ladj->prox)
        {
            if (L[v] < minimo && M[v]==0)
            {
                minimo = L[v];
                posmin = v; // POSIÇÃO É O ID
                w = 1;
            }
            if(aux -> ladj -> prox == NULL)
                break;
        }

        if (w == 0)
            break;

        M[posmin] = 1;
    }



    // DEVOLVE O AUX AO SEU VALOR ORIGINAL E TRAZ O ID DA POSMIN

    while(aux->prox != NULL)
    {
        if(aux->id == posmin)
            break;

        aux = aux->prox;
    }
    if(aux->prox == NULL && aux->id == posmin)
    {
        aux = aux;
    }



    for (i = 0; i < G->NumVert; i++)
    {
        for (v = aux->ladj->id; v < G->NumVert; aux->ladj = aux->ladj->prox)
        {
            if (M[v] == 0)
            {
                S = L[posmin] + (aux -> ladj -> peso);

                if (S < L[v])
                    L[v] = S;
            }

            if(aux -> ladj -> prox == NULL)
                    break;

            v = aux->ladj->prox->id;
        }
    }

    printf("\nMenor caminho partindo de %d: \n",origem);
    for (v = 0; v < G->NumVert; v++)
    {
        if (L[v] == 999999)
            printf("%d: - \n",v);
        else
            printf("%d: %d\n",v,L[v]);
    }

    free(L);
    free(M);
}



