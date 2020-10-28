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
            //1 - Carregar o Grafo do Arquivo Texto
            case 1:
                grafo = cria_grafo();
                //Cria os vetores auxiliares para as funcoes do programa
                int *visitado = (int*) malloc( numero_vertices(grafo) * sizeof(int) );
                int *pai = (int*) malloc( numero_vertices(grafo) * sizeof(int) );
                int *arvore = (int*) malloc( numero_vertices(grafo) * sizeof(int) );
                int *antecessor = (int*) malloc( numero_vertices(grafo) * sizeof(int) );
                float *distancia = (float*) malloc( numero_vertices(grafo) * sizeof(float) );
                printf("\n\n");
                break;

            //2 - Imprime o Grafo
            case 2:
                imprime_grafo(grafo);
                break;

            //3 - Busca em Largura (BFS)
            case 3:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                busca_largura_grafo(grafo, vertice, visitado);
                imprime_vetor_inteiro(visitado, numero_vertices(grafo));
                break;

            //4 - Busca em Profundidade (DFS)
            case 4:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                busca_profundidade_grafo(grafo, vertice, visitado);
                imprime_vetor_inteiro(visitado, numero_vertices(grafo));
                break;

            //5 - Arvore Geradora Minima (Algoritmo de Prim)
            case 5:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                arvore_geradora_minima_prim(grafo, vertice, pai);
                imprime_vetor_inteiro(pai, numero_vertices(grafo));
                break;

            //6 - Arvore Geradora Minima (Algoritmo de Kruskal)
            case 6:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                arvore_geradora_minima_kruskal(grafo, vertice, pai, arvore);
                imprime_vetor_inteiro(pai, numero_vertices(grafo));
                imprime_vetor_inteiro(arvore, numero_vertices(grafo));
                break;

            //7 - Caminhos Minimos - Busca em Largura (BFS)
            case 7:
                //Implementar
                break;

            //8 - Caminhos Minimos - Dijkstra
            case 8:
                printf("Digite o Vertice Inicial: ");
                scanf("%d", &vertice);
                menor_caminho_grafo_dijkstra(grafo, vertice, antecessor, distancia);
                imprime_vetor_inteiro(antecessor, numero_vertices(grafo));
                imprime_vetor_float(distancia, numero_vertices(grafo));
                break;

            //9 - Caminhos Minimos - Floyd Warshall
            case 9:
                menor_caminho_grafo_floyd_warshall(grafo);
                break;

            //10 - Limpar o Grafo da Memoria e Sair
            case 10:
                libera_grafo(grafo);
                //Libera da memoria os vetores auxiliares
                free(visitado);
                free(pai);
                free(arvore);
                free(antecessor);
                free(distancia);
                printf("Saindo...\n");
        }

    } while(opcao != 10);

    return 0;
}