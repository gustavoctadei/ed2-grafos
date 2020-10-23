#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void imprime_vetor_inteiro(int* vetor, int tamanho_vetor) {
    int i;
    for(i = 0; i < tamanho_vetor; i++) {
        printf("V[%d] - %d\n", i, vetor[i]);
    }
    printf("\n");
}

void imprime_vetor_float(float* vetor, int tamanho_vetor) {
    int i;
    for(i = 0; i < tamanho_vetor; i++) {
        printf("V[%d] - %f\n", i, vetor[i]);
    }
    printf("\n");
}

int main() {
    //Cria a variavel do Grafo
    Grafo* grafo;

    //Cria as variáveis de interface com o usuário
    int opcao, vertice;

    do {
        printf("1 - Carregar o Grafo do Arquivo Texto\n");
        printf("2 - Imprime o Grafo\n");
        printf("3 - Busca em Largura (BFS)\n");
        printf("4 - Busca em Profundidade (DFS)\n");
        printf("5 - Arvore Geradora Minima (Algoritmo de Prim)\n");
        printf("6 - Arvore Geradora Minima (Algoritmo de Kruskal)\n");
        printf("7 - Caminhos Minimos - Busca em Largura (BFS)\n");
        printf("8 - Caminhos Minimos - Dijkstra\n");
        printf("9 - Caminhos Minimos - Floyd Warshall\n");
        printf("10 - Limpar o Grafo da Memoria e Sair\n");
        printf("Digite a Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                grafo = cria_grafo();
                //Cria o Vetor que armazena a ordem de visitas
                int *visitado = (int*) malloc( numero_vertices(grafo) * sizeof(int) );
                printf("\n\n");
                break;

            case 2:
                imprime_grafo(grafo);
                break;

            case 3:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                busca_largura_grafo(grafo, vertice, visitado);
                imprime_vetor_inteiro(visitado, numero_vertices(grafo));
                break;

            case 4:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                busca_profundidade_grafo(grafo, vertice, visitado);
                imprime_vetor_inteiro(visitado, numero_vertices(grafo));
                break;

            case 5:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                int *pai = (int*) malloc( numero_vertices(grafo) * sizeof(int) );
                arvore_geradora_minima_prim(grafo, vertice, pai);
                imprime_vetor_inteiro(pai, numero_vertices(grafo));
                break;

            case 8:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                int *antecessor = (int*) malloc( numero_vertices(grafo) * sizeof(int) );
                float *distancia = (float*) malloc( numero_vertices(grafo) * sizeof(float) );
                menor_caminho_grafo_dijkstra(grafo, vertice, antecessor, distancia);
                imprime_vetor_inteiro(antecessor, numero_vertices(grafo));
                imprime_vetor_float(distancia, numero_vertices(grafo));
                break;

            case 9:
                menor_caminho_grafo_floyd_warshall(grafo);
                break;

            case 10:
                libera_grafo(grafo);
                printf("Saindo...\n");
        }

    } while(opcao != 10);

    return 0;
}