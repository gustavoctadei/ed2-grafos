typedef struct grafo Grafo;

Grafo* cria_grafo(int numero_vertices, int grau_maximo, int eh_ponderado);
void libera_grafo(Grafo* grafo);
void imprime_grafo(Grafo *grafo);

int insere_aresta(Grafo* grafo, int origem, int destino, int eh_digrafo, float peso);
int remove_aresta(Grafo* grafo, int origem, int destino, int eh_digrafo);

//Funções de Busca
void busca_profundidade_grafo(Grafo *grafo, int inicio, int *visitado);
void busca_largura_grafo(Grafo *grafo, int inicio, int *visitado);