typedef struct grafo Grafo;

//Grafo* cria_grafo(FILE* f);
Grafo* cria_grafo();
void libera_grafo(Grafo* grafo);
void imprime_grafo(Grafo *grafo);
int numero_vertices(Grafo *grafo);

//Funções de Busca
void busca_profundidade_grafo(Grafo *grafo, int inicio, int *visitado);
void busca_largura_grafo(Grafo *grafo, int inicio, int *visitado);

//Função Principal para Menor Caminho entre dois Vértices utilizando o Algoritmo de Dijkstra
void menor_caminho_grafo(Grafo *grafo, int inicial, int *antecessor, float *distancia);