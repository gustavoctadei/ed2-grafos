#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main() {
    int numero_vertices = 5, eh_digrafo = 1, i;
    Grafo* grafo = cria_grafo(5, 5, 0);
    int *visitado = (int*) malloc(numero_vertices * sizeof(int));

    //Criando o grafo
    insere_aresta(grafo, 0, 1, eh_digrafo, 0);
    insere_aresta(grafo, 1, 3, eh_digrafo, 0);
    insere_aresta(grafo, 1, 2, eh_digrafo, 0);
    insere_aresta(grafo, 2, 4, eh_digrafo, 0);
    insere_aresta(grafo, 3, 0, eh_digrafo, 0);
    insere_aresta(grafo, 3, 4, eh_digrafo, 0);
    insere_aresta(grafo, 4, 1, eh_digrafo, 0);

    imprime_grafo(grafo);


    //Realizar a busca em profundidade aqui
    //busca_profundidade_grafo(grafo, 0, visitado);

    //Imprimindo o vetor que guarda a ordem de visita
    //for(i = 0; i < 5; i++) {
    //    printf("V[%d] - %d\n", i, visitado[i]);
    //}

    ////////////////////////////////////////////////////////

    //Realizar a busca em largura
    //busca_largura_grafo(grafo, 0, visitado);

    //Imprimindo o vetor que guarda a ordem de visita
    //for(i = 0; i < 5; i++) {
    //    printf("V[%d] - %d\n", i, visitado[i]);
    //}

    //Liberando o Grafo
    libera_grafo(grafo);

    system("pause");
    return 0;
}