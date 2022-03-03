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

    Registro aux[5]; //ARMAZENA TEMPORARIAMENTE OS ELEMENTOS DA LINHA SEPARADOS POR V�RGULA
    Registro Arestas[100]; //ARMAZENA OS PARES DE V�RTICES QUE FORMAM UMA ARESTA
    Registro x[100]; //ARMAZENA OS V�RTICES N�O REPETIDOS DO ARQUIVO

    int peso[100]; // ARMAZENA O PESO DAS ARESTAS
    int k = 0; // ARMAZENA O N�MERO DE V�RTICES N�O REPETIDOS
    int w = 0; // AUXILIAR
    int j = 0; // ARMAZENA O N�MERO DE LINHAS DO ARQUIVO
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
        // CADA LINHA � SEPARADA POR V�RGULA E COLOCADA NO REGISTRO AUX
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

        // GUARDA AS DUAS PRIMEIRAS POSI��ES
        if (k == 0){
            x[0] = aux[0];
            x[1] = aux[1];
            k = k +2;
        }



        // CONT VAI VERIFICAR SE O V�RTICE J� EXISTE OU N�O
        // SE ELE CONTINUAR COM -1, ELE � UM V�RTICE NOVO
        // SE ELE FOR UM V�RTICE QUE J� EXISTE CONT VAI GUARDAR A POSI��O ONDE ELE EST�
        int cont1 = -1;
        for(i=0; i<k; i++){
            if (strcmp(aux[0].nome, x[i].nome)==0 && strcmp(aux[0].tipo, x[i].tipo)==0 && strcmp(aux[0].acao, x[i].acao)==0){
                cont1 = i;
                break;
            }
        }
        // COMO � UM V�RTICE NOVO ELE � ADICIONADO EM X[]
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



        // CASO1: OS DOIS V�RTICES S�O NOVOS - S�O ADICIONADOS NA ARESTA[] OS 2 �LTIMOS ELEMENTOS DE X[]
        if(cont1 == -1 && cont2 == -1){
            Arestas[w] = x[k-2];
            Arestas[w+1] = x[k-1];
        }
        // CASO2: O PRIMEIRO J� EXISTE E O SEGUNDO � NOVO -
        //        CONT GUARDA A POSI��O ONDE O ELEMENTO EST� EM X[]
        //        � ADICIONADO NA ARESTA[] ESSES V�RTICES - O �LTIMO ELEMENTO DE X[] (NOVO) E O [CONT]
        if(cont1 != -1 && cont2 == -1){
            Arestas[w] = x[cont1];
            Arestas[w+1] = x[k-1];
        }
        // CASO3: O PRIMEIRO � NOVO E O SEGUNDO J� EXISTE -
        //        CONT GUARDA A POSI��O ONDE O ELEMENTO EST� EM X[]
        //        ESSES V�RTICE S�O ADICIONADOS NA ARESTA[] - O [CONT] E O �LTIMO ELEMENTO DE X[] (NOVO)
        if(cont1 == -1 && cont2 != -1){
            Arestas[w] = x[k-1];
            Arestas[w+1] = x[cont2];
        }
        // CASO4: OS DOIS J� EXISTEM
        //        CONT GUARDA A POSI��O ONDE O ELEMENTO EST� EM X[]
        //        � ADICIONADO NA ARESTA[] CONT1 E CONT2
        if(cont1 != -1 && cont2 != -1){
            Arestas[w] = x[cont1];
            Arestas[w+1] = x[cont2];
        }


        w = w + 2; //FOI ADICIONADO DOIS V�RTICES EM ARESTAS[], ENT�O ACRESCENTA DOIS NO CONTADOR W
        j++; // CONTA O N�MERO DE LINHAS DO ARQUIVO, VAI PARA A PR�XIMA LINHA, AUMENTA UM NO CONTADOR J
    }

    //FECHA O ARQUIVO
    fclose(file);


    Grafo g; //CRIA��O DO GRAFO
    g = criarGrafo();


    // � ADICIONADO CADA V�RTICE DO VETOR X[] NO GRAFO g
    int confirma = 0;
    for(i=0; i<k; i++){
        confirma = inserirNovoVertice(g, x[i]);
    }
    if(confirma == 1)
        printf("\nV�rtices adicionados com sucesso\n");


    // � INSERIDO OS ARCOS (DE DOIS EM DOIS) A PARTIR DO VETOR ARESTAS[] E SEU RESPECTIVO PESO, DO VETOR PESO
    int m = 0;
    for(i=0; i<2*j; i=i+2){
        confirma = inserirArco(g, Arestas[i], Arestas[i+1], peso[m]);
        m++;
    }
    if(confirma == 1)
        printf("Arestas adicionadas com sucesso\n");


    imprimirListaAdj(g); // IMPRESS�O DO ARQUIVO NO MODO INICIAL
    opcoes(g); //CHAMA A FUN��O DO MENU DE OP��ES

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
        printf("  [1]Inserir novo v�rtice\n");
        printf("  [2]Remover v�rtice\n");
        printf("  [3]Inserir nova aresta\n");
        printf("  [4]Remover aresta\n");
        printf("  [5]Verificar v�rtice de maior grau\n");
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
                // INSERE NOVO V�RTICE

                //SE O V�RTICE J� EXISTE, PEDE A INFORMA��O DE NOVO
                do{
                    printf("\n\nIndique as informa��es do v�rtice:\n");
                    printf("Nome: ");fflush(stdin);scanf("%[^\n]", nome);
                    printf("Tipo: ");fflush(stdin);scanf("%s", tipo);
                    printf("A��o: ");fflush(stdin);scanf("%s", acao);

                    strcpy(novo.nome, nome); strcpy(novo.tipo, tipo); strcpy(novo.acao, acao);

                    // SE ELE J� EXISTE, ESCOLHE ENTRE ESCREVER DE NOVO E SAIR
                    if(verificaVertice(g, novo)==0){
                        printf("\nV�rtice j� existe!");
                        printf("\n[0]Para sair\n[1]Para escrever outro id: ");
                        scanf("%d", &op);
                        if(op == 0)
                            break;
                    }
                 }while(verificaVertice(g, novo)==0);

                inserirNovoVertice(g, novo);

                break;


            case 2:
                // RETIRA UM V�RTICE POR MEIO DO ID

                //SE O ID N�O EXISTE, PEDE A INFORMA��O DE NOVO
                do{
                    printf("\n\nIndique o id do v�rtice a ser retirado: ");
                    fflush(stdin);
                    scanf("%d", &id);
                    // SE ELE N�O EXISTE, ESCOLHE ENTRE ESCREVER DE NOVO E SAIR
                    if(confere_id(g, id)==0){
                        printf("\nV�rtice n�o existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                        if(op == 0)
                            break;
                    }
                }while(confere_id(g, id)==0);

                if(op == 0)
                    break;

                aux = removerVertice2(g, id);

                printf("O v�rtice retirado foi: %s", aux.nome);
                break;


            case 3:
                // INSERE ARESTAS POR MEIO DOS ID'S

                 //SE OS ID'S N�O EXISTIREM, PEDE A INFORMA��O DE NOVO - CASO ELE N�O EXISTA, ESCOLHE ENTRE ESCREVER DE NOVO E SAIR
                do{
                    printf("\n\nIndique o id do primeiro v�rtice: ");
                    scanf("%d", &id);
                    if(confere_id(g, id)==0){
                        printf("\nV�rtice n�o existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id)==0 || op == 1);
                if(op == 0)
                    break;

                do{
                    printf("Indique o id do segundo v�rtice: ");
                    scanf("%d", &id2);
                    if(confere_id(g, id2)==0){
                        printf("\nV�rtice n�o existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id2)==0 || op == 1);

                if(op == 0)
                    break;

                printf("\nQual � o peso da aresta que vai ser adicionada? ");
                scanf("%d", &pesos);
                printf("\n\n");

                if(inserirArco2(g, id, id2, pesos)==0)
                    printf("\nO arco j� existe!");


                break;

            case 4:
                // RETIRA ARESTAS POR MEIO DOS ID'S

                //SE OS ID'S N�O EXISTEM, PEDE A INFORMA��O DE NOVO - CASO ELE N�O EXISTA, ESCOLHE ENTRE ESCREVER DE NOVO E SAIR
                do{
                    printf("\n\n     Para ser retirada a aresta...\n");
                    printf("Indique o informa��es do primeiro v�rtice: ");
                    scanf("%d", &id);
                    if(confere_id(g, id)==0){
                        printf("\nV�rtice n�o existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id)==0 || op == 1);
                if(op == 0)
                    break;

                do{
                    printf("\nIndique as informa��es do segundo v�rtice: ");
                    scanf("%d", &id2);
                    if(confere_id(g, id2)==0){
                        printf("\nV�rtice n�o existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id2)== 0  || op == 1);
                if(op == 0)
                    break;

                if(removerArco2(g, id, id2)==1)
                    printf("\nAresta retirada com sucesso!\n");
                else
                    printf("\nErro ao retirar aresta! Esses v�rtices n�o tem conex�o!\n");

                break;

            case 5:
                // MAIOR GRAU

                printf("\nO maior grau �: ");
                // CHAMA A FUN��O DE MAIOR GRAU QUE RETORNA QUAL � SEU NOME E N�MERO DO V�RTICE
                aux = maior_grau(g);
                printf("\nO v�rtice de maior grau �: ");printf("%s", aux.nome);
                printf("\n\n**Esse pode n�o ser o �nico v�rtice que cont�m o maior grau**");

                break;

            case 6:
                // VERIFICA SE EXISTE CAMINHO ENTRE DOIS V�RTICES

                 //SE O ID N�O EXISTE, PEDE A INFORMA��O DE NOVO
                do{
                    printf("\nIndique o id do primeiro v�rtice: ");
                    scanf("%d", &id);
                    if(confere_id(g, id)==0){
                        printf("\nV�rtice n�o existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id)==0 || op == 1);
                if(op == 0)
                    break;

                do{
                    printf("Indique o id do segundo v�rtice: ");
                    scanf("%d", &id2);
                    if(confere_id(g, id2)==0){
                        printf("\nV�rtice n�o existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id2)==0 || op == 1);
                if(op == 0)
                    break;

                // DESCOBRE QUAIS S�O OS V�RTICES DOS IDS DADOS
                aux = acha_vertice(g, id);
                aux2 = acha_vertice(g, id2);

                //CHAMA A FUN��O PARA SABER SE EXISTE CAMINHO ENTRE OS DOIS IDS
                if(ExisteCaminho(g, id, id2)==1)
                    printf("\nExiste caminho entre os v�rtices %s e %s!", aux.nome, aux2.nome);
                else
                    printf("\nN�o existe caminho entre os v�rtices %s e %s!", aux.nome, aux2.nome);

                break;



            case 7:
                // CAMINHO MAIS CURTO

                do{
                    printf("\nDigite a id para saber o caminho mais curto: ");
                    scanf("%d", &id);
                    if(confere_id(g, id)==0){
                        printf("\nV�rtice n�o existe!");
                        printf("\n[0]Para sair\n[1]Para escrever de novo: ");
                        scanf("%d", &op);
                    }
                }while(confere_id(g, id)==0 || op == 1);
                if(op == 0)
                    break;

                caminhoMaisCurto(g,id);

                break;

            case 8:
                // SABER QUAIS S�O OS CONJUNTOS FORTEMENTE CONECTADOS

                printf("\n\nGrupo Fortemente conectado:");
                Kosaraju(g);
                break;

            case 9:
                // IMPRESS�O DA LISTA
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

