#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//Definindo o TAD do Grafo
struct grafo {
    int eh_ponderado;
    int numero_vertices;
    int grau_maximo;
    int** arestas;
    float** pesos;
    int* grau;
};

Grafo* cria_grafo(int numero_vertices, int grau_maximo, int eh_ponderado) {
    Grafo *grafo;

    //Aloca memória para armazenar a estrutura do grafo
    grafo = (Grafo*) malloc( sizeof(struct grafo) );

    //Caso consiga alocar a memória com sucesso, entra no if
    if(grafo != NULL) {
        int i;

        //Insere as informações fornecidas pelo usuario à estrutura do grafo
        grafo->numero_vertices = numero_vertices;
        grafo->grau_maximo = grau_maximo;
        grafo->eh_ponderado = eh_ponderado;
        grafo->grau = (int*) calloc(numero_vertices, sizeof(int*)); //Vetor para armezenar o grau de cada vértice

        //Alocando a lista de adjacências de cada vértice
        grafo->arestas = (int**) malloc( numero_vertices * sizeof(int*) );
        for(i = 0; i < numero_vertices; i++) {
            grafo->arestas[i] = (int*) malloc(grau_maximo * sizeof(int*) );
        }

        //Se for ponderado, aloca memória para a estrutura que armazena os pesos
        if(grafo->eh_ponderado) {
            grafo->pesos = (float**) malloc(numero_vertices * sizeof(float**) );
            for(i = 0; i < numero_vertices; i++) {
                grafo->pesos[i] = (float*) malloc(grau_maximo * sizeof(float) );
            }
        }
    }

    return grafo;
}

void libera_grafo(Grafo* grafo) {
    //Verifica se o ponteiro está, de fato, apontando para o grafo na memória
    if(grafo != NULL) {
        int i;

        for(i = 0; i < grafo->numero_vertices; i++) {
            free(grafo->arestas[i]); //Libera a lista de adjacências de cada vértice
        }
        free(grafo->arestas); //Libera a lista de vértices

        //Verifica se o grafo é ponderado. Caso sim, libera a estrutura que armazena os pesos das arestas
        if(grafo->eh_ponderado) {
            for(i = 0; i < grafo->numero_vertices; i++) {
                free(grafo->pesos[i]);
            }
            free(grafo->pesos);
        }

        free(grafo->grau); //Libera a lista que armazena o grau de cada vértice
        free(grafo);
    }
}

int insere_aresta(Grafo* grafo, int origem, int destino, int eh_digrafo, float peso) {
    //Se o Ponteiro para o Grafo, o Vértice de Origem ou Vértice de Destino forem inválidos, retorna 0
    if(grafo == NULL) {
        return 0;
    }

    if(origem < 0 || origem >= grafo->numero_vertices) {
        return 0;
    }

    if(destino < 0 || destino >= grafo->numero_vertices) {
        return 0;
    }

    grafo->arestas[origem][grafo->grau[origem]] = destino; //Insere o vértice de destino ao final da lista de adjacências do vértice de origem
    
    //Caso o grafo seja ponderado, insere o peso da aresta
    if(grafo -> eh_ponderado) {
        grafo->pesos[origem][grafo->grau[origem]] = peso;
    }
    grafo->grau[origem]++; //Incrementa o valor do Grau do Vértice de Origem

    //Se não for dígrafo, insere a aresta inversa
    if(eh_digrafo == 0){
        insere_aresta(grafo, destino, origem, 1, peso);
    }

    //Caso tenha inserido com sucesso, retorna 1
    return 1;
}

int remove_aresta(Grafo* grafo, int origem, int destino, int eh_digrafo) {
    //Se o Ponteiro para o Grafo, o Vértice de Origem ou Vértice de Destino forem inválidos, retorna 0
    if(grafo == NULL) {
        return 0;
    }

    if(origem < 0 || origem >= grafo->numero_vertices) {
        return 0;
    }

    if(destino < 0 || destino >= grafo->numero_vertices) {
        return 0;
    }

    int i = 0;

    //Procura a aresta na lista de adjacências do Vértice de Destino
    while(i < grafo->grau[origem] && grafo->arestas[origem][i] != destino) {
        if(i == grafo->grau[origem]) { //Se percorreu toda a lista de adjacências do vértice de Origem, elemento não encontrado
            return 0;
        }
    }

    grafo->grau[origem]--; //Decrementa o Grau do Vértice de Origem
    grafo->arestas[origem][i] = grafo->arestas[origem][grafo->grau[origem]]; //Copia a última aresta para a posição que foi removida da lista de adjacências da Origem

    if(grafo->eh_ponderado) {
        grafo->pesos[origem][i] = grafo->pesos[origem][grafo->grau[origem]]; //Copia o peso da última aresta para a posição que foi removida da lista de Pesos da aresta
    }

    //Se não for Dígrafo, remove a aresta inversa
    if(eh_digrafo == 0) {
        remove_aresta(grafo, destino, origem, 1);
    }

    //Caso a remoção tenha ocorrido com sucesso, retorna 1
    return 1;
}

//Funções de Busca

//Função auxiliar para Busca em Profundidade
void busca_profundidade(Grafo *grafo, int inicio, int *visitado, int cont) {
    int i;
    visitado[inicio] = cont; //Marca o vértice inicial como visitado

    //Verifica se cada vizinho do Vértice inicio já foi visitado
    for(i = 0; i < grafo->grau[inicio]; i++) {
        if( !visitado[grafo->arestas[inicio][i]] ) { //Caso não tenha sido visitado, a função de Busca em Profundidade é chamada e o contador de visitação é incrementado
            busca_profundidade(grafo, grafo->arestas[inicio][i], visitado, cont+1);
        }
    }
    //Ao fim, temos o vetor visitado que contém a ordem em que cada vértice foi visitado
}

//Função principal para Busca em Profundidade
void busca_profundidade_grafo(Grafo *grafo, int inicio, int *visitado) {
    int i, cont = 1;

    //Array que armazena a ordem em que cada vértice será visitado
    //Marca todos os vértices como não visitados
    for(i = 0; i < grafo->numero_vertices; i++) {
        visitado[i] = 0;
    }

    //Chama a função de busca em profundidade para o Vértice Inicial
    busca_profundidade(grafo, inicio, visitado, cont);
}