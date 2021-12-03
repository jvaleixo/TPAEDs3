/*
    
    TP1 - AEDs 3
    Juan Victor Costa Silva Aleixo - 202050025
    Samanta Ribeiro Freire - 192050022
   

*/

#include <stdio.h>
#include <stdlib.h> 

typedef struct TEvento{
    char *nome;
    float p; // probabilidade
    int timedelay;
    int time;
    int repeat; // 0 nao, 1 sim
} Evento;
typedef struct TVertice{
    int id;
    char *estado; 
} Vertice;
typedef struct TAresta{
    Vertice* origem;
    Vertice* destino;
} Aresta;
typedef struct TGrafo{
  int dir;       		//0 não direcionado, 1 direcionado, -1 grafo nao criado
  int qv;    		    //quantidade de vértices
  Vertice vertices[20];
  Aresta arestas[400];
  int **matrizadj; //matriz de adjacência alocada dinamicamente
} Grafo;

Grafo* criaGrafo(int dir, int qv){
    Grafo* g = (Grafo*) malloc(sizeof(Grafo)); 
    g->dir = dir; 
    g->qv = qv; 
    //Aloca a matriz |V|x|V| 
    g->matrizadj = (int**) malloc(qv*sizeof(int*));
    for (int i = 0; i < qv; i++)
        g->matrizadj[i] = (int*) malloc(qv*sizeof(int));
    return g; 
}

void inicializaMatrizAdj(Grafo* g){
    for (int i = 0; i < g->qv; i++) 
        for (int j = 0; j < g->qv; j++)
            g->matrizadj[i][j] = 0;
}
void criaVertice(Grafo* g, int v, char *estado){
    g->vertices[v].estado= estado;
}
void imprimeVertice(Grafo* g){ 
    for (int i = 1; i <= g->qv; i++) {
        printf("Vértice: %d - estado: %c\n",i, g->vertices[i].estado);
    }
}
void criaAresta(Grafo* g, int u, int v, int ligacao){
    if (u < 0 || u >= g->qv) return;
    if (v < 0 || v >= g->qv) return;
    g->arestas->origem->id = u;
    g->arestas->destino->id = v;
    if (g->dir)
        g->matrizadj[u][v] = ligacao; 
    else {
        g->matrizadj[u][v] = ligacao; 
        g->matrizadj[v][u] = ligacao; 
    } 
}

void imprimeMatrizAdj(Grafo* g){
    printf("Matriz de adjacência:\n"); 
    for (int i = 0; i < g->qv; i++) {
        for (int j = 0; j < g->qv; j++)
            printf(" %d ", g->matrizadj[i][j]);
        printf("\n");
    }
}

void liberaGrafo(Grafo *g){
    for (int i = 0; i < g->qv; i++) 
        free(g->matrizadj[i]);
    free(g->matrizadj); 
    free(g); 
}

int main(){
    int qv, dir,v; 
    char *estado;
    /* printf("Qual a quantidade de vertices do grafo:\n"); 
    scanf("%d", &qv);
    printf("O grafo é direcionado (1) ou não (0):\n");
    scanf("%d", &dir);

    if (qv <= 0){
        printf("Digite um valor válido para a quantidade de vertices\n");
        exit(1); 
    }
    if (dir != 0 && dir != 1){
        printf("Digite um valor válido para o tipo de grafo\n");
        exit(1); 
    }

    Grafo* grafo = criaGrafo(dir,qv); 
    inicializaMatrizAdj(grafo); 
    int u = 0, v, ligacao; 
    while (u != -1){
        printf("Digite os vertices de origem, destino e o peso da aresta (origem -1 para sair):\n");         
        scanf("%d %d %d", &u, &v, &ligacao);
        criaAresta(grafo,u,v,ligacao);         
    }
    imprimeMatrizAdj(grafo);*/
    
    dir = 0;
    qv = 4;
    Grafo* grafo = criaGrafo(dir,qv); 
    printf("%d\n",grafo->qv);
    while (v != -1){
        printf("digite o vertice (-1 para sair)\n");
        scanf("%d",&v);
        printf("digite o estado desejado\n");
        scanf("%s",&estado);
        criaVertice(grafo,v,estado);
    }

    imprimeVertice(grafo);
    liberaGrafo(grafo);

    return 0; 
}
