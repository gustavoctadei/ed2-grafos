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