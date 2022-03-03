#include "registro.h"
#include "pilha.h"

struct grafo {
   int NumVert;
   int NumArco;
   struct noVert *vertices;
};
typedef struct grafo *Grafo;

struct noVert {
   int id; //
   Registro vert; //
   struct noVert *prox;
   struct noAdj *ladj;
};

struct noAdj {
   int id;
   Registro vert; //
   struct noAdj *prox;
   int peso;
};

struct visitaTempo{
  Registro vert; //
  int tempoDescoberta;
  int tempoFinalizacao;
  int id;
};


Grafo criarGrafo();
Grafo criarGrafoTransposto(Grafo G);

int inserirArco(Grafo G, Registro v1, Registro v2, int peso);
int removerArco(Grafo G, Registro x, Registro y);
int inserirArco2(Grafo G, int v1, int v2, int peso);
int removerArco2(Grafo G, int v1, int v2);

struct noVert* inserirVertice(struct noVert *ini, Registro x, int num);
int inserirNovoVertice(Grafo G, Registro nv);
int removerVertice(Grafo G, Registro x, int id);
Registro removerVertice2(Grafo G, int x);

int arruma_id(Grafo G, int id);
int confere_id(Grafo G, int x);
int verificaVertice(Grafo G, Registro x);
Registro acha_vertice(Grafo G, int x);
int acha_id(Grafo G, Registro x);

int grauVertice(Grafo G, Registro v);
Registro maior_grau(Grafo G);

void imprimirListaAdj(Grafo G);
void imprimirListaAdjRec(struct noVert *nv);

int BuscaEmProfundidade (Grafo G, Registro v1, Registro v2);
int ExisteCaminho(Grafo G, int v1, int v2);

int PercursoProfundidadeTempo (Grafo G, Registro v, struct visitaTempo** visitados);
int MarcaVisitaTempo(Registro vt, int pos, char tipo, struct visitaTempo *vet, int tam);
int FoiVisitadoTempo(Registro vert, struct visitaTempo *vet, int tam);
Pilha OrdenaTempo(Grafo G, struct visitaTempo *vet, int tam);

int BuscaEmProfundidade2 (Grafo Gt, Registro v, int vetor[]);
void InicializaVisitados(Grafo G, struct visitaTempo** visitados);
void Kosaraju(Grafo G);

void caminhoMaisCurto(Grafo G, int origem);


