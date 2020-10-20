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