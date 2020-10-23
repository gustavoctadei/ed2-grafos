typedef struct grafo Grafo;

Grafo* cria_grafo();
void libera_grafo(Grafo* grafo);
void imprime_grafo(Grafo *grafo);
int numero_vertices(Grafo *grafo);

//Funções de Busca
void busca_profundidade_grafo(Grafo *grafo, int inicio, int *visitado);
void busca_largura_grafo(Grafo *grafo, int inicio, int *visitado);

//Função Principal para Menor Caminho entre dois Vértices utilizando o Algoritmo de Dijkstra
void menor_caminho_grafo_dijkstra(Grafo *grafo, int inicial, int *antecessor, float *distancia);
//Função Principal para Menor Caminho entre dois Vértices utilizando o Algoritmo de Floyd Warshall
void menor_caminho_grafo_floyd_warshall(Grafo *grafo);
//Arvore Geradora Minima - Algoritmo de Prim
void arvore_geradora_minima_prim(Grafo *grafo, int origem, int *pai);