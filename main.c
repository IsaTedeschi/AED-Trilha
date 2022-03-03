#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "grafo.h"


void opcoes(Grafo g);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    char linha[100]; //ARMAZENA TEMPORARIAMENTE CADA LINHA DO ARQUIVO

    Registro aux[5]; //ARMAZENA TEMPORARIAMENTE OS ELEMENTOS DA LINHA SEPARADOS POR VÍRGULA
    Registro Arestas[100]; //ARMAZENA OS PARES DE VÉRTICES QUE FORMAM UMA ARESTA
    Registro x[100]; //ARMAZENA OS VÉRTICES NÃO REPETIDOS DO ARQUIVO

    int peso[100]; // ARMAZENA O PESO DAS ARESTAS
    int k = 0; // ARMAZENA O NÚMERO DE VÉRTICES NÃO REPETIDOS
    int w = 0; // AUXILIAR
    int j = 0; // ARMAZENA O NÚMERO DE LINHAS DO ARQUIVO
    int i = 0; // AUXILIAR
    char *token;

    printf("\n****GRAFOS*****\n\n");

    // ABRE O ARQUIVO
    FILE *file = fopen("texto.txt", "r");

    if (file == NULL){
        fprintf(stderr, "Arquivo de leitura nao pode ser aberto!!!\n");
        return -1;
    }


    while (fscanf(file, "%[^\n] ", linha) != EOF){
        // CADA LINHA É SEPARADA POR VÍRGULA E COLOCADA NO REGISTRO AUX
        token = strtok(linha, ",");
        strcpy(aux[0].nome, token);
        token = strtok(NULL, ",");
        strcpy(aux[0].tipo, token);
        token = strtok(NULL, ",");
        strcpy(aux[0].acao, token);

        token = strtok(NULL, ",");
        peso[j] = atoi(token);

        token = strtok(NULL, ",");
        strcpy(aux[1].nome, token);
        token = strtok(NULL, ",");
        strcpy(aux[1].tipo, token);
        token = strtok(NULL, ",");
        strcpy(aux[1].acao, token);

        // GUARDA AS DUAS PRIMEIRAS POSIÇÕES
        if (k == 0){
            x[0] = aux[0];
            x[1] = aux[1];
            k = k +2;
        }



        // CONT VAI VERIFICAR SE O VÉRTICE JÁ EXISTE OU NÃO
        // SE ELE CONTINUAR COM -1, ELE É UM VÉRTICE NOVO
        // SE ELE FOR UM VÉRTICE QUE JÁ EXISTE CONT VAI GUARDAR A POSIÇÃO ONDE ELE ESTÁ
        int cont1 = -1;
        for(i=0; i<k; i++){
            if (strcmp(aux[0].nome, x[i].nome)==0 && strcmp(aux[0].tipo, x[i].tipo)==0 && strcmp(aux[0].acao, x[i].acao)==0){
                cont1 = i;
                break;
            }
        }
        // COMO É UM VÉRTICE NOVO ELE É ADICIONADO EM X[]
        if(cont1 == -1){
            x[k] = aux[0];
            k++;
        }

        int cont2 = -1;
        for(i=0; i<k; i++){
            if (strcmp(aux[1].nome, x[i].nome)==0 && strcmp(aux[1].tipo, x[i].tipo)==0 && strcmp(aux[1].acao, x[i].acao)==0){
                cont2 = i;
                break;
            }
        }
        if(cont2 == -1){
            x[k] = aux[1];
            k++;
        }



        // CASO1: OS DOIS VÉRTICES SÃO NOVOS - SÃO ADICIONADOS NA ARESTA[] OS 2 ÚLTIMOS ELEMENTOS DE X[]
        if(cont1 == -1 && cont2 == -1){
            Arestas[w] = x[k-2];
            Arestas[w+1] = x[k-1];
        }
        // CASO2: O PRIMEIRO JÁ EXISTE E O SEGUNDO É NOVO -
        //        CONT GUARDA A POSIÇÃO ONDE O ELEMENTO ESTÁ EM X[]
        //        É ADICIONADO NA ARESTA[] ESSES VÉRTICES - O ÚLTIMO ELEMENTO DE X[] (NOVO) E O [CONT]
        if(cont1 != -1 && cont2 == -1){
            Arestas[w] = x[cont1];
            Arestas[w+1] = x[k-1];
        }
        // CASO3: O PRIMEIRO É NOVO E O SEGUNDO JÁ EXISTE -
        //        CONT GUARDA A POSIÇÃO ONDE O ELEMENTO ESTÁ EM X[]
        //        ESSES VÉRTICE SÃO ADICIONADOS NA ARESTA[] - O [CONT] E O ÚLTIMO ELEMENTO DE X[] (NOVO)
        if(cont1 == -1 && cont2 != -1){
            Arestas[w] = x[k-1];
            Arestas[w+1] = x[cont2];
        }
        // CASO4: OS DOIS JÁ EXISTEM
        //        CONT GUARDA A POSIÇÃO ONDE O ELEMENTO ESTÁ EM X[]
        //        É ADICIONADO NA ARESTA[] CONT1 E CONT2
        if(cont1 != -1 && cont2 != -1){
            Arestas[w] = x[cont1];
            Arestas[w+1] = x[cont2];
        }


        w = w + 2; //FOI ADICIONADO DOIS VÉRTICES EM ARESTAS[], ENTÃO ACRESCENTA DOIS NO CONTADOR W
        j++; // CONTA O NÚMERO DE LINHAS DO ARQUIVO, VAI PARA A PRÓXIMA LINHA, AUMENTA UM NO CONTADOR J
    }

    //FECHA O ARQUIVO
    fclose(file);


    Grafo g; //CRIAÇÃO DO GRAFO
    g = criarGrafo();


    // É ADICIONADO CADA VÉRTICE DO VETOR X[] NO GRAFO g
    int confirma = 0;
    for(i=0; i<k; i++){
        confirma = inserirNovoVertice(g, x[i]);
    }
    if(confirma == 1)
        printf("\nVértices adicionados com sucesso\n");


    // É INSERIDO OS ARCOS (DE DOIS EM DOIS) A PARTIR DO VETOR ARESTAS[] E SEU RESPECTIVO PESO, DO VETOR PESO
    int m = 0;
    for(i=0; i<2*j; i=i+2){
        confirma = inserirArco(g, Arestas[i], Arestas[i+1], peso[m]);
        m++;
    }
    if(confirma == 1)
        printf("Arestas adicionadas com sucesso\n");


    imprimirListaAdj(g); // IMPRESSÃO DO ARQUIVO NO MODO INICIAL
    opcoes(g); //CHAMA A FUNÇÃO DO MENU DE OPÇÕES

    return 0;

}

void opcoes(Grafo g){

    //AUXILIARES DO TIPO REGISTRO
    Registro novo;
    Registro aux;
    Registro aux2;

    int option = 0;
    int op;

    int pesos;
    char nome[20], tipo[20], acao[20];
    int id, id2;


    do{
        printf("\n\n");
        printf(" ---------------------------------------------------\n");
        printf("  [1]Inserir novo vértice\n");
        printf("  [2]Remover vértice\n");
        printf("  [3]Inserir nova aresta\n");
        printf("  [4]Remover aresta\n");
        printf("  [5]Verificar vértice de maior grau\n");
        printf("  [6]Verificar se existe caminho entre dois vertices \n");
        printf("  [7]Encontrar o menor caminho\n");
        printf("  [8]Encontrar recursos fortemente conectados\n");
        printf("  [9]Imprimir\n");
        printf("  [10]Sair\n");
        printf(" ---------------------------------------------------\n");
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &option);

        switch(option){

            case 1:
                // INSERE NOVO VÉRTICE

                //SE O VÉRTICE JÁ EXISTE, PEDE A INFORMAÇÃO DE NOVO
                do{
                    printf("\n\nIndique as informações do vértice:\n");
                    printf("Nome: ");fflush(stdin);scanf("%[^\n]", nome);
                    printf("Tipo: ");fflush(stdin);scanf("%s", tipo);
                    printf("Ação: ");fflush(stdin);scanf("%s", acao);

                    strcpy(novo.nome, nome); strcpy(novo.tipo, tipo); strcpy(novo.acao, acao);

                    // SE ELE JÁ EXISTE, ESCOLHE ENTRE ESCREVER DE NOVO E SAIR
                    if(verificaVertice(g, novo)==0){
                        printf("\nVértice já existe!");
                        printf("\n[0]Para sair\n[1]Para escrever outro id: ");
                        scanf("%d", &op);
                        if(op == 0)
                            break;
                    }
                 }while(verificaVertice(g, novo)==0);

                inserirNovoVertice(g, novo);

                break;


            case 2:
                // RETIRA UM VÉRTICE POR MEIO DO ID

                //SE O ID NÃO EXISTE, PEDE A INFORMAÇÃO DE NOVO
                do{
                    printf("\n\nIndique o id do vértice a ser retirado: ");
                    fflush(stdin);
                    scanf("%d", &id);
                    // SE ELE NÃO EXISTE, ESCOLHE ENTRE ESCREVER DE NOVO E SAIR
                    if(confere_id(g, id)==0){
                        printf("\nVértice não existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                        if(op == 0)
                            break;
                    }
                }while(confere_id(g, id)==0);

                if(op == 0)
                    break;

                aux = removerVertice2(g, id);

                printf("O vértice retirado foi: %s", aux.nome);
                break;


            case 3:
                // INSERE ARESTAS POR MEIO DOS ID'S

                 //SE OS ID'S NÃO EXISTIREM, PEDE A INFORMAÇÃO DE NOVO - CASO ELE NÃO EXISTA, ESCOLHE ENTRE ESCREVER DE NOVO E SAIR
                do{
                    printf("\n\nIndique o id do primeiro vértice: ");
                    scanf("%d", &id);
                    if(confere_id(g, id)==0){
                        printf("\nVértice não existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id)==0 || op == 1);
                if(op == 0)
                    break;

                do{
                    printf("Indique o id do segundo vértice: ");
                    scanf("%d", &id2);
                    if(confere_id(g, id2)==0){
                        printf("\nVértice não existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id2)==0 || op == 1);

                if(op == 0)
                    break;

                printf("\nQual é o peso da aresta que vai ser adicionada? ");
                scanf("%d", &pesos);
                printf("\n\n");

                if(inserirArco2(g, id, id2, pesos)==0)
                    printf("\nO arco já existe!");


                break;

            case 4:
                // RETIRA ARESTAS POR MEIO DOS ID'S

                //SE OS ID'S NÃO EXISTEM, PEDE A INFORMAÇÃO DE NOVO - CASO ELE NÃO EXISTA, ESCOLHE ENTRE ESCREVER DE NOVO E SAIR
                do{
                    printf("\n\n     Para ser retirada a aresta...\n");
                    printf("Indique o informações do primeiro vértice: ");
                    scanf("%d", &id);
                    if(confere_id(g, id)==0){
                        printf("\nVértice não existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id)==0 || op == 1);
                if(op == 0)
                    break;

                do{
                    printf("\nIndique as informações do segundo vértice: ");
                    scanf("%d", &id2);
                    if(confere_id(g, id2)==0){
                        printf("\nVértice não existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id2)== 0  || op == 1);
                if(op == 0)
                    break;

                if(removerArco2(g, id, id2)==1)
                    printf("\nAresta retirada com sucesso!\n");
                else
                    printf("\nErro ao retirar aresta! Esses vértices não tem conexão!\n");

                break;

            case 5:
                // MAIOR GRAU

                printf("\nO maior grau é: ");
                // CHAMA A FUNÇÃO DE MAIOR GRAU QUE RETORNA QUAL É SEU NOME E NÚMERO DO VÉRTICE
                aux = maior_grau(g);
                printf("\nO vértice de maior grau é: ");printf("%s", aux.nome);
                printf("\n\n**Esse pode não ser o único vértice que contém o maior grau**");

                break;

            case 6:
                // VERIFICA SE EXISTE CAMINHO ENTRE DOIS VÉRTICES

                 //SE O ID NÃO EXISTE, PEDE A INFORMAÇÃO DE NOVO
                do{
                    printf("\nIndique o id do primeiro vértice: ");
                    scanf("%d", &id);
                    if(confere_id(g, id)==0){
                        printf("\nVértice não existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id)==0 || op == 1);
                if(op == 0)
                    break;

                do{
                    printf("Indique o id do segundo vértice: ");
                    scanf("%d", &id2);
                    if(confere_id(g, id2)==0){
                        printf("\nVértice não existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id2)==0 || op == 1);
                if(op == 0)
                    break;

                // DESCOBRE QUAIS SÃO OS VÉRTICES DOS IDS DADOS
                aux = acha_vertice(g, id);
                aux2 = acha_vertice(g, id2);

                //CHAMA A FUNÇÃO PARA SABER SE EXISTE CAMINHO ENTRE OS DOIS IDS
                if(ExisteCaminho(g, id, id2)==1)
                    printf("\nExiste caminho entre os vértices %s e %s!", aux.nome, aux2.nome);
                else
                    printf("\nNão existe caminho entre os vértices %s e %s!", aux.nome, aux2.nome);

                break;



            case 7:
                // CAMINHO MAIS CURTO

                do{
                    printf("\nDigite a id para saber o caminho mais curto: ");
                    scanf("%d", &id);
                    if(confere_id(g, id)==0){
                        printf("\nVértice não existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id)==0 || op == 1);
                if(op == 0)
                    break;

                caminhoMaisCurto(g,id);

                break;

            case 8:
                // SABER QUAIS SÃO OS CONJUNTOS FORTEMENTE CONECTADOS

                printf("\n\nGrupo Fortemente conectado:");
                Kosaraju(g);
                break;

            case 9:
                // IMPRESSÃO DA LISTA
                imprimirListaAdj(g);
                break;

            case 10:
                printf("\n\nFIM DO PROGRAMA!!!\n\n");
                break;

            default:
                printf(">> Opcao invalida, tente novamente!");
                break;
        }
    }while(option != 10);

}

