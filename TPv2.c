/*
    
   TP1 - AEDs 3
   Juan Victor Costa Silva Aleixo - 202050025
   Samanta Ribeiro Freire - 192050022
   
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX 100
#define vertex int


typedef struct fila_prioridade Fila;

struct evento{
    char nome[30];
    int time;
    int timedelay;
    float p;
    int repeat;
};

struct fila_prioridade{
    int qtd;
    struct evento dados[MAX];
};

Fila* criaFila(){
    Fila *fp;
    fp = (Fila*) malloc(sizeof(struct fila_prioridade));
    if(fp != NULL)
        fp->qtd = 0;
    return fp;
}

void liberaFila(Fila* fp){
    free(fp);
}

int consultaFila(Fila* fp, char* nome){
    if(fp == NULL || fp->qtd == 0)
        return 0;
    strcpy(nome,fp->dados[0].nome);
    return 1;
}

void ordenarElemento(Fila* fp, int filho){
    int pai;
    struct evento temp;
    pai = (filho - 1) / 2;
    while((filho > 0) && (fp->dados[pai].time >= fp->dados[filho].time)){
        temp = fp->dados[filho];
        fp->dados[filho] = fp->dados[pai];
        fp->dados[pai] = temp;

        filho = pai;
        pai = (pai - 1) / 2;
    }
}

int insereFila(Fila* fp, char *nome, int time, int td, float prob, int repeat){
    if(fp == NULL)
        return 0;
    if(fp->qtd == MAX)//fila cheia
        return 0;
    /* insere na primeira posi��o livre */
    strcpy(fp->dados[fp->qtd].nome,nome);
    fp->dados[fp->qtd].time = time;
    fp->dados[fp->qtd].timedelay = td;
    fp->dados[fp->qtd].p = prob;
    fp->dados[fp->qtd].repeat = repeat;
    /* desloca elemento para posi��o correta */
    ordenarElemento(fp,fp->qtd);
    /* incrementa n�mero de elementos no heap */
    fp->qtd++;
    return 1;
}

void rebaixarElemento(Fila* fp, int pai){
    struct evento temp;
    int filho = 2 * pai + 1;
    while(filho < fp->qtd){

        if(filho < fp->qtd-1) /* verifica se tem 2 filhos */
            if(fp->dados[filho].time < fp->dados[filho+1].time)
                filho++; /*filho aponta para filho menor */

        if(fp->dados[pai].time >= fp->dados[filho].time)
            break; /* encontrou lugar */

        temp = fp->dados[pai];
        fp->dados[pai] = fp->dados[filho];
        fp->dados[filho] = temp;

        pai = filho;
        filho = 2 * pai + 1;
    }
}

int removeFila(Fila* fp){
    if(fp == NULL)
        return 0;
    if(fp->qtd == 0)
        return 0;

    fp->qtd--;
    fp->dados[0] = fp->dados[fp->qtd];
    rebaixarElemento(fp,0);
    return 1;
}

int tamanhoFila(Fila* fp){
    if(fp == NULL)
        return -1;
    else
        return fp->qtd;
}

int estaCheiaFila(Fila* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == MAX);
}

int estaVaziaFila(Fila* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == 0);
}

void imprimeFila(Fila* fp){
    if(fp == NULL)
        return;
    int i;
    for(i=0; i < fp->qtd ; i++){
        printf("%d) Time: %d \tNome: %s",i,fp->dados[i].time,fp->dados[i].nome);
        printf("\tTimeDelay: %d \tProbabilidade: %f",fp->dados[i].timedelay,fp->dados[i].p);
        printf("\tRepeat: %d\n",fp->dados[i].repeat);
    }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa um grafo. 
O campo adj é um ponteiro para a matriz de adjacências do grafo. 
O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
typedef struct graph {
   int V; 
   int A; 
   int **adj; 
   char *eventoatual[MAX];
} *Graph;
/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função iniciaMatriz() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1.
 Cada elemento da matriz recebe valor val. */
static int **iniciaMatriz( int r, int c, int val) { 
   int **m = malloc( r * sizeof (int *));
   for (vertex i = 0; i < r; ++i) 
      m[i] = malloc( c * sizeof (int));
   for (vertex i = 0; i < r; ++i)
      for (vertex j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função iniciaGrafo() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph iniciaGrafo( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = iniciaMatriz( V, V, 0);
    for(int i = 0; i<20;i++){
        G->eventoatual[i] = "S";
    }
   return G;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função inserirligacaoGrafo() insere um arco v-w no grafo G. 
A função supõe que v e w são distintos, positivos e menores que G->V. 
Se o grafo já tem um arco v-w, a função não faz nada. */
void inserirligacaoGrafo( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função removerligacaoGrafo() remove do grafo G o arco v-w. 
A função supõe que v e w são distintos, positivos e menores que G->V. 
Se não existe arco v-w, a função não faz nada. */
void removerligacaoGrafo( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função printaGrafo() imprime, para cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */
void printaGrafo( Graph G) { 
   printf("Ligacoes dos vertices do grafo:\n");
   for (vertex v = 0; v < G->V; ++v) {
      printf( "%2d:", v);
      for (vertex w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1) 
            printf( " %2d", w);
      printf( "\n");
   }
}

/* Percorre o vetor de eventoatual para printar o valor de cada vertice, 
o indice do vetor indica a qual vertice esse valor ta relacionado
posicao 0 é o vertice 0, por exemplo
*/
void printaEvento(Graph G){
   printf("\n");
   for(int i = 0; i<20; i++){
     printf("Evento: (%d) - %s\n",i,G->eventoatual[i]); 
   }
}


/*
Graph G - Grafo em questao
Fila fp - Fila de prioridade
int tempofinal - Tempo em dias da simulacao
*/
void simulacaoEvento(Graph G, Fila* fp, int tempofinal){
   printf("Rodando a simulacao\n");
   int contadorR = 0, contadorI=0;
   int dt=1;
   for (int tempo = dt; tempo <= tempofinal; tempo+=dt){
      printf("t: (%d)\n",tempo);
      struct evento e = fp->dados[0];
      //printf("e.time:%d\n",e.prio);
      //printf("e.nome: %s\n",e.nome);
      //printf("e.p:%f\n",e.p);
      //printf("e.repeat: %d\n",e.repeat);
      //printf("e.timedelay:%d\n",e.timedelay);
      //char *I = "I";
      //char *R = "R";
      //char *EventoX = "X";
      //char *S = "S";
      while(e.time <= tempo){
         /* srand(time(NULL)); // para o computador gerar o numero mais aleatorio possivel, isso é, não repetir sempre os mesmos numeros gerados
         float x = rand()%10; // gerando um numero aleatorio entre 0 e 10
         float randnprob = x/10; // dividindo o numero aleatorio por 10 para chegar no valor desejado entre 0 e 1 */
            FILE *pont_arq;
            for(int i = 0 ; i<20; i++){
               for(int j = 0; j<20; j++){ 
                  //printf("ola\n"); 
                  srand(time(NULL)); // para o computador gerar o numero mais aleatorio possivel, isso é, não repetir sempre os mesmos numeros gerados
                  float x = 0;
                  x = rand()%10; // gerando um numero aleatorio entre 0 e 10
                  float randnprob = 0;
                  randnprob = x/10;  // dividindo o numero aleatorio por 10 para chegar no valor desejado entre 0 e 1
                  //printf("numero aleatorio gerado:%f, numero aleatorio predefindo: %f\n",randnprob,e.p);
                  if((strcmp(G->eventoatual[i],"S") == 0) && (strcmp(G->eventoatual[j],"I") == 0) && G->adj[i][j] == 1 && (e.p > randnprob) && (strcmp(e.nome,"I") == 0)){ // (strcmp(G->eventoatual[i],R) == 0) && (strcmp(G->eventoatual[j],I) == 0) && G->adj[i][j] == 1 && (strcmp(e.nome[i],I) == 0) &&
                    G->eventoatual[i] = "I";
                  } else if((strcmp(G->eventoatual[i],"I") == 0) && (strcmp(e.nome,"R") == 0) && (e.p > randnprob)){ //(strcmp(G->eventoatual[i],I) == 0) && (strcmp(e.nome[i],R) == 0)
                    G->eventoatual[i] = "R";
                  }  
               } 
               pont_arq = fopen("resultados.txt","w");
               fprintf(pont_arq,G->eventoatual[i]);
            } 
        printaEvento(G);
        fclose(pont_arq);
        removeFila(fp);
        if(e.repeat == 1){
            e.time = tempo + e.timedelay;
            insereFila(fp,e.nome,e.time,e.timedelay,e.p,e.repeat);  
        }
        e = fp->dados[0];
      }
   }
    for(int i = 0; i<20; i++){
        if((strcmp(G->eventoatual[i],"R") == 0)){
            contadorR++;
        } else if((strcmp(G->eventoatual[i],"I") == 0)){
            contadorI++;
            }
    }
    float PorcI = (contadorI/0.20);
    float PorcR = (contadorR/0.20);
    printf("Porcentagem infectados: %.2f %% \n", PorcI);
    printf("Porcentagem recuperados: %.2f %%\n", PorcR);
    printf("Terminou a simulacao\n");

} 

int main(){
    
    struct evento eventos[2] = {{"I",1,1,0.70,1},
                                {"R",5,5,0.20,1}};
    int tempofinal = 30; // tempo em dias da simulacao
    Fila* fp;
    fp = criaFila();
    Graph grafo = iniciaGrafo(20);

    inserirligacaoGrafo(grafo,0,1); 
    inserirligacaoGrafo(grafo,0,4); 
    inserirligacaoGrafo(grafo,1,0); 
    inserirligacaoGrafo(grafo,1,2);
    inserirligacaoGrafo(grafo,1,5); 
    inserirligacaoGrafo(grafo,2,1); 
    inserirligacaoGrafo(grafo,2,3); 
    inserirligacaoGrafo(grafo,2,6); 
    inserirligacaoGrafo(grafo,3,2); 
    inserirligacaoGrafo(grafo,3,7); 
    inserirligacaoGrafo(grafo,4,0); 
    inserirligacaoGrafo(grafo,4,5); 
    inserirligacaoGrafo(grafo,4,8);  
    inserirligacaoGrafo(grafo,5,1);
    inserirligacaoGrafo(grafo,5,4);
    inserirligacaoGrafo(grafo,5,6);
    inserirligacaoGrafo(grafo,5,9);
    inserirligacaoGrafo(grafo,6,2);
    inserirligacaoGrafo(grafo,6,5);
    inserirligacaoGrafo(grafo,6,7);
    inserirligacaoGrafo(grafo,6,10); 
    inserirligacaoGrafo(grafo,7,3);
    inserirligacaoGrafo(grafo,7,6);
    inserirligacaoGrafo(grafo,7,11);
    inserirligacaoGrafo(grafo,8,4);
    inserirligacaoGrafo(grafo,8,9);
    inserirligacaoGrafo(grafo,8,12);
    inserirligacaoGrafo(grafo,9,5);
    inserirligacaoGrafo(grafo,9,8);
    inserirligacaoGrafo(grafo,9,10);
    inserirligacaoGrafo(grafo,9,13);
    inserirligacaoGrafo(grafo,10,6);
    inserirligacaoGrafo(grafo,10,9);
    inserirligacaoGrafo(grafo,10,11);
    inserirligacaoGrafo(grafo,10,14);
    inserirligacaoGrafo(grafo,11,7);
    inserirligacaoGrafo(grafo,11,10);
    inserirligacaoGrafo(grafo,11,15);
    inserirligacaoGrafo(grafo,12,8);
    inserirligacaoGrafo(grafo,12,13);
    inserirligacaoGrafo(grafo,12,16);
    inserirligacaoGrafo(grafo,13,9);
    inserirligacaoGrafo(grafo,13,12);
    inserirligacaoGrafo(grafo,13,14);
    inserirligacaoGrafo(grafo,13,17);
    inserirligacaoGrafo(grafo,14,10);
    inserirligacaoGrafo(grafo,14,13);
    inserirligacaoGrafo(grafo,14,15);
    inserirligacaoGrafo(grafo,14,18);
    inserirligacaoGrafo(grafo,15,11);
    inserirligacaoGrafo(grafo,15,14);
    inserirligacaoGrafo(grafo,15,19);
    inserirligacaoGrafo(grafo,16,12);
    inserirligacaoGrafo(grafo,16,17);
    inserirligacaoGrafo(grafo,17,13);
    inserirligacaoGrafo(grafo,17,16);
    inserirligacaoGrafo(grafo,17,18);
    inserirligacaoGrafo(grafo,18,14);
    inserirligacaoGrafo(grafo,18,17);
    inserirligacaoGrafo(grafo,18,19);
    inserirligacaoGrafo(grafo,19,15);
    inserirligacaoGrafo(grafo,19,18); // associa os vértices para fazer as ligacoes desejadas


    grafo->eventoatual[10] = "I";

    
    printaGrafo(grafo); 

    int i;
    for (i=0; i< 2; i++){
        printf("%d) %d %s\n",i,eventos[i].time, eventos[i].nome);
        insereFila(fp,eventos[i].nome,eventos[i].time,eventos[i].timedelay,eventos[i].p,eventos[i].repeat);
    }

    printf("=================================\n");

    simulacaoEvento(grafo,fp,tempofinal);
    


    //grafo->eventoatual[4] = "R";
    //printaEvento(grafo);

    imprimeFila(fp);



    printf("=================================\n");

    liberaFila(fp);

    return 0;

}
