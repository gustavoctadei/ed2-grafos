#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//Definindo o TAD do Grafo
struct grafo {
    int eh_ponderado;
    int eh_digrafo;
    int numero_vertices;
    int grau_maximo;
    int** arestas;
    float** pesos;
    int* grau;
};

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

Grafo* cria_grafo() {
    FILE *f = fopen("grafo.txt", "r");
    
    if(f == NULL) {
        return 0;
    }
    
    int numero_vertices, grau_maximo, eh_ponderado;

    //Lê do arquivo texto o numero de vértices, grau máximo e se o grafo é ponderado
    fscanf(f, "%d, %d, %d\n", &numero_vertices, &grau_maximo, &eh_ponderado);

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

    //Cria as variáveis para inserção das arestas do arquivo texto
    int origem, destino, eh_digrafo, eof;
    float peso;

    while(eof != EOF) {
        eof = fscanf(f, "%d, %d, %d, %f\n", &origem, &destino, &eh_digrafo, &peso); //Lê as informações da aresta
        if (eof != EOF){
            insere_aresta(grafo, origem, destino, eh_digrafo, peso); //Insere a aresta com as informações contidas no arquivo texto
        }
    }
    
    fclose(f);
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

// Percorre e imprime todo o grafo
void imprime_grafo(Grafo *grafo) {
    if(grafo == NULL) {
        return;
    }

    int i, j;

    printf("\n");
    for(i = 0; i < grafo->numero_vertices; i++) {
        printf ("%d: ", i);

        for(j = 0; j < grafo->grau[i]; j++) {
            if(grafo->eh_ponderado) {
                printf("%d (%.2f), ", grafo->arestas[i][j], grafo->pesos[i][j]);
            }
            else {
                printf("%d, ", grafo->arestas[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n\n");
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

//Função para Busca em Largura
void busca_largura_grafo(Grafo *grafo, int inicio, int *visitado) {
    int i, vertice, numero_vertices, cont = 1;
    int *fila, inicio_fila = 0, fim_fila = 0;

    //Marca todos os Vértices como não visitados
    for(i = 0; i < grafo->numero_vertices; i++) {
        visitado[i] = 0;
    }

    numero_vertices = grafo->numero_vertices;
    fila = (int*) malloc(numero_vertices * sizeof(int) ); //Aloca a fila para controlar de visitação

    fim_fila++;
    fila[fim_fila] = inicio; //Coloca o Vértice inicial no fim da fila
    visitado[inicio] = cont; //Marca a ordem de visitação do vértice inicio

    //Inicia a busca enquanto houver vértices na fila
    while(inicio_fila != fim_fila) {
        //Remove um vértice da fila e incrementa o contador de visitação
        inicio_fila = (inicio_fila + 1) % numero_vertices;
        vertice = fila[inicio_fila];
        cont++;

        //Para cada vizinho de vertice
        for(i = 0; i < grafo->grau[vertice]; i++) {
            //Verifica se o vizinho de vertice já foi visitado
            if( !visitado[grafo->arestas[vertice][i]] ) {
                //Caso não tenha sido visitado, é inserido no final da fila e marcado como visitado (na ordem)
                fim_fila = (fim_fila + 1) % numero_vertices;
                fila[fim_fila] = grafo->arestas[vertice][i];
                visitado[grafo->arestas[vertice][i]] = cont;
            }
        }
    }

    free(fila);
}

int numero_vertices(Grafo *grafo) {
    return grafo->numero_vertices;
}

//Função Auxiliar para Menor Caminho entre dois Vértices utilizando o Algoritmo de Dijkstra
int procura_menor_distancia_dijkstra(float *distancia, int *visitado, int numero_vertices) {
    int i, menor = -1, primeiro = 1;

    for(i = 0; i < numero_vertices; i++) {
        if(distancia[i] >= 0 && visitado[i] == 0) { //Verifica se a distância[i] é não-negativa e se o vértice não foi visitado
            if(primeiro) { //Se for o primeiro, considera como menor distância até então
                menor = i;
                primeiro = 0;
            }
            else {
                if(distancia[menor] > distancia[i]) { //Verifica se a distância atual é menor que a distância atualmente marcada como menor
                    menor = i; //Se for, menor recebe o índice da menor distância
                }
            }
        }
    }

    return menor;
}

//Função Principal para Menor Caminho entre dois Vértices utilizando o Algoritmo de Dijkstra
void menor_caminho_grafo_dijkstra(Grafo *grafo, int inicial, int *antecessor, float *distancia) {
    int i, cont, numero_vertices, indice, *visitado, vertice;
    cont = numero_vertices = grafo->numero_vertices;
    visitado = (int*) malloc(numero_vertices * sizeof(int));

    //Marcando todos os vértices como não possuindo antecessor, distância de -1 e não-visitados
    for(i = 0; i < numero_vertices; i++) {
        antecessor[i] = -1;
        distancia[i] = -1;
        visitado[i] = 0;
    }

    distancia[inicial] = 0; //A distância do vértice inicial para ele mesmo é igual a 0

    while(cont > 0) {
        vertice = procura_menor_distancia_dijkstra(distancia, visitado, numero_vertices); //Procura o vértice com menor distância que ainda não foi visitado

        //Caso o índice do vértice seja inválido, encerra a busca
        if(vertice == -1) {
            break;
        }

        //Marca o Vértice como visitado e diminui o número de vértices a serem visitados
        visitado[vertice] = 1;
        cont--;

        //Para cada vizinho de vertice
        for(i = 0; i < grafo->grau[vertice]; i++) {
            indice = grafo->arestas[vertice][i];

            //Caso a distância até ele for negativa, a distância passa a ser a distância de vertice + 1 e vertice se torna o antecessor
            if(distancia[indice] < 0) {
                distancia[indice] = distancia[vertice] + 1;
                antecessor[indice] = vertice;
            }
            else {
                //Verifica se a distância de vertice + 1 é menor do que a distância atual
                if(distancia[indice] > distancia[vertice] + 1) {
                    distancia[indice] = distancia[vertice] + 1;
                    antecessor[indice] = vertice;
                }
            }
        }
    }
    
    free(visitado);
}

void menor_caminho_grafo_floyd_warshall(Grafo *grafo) {
    int numero_vertices = grafo->numero_vertices;
    int distancias[numero_vertices][numero_vertices], i, j, k;

    for(i = 0; i < numero_vertices; i++) {
        for(j = 0; j < numero_vertices; j++) {
            distancias[i][j] = grafo->arestas[i][j];
        }
    }

    for(k = 0; k < numero_vertices; k++) {
        for(i = 0; i < numero_vertices; i++) {
            for(j = 0; j < numero_vertices; j++) {
                if (distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }
            }
        }
    }

    for(i = 0; i < numero_vertices; i++) {
        for(j = 0; j < numero_vertices; j++) {
            printf("[%d][%d] - %d | ", i, j, distancias[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}

//Arvore Geradora Minima - Algoritmo de Prim
void arvore_geradora_minima_prim(Grafo *grafo, int origem, int *pai) {
    int i, j, destino, numero_vertices, primeiro;
    double menor_peso;
    numero_vertices = grafo->numero_vertices;

    //Inicialmente marcando todos os vértices como sem pai
    for(i = 0; i < numero_vertices; i++) {
        pai[i] = -1;
    }

    //O pai do vértice de origem como ele mesmo
    pai[origem] = origem;

    //Enquanto for possível achar um vértice sem pai
    while(1) {
        primeiro = 1;
        //Para todos os vértices
        for(i = 0; i < numero_vertices; i++) {
            //Verifica se já possui pai
            if(pai[i] != -1) {
                //Caso sim, percorrer suas arestas procurando vértices vizinhos
                for(j = 0; j < grafo->grau[i]; j++) {
                    //Verifica se o vizinho possui pai
                    if(pai[grafo->arestas[i][j]] == -1) {
                        //Caso seja o primeiro vértice que não possui pai
                        if(primeiro) {
                            //Considera este como tendo o menor peso
                            menor_peso = grafo->pesos[i][j];
                            //Guarda os vértices de origem e de destino
                            origem = i;
                            destino = grafo->arestas[i][j];
                            //Já não é mais o primeiro
                            primeiro = 0;
                        }
                        //Caso não seja o primeiro vértice que não possui pai
                        else {
                            //Verifica se o peso da aresta é menor do que a da aresta atual
                            if(menor_peso > grafo->pesos[i][j]) {
                                //Caso sim, guardar a aresta e os vértices de origem e de destino
                                menor_peso = grafo->pesos[i][j];
                                origem = i;
                                destino = grafo->arestas[i][j];
                            }
                        }
                    }
                }
            }
        }
        //Verifica se foi possivel encontrar uma aresta de menor peso
        if(primeiro == 1) {
            break;
        }
        pai[destino] = origem;
    }
}

//Arvore Geradora Minima - Algoritmo de Kruskal
void arvore_geradora_minima_kruskal(Grafo *grafo, int origem, int *pai, int *arvore) {
    int i, j, destino, numero_vertices, primeiro;
    double menor_peso;

    numero_vertices = grafo->numero_vertices;

    //Marca todos os vertices como sem pai
    for(i = 0; i < numero_vertices; i++) {
        arvore[i] = i;
        pai[i] = -1;
    }

    //Marca o pai do vértice de origem como ele mesmo
    pai[origem] = origem;

    //Enquanto for possível achar uma aresta ligando dois vértices de árvores diferentes
    while(1) {
        primeiro = 1;

        //Para cada vértice, percorrer suas arestas procurando por vértices vizinhos de outra árvore
        for(i = 0; i < numero_vertices; i++) {
            for(j = 0; j < grafo->grau[i]; j++) {
                //Caso seja a primeira aresta encontrada, considera como a de menor peso e guarda seus vértices de origem e destino
                if(arvore[i] != arvore[ grafo->arestas[i][j] ]) {
                    if(primeiro) {
                        menor_peso = grafo->arestas[i][j];
                        origem = i;
                        destino = grafo->arestas[i][j];
                        primeiro = 0;
                    }
                    //Caso não seja a primeira aresta encontrada, verifica se o menor peso atual é maior do que a aresta que está sendo verificada.
                    else {
                        //Caso sim, considera a aresta que está sendo verificada como a de menor peso e guarda seus vértices de origem e destino
                        if(menor_peso > grafo->pesos[i][j]) {
                            menor_peso = grafo->pesos[i][j];
                            origem = i;
                            destino = grafo->arestas[i][j];
                        }
                    }

                }
            }
        }

        //Verifica se foi possivel achar uma aresta de menor peso. Caso não, encerra a execução
        if(primeiro == 1) {
            break;
        }

        //Define o vértice destino como pai do vértice de origem caso o de origem não tenha pai
        if(pai[origem] == -1) {
            pai[origem] = destino;
        }
        else {
            pai[destino] = origem;
        }

        for(i = 0; i < numero_vertices; i++) {
            if(arvore[i] == arvore[destino]) {
                arvore[i] = arvore[origem];
            }
        }
    }

}