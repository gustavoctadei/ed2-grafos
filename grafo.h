typedef struct grafo Grafo;

Grafo* cria_grafo(int numero_vertices, int grau_maximo, int eh_ponderado);
void libera_grafo(Grafo* grafo);

int insere_aresta(Grafo* grafo, int origem, int destino, int eh_digrafo, float peso);
int remove_aresta(Grafo* grafo, int origem, int destino, int eh_digrafo);