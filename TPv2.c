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


typedef struct fila_prioridade FilaPrio;

struct paciente{
    char nome[30];
    int prio;
    int timedelay;
    float p;
    int repeat;
};

struct fila_prioridade{
    int qtd;
    struct paciente dados[MAX];
};

FilaPrio* cria_FilaPrio(){
    FilaPrio *fp;
    fp = (FilaPrio*) malloc(sizeof(struct fila_prioridade));
    if(fp != NULL)
        fp->qtd = 0;
    return fp;
}

void libera_FilaPrio(FilaPrio* fp){
    free(fp);
}

int consulta_FilaPrio(FilaPrio* fp, char* nome){
    if(fp == NULL || fp->qtd == 0)
        return 0;
    strcpy(nome,fp->dados[0].nome);
    return 1;
}

void promoverElemento(FilaPrio* fp, int filho){
    int pai;
    struct paciente temp;
    pai = (filho - 1) / 2;
    while((filho > 0) && (fp->dados[pai].prio >= fp->dados[filho].prio)){
        temp = fp->dados[filho];
        fp->dados[filho] = fp->dados[pai];
        fp->dados[pai] = temp;

        filho = pai;
        pai = (pai - 1) / 2;
    }
}

int insere_FilaPrio(FilaPrio* fp, char *nome, int prioridade, int td, float prob, int repeat){
    if(fp == NULL)
        return 0;
    if(fp->qtd == MAX)//fila cheia
        return 0;
    /* insere na primeira posi��o livre */
    strcpy(fp->dados[fp->qtd].nome,nome);
    fp->dados[fp->qtd].prio = prioridade;
    fp->dados[fp->qtd].timedelay = td;
    fp->dados[fp->qtd].p = prob;
    fp->dados[fp->qtd].repeat = repeat;
    /* desloca elemento para posi��o correta */
    promoverElemento(fp,fp->qtd);
    /* incrementa n�mero de elementos no heap */
    fp->qtd++;
    return 1;
}

void rebaixarElemento(FilaPrio* fp, int pai){
    struct paciente temp;
    int filho = 2 * pai + 1;
    while(filho < fp->qtd){

        if(filho < fp->qtd-1) /* verifica se tem 2 filhos */
            if(fp->dados[filho].prio < fp->dados[filho+1].prio)
                filho++; /*filho aponta para filho menor */

        if(fp->dados[pai].prio >= fp->dados[filho].prio)
            break; /* encontrou lugar */

        temp = fp->dados[pai];
        fp->dados[pai] = fp->dados[filho];
        fp->dados[filho] = temp;

        pai = filho;
        filho = 2 * pai + 1;
    }
}

int remove_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return 0;
    if(fp->qtd == 0)
        return 0;

    fp->qtd--;
    fp->dados[0] = fp->dados[fp->qtd];
    rebaixarElemento(fp,0);
    return 1;
}

int tamanho_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return -1;
    else
        return fp->qtd;
}

int estaCheia_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == MAX);
}

int estaVazia_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == 0);
}

void imprime_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return;
    int i;
    for(i=0; i < fp->qtd ; i++){
        printf("%d) Time: %d \tNome: %s",i,fp->dados[i].prio,fp->dados[i].nome);
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

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1.
 Cada elemento da matriz recebe valor val. */
static int **MATRIXint( int r, int c, int val) { 
   int **m = malloc( r * sizeof (int *));
   for (vertex i = 0; i < r; ++i) 
      m[i] = malloc( c * sizeof (int));
   for (vertex i = 0; i < r; ++i)
      for (vertex j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
    for(int i = 0; i<20;i++){
        G->eventoatual[i] = "S";
    }
   return G;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinsertArc() insere um arco v-w no grafo G. 
A função supõe que v e w são distintos, positivos e menores que G->V. 
Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHremoveArc() remove do grafo G o arco v-w. 
A função supõe que v e w são distintos, positivos e menores que G->V. 
Se não existe arco v-w, a função não faz nada. */
void GRAPHremoveArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHshow() imprime, para cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */
void GRAPHshow( Graph G) { 
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
void simulacaoEvento(Graph G, FilaPrio* fp, int tempofinal){
   printf("Rodando a simulacao\n");
   int contadorR = 0, contadorI=0;
   int dt=1;
   for (int tempo = dt; tempo <= tempofinal; tempo+=dt){
      printf("t: (%d)\n",tempo);
      struct paciente e = fp->dados[0];
      //printf("e.time:%d\n",e.prio);
      //printf("e.nome: %s\n",e.nome);
      //printf("e.p:%f\n",e.p);
      //printf("e.repeat: %d\n",e.repeat);
      //printf("e.timedelay:%d\n",e.timedelay);
      //char *I = "I";
      //char *R = "R";
      //char *EventoX = "X";
      //char *S = "S";
      printaEvento(G);
      while(e.prio < tempo){
         /* srand(time(NULL)); // para o computador gerar o numero mais aleatorio possivel, isso é, não repetir sempre os mesmos numeros gerados
         float x = rand()%10; // gerando um numero aleatorio entre 0 e 10
         float randnprob = x/10; // dividindo o numero aleatorio por 10 para chegar no valor desejado entre 0 e 1 */
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
                  } else if((strcmp(G->eventoatual[i],"I") == 0) && (strcmp(e.nome,"R") == 0) ){ //(strcmp(G->eventoatual[i],I) == 0) && (strcmp(e.nome[i],R) == 0)
                    G->eventoatual[i] = "R";
                  }  
               } 
            } 
        
         remove_FilaPrio(fp);
         if(e.repeat == 1){
            e.prio = tempo + e.timedelay;
            insere_FilaPrio(fp,e.nome,e.prio,e.timedelay,e.p,e.repeat);  
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
    struct paciente itens[2] = {{"I",1,1,0.7,1},
                                {"R",5,5,0.4,1}};
    int tempofinal = 30; // tempo em dias da simulacao
    FilaPrio* fp;
    fp = cria_FilaPrio();
    Graph grafo = GRAPHinit(20);

    GRAPHinsertArc(grafo,0,1); 
    GRAPHinsertArc(grafo,0,4); 
    GRAPHinsertArc(grafo,1,0); 
    GRAPHinsertArc(grafo,1,2);
    GRAPHinsertArc(grafo,1,5); 
    GRAPHinsertArc(grafo,2,1); 
    GRAPHinsertArc(grafo,2,3); 
    GRAPHinsertArc(grafo,2,6); 
    GRAPHinsertArc(grafo,3,2); 
    GRAPHinsertArc(grafo,3,7); 
    GRAPHinsertArc(grafo,4,0); 
    GRAPHinsertArc(grafo,4,5); 
    GRAPHinsertArc(grafo,4,8);  
    GRAPHinsertArc(grafo,5,1);
    GRAPHinsertArc(grafo,5,4);
    GRAPHinsertArc(grafo,5,6);
    GRAPHinsertArc(grafo,5,9);
    GRAPHinsertArc(grafo,6,2);
    GRAPHinsertArc(grafo,6,5);
    GRAPHinsertArc(grafo,6,7);
    GRAPHinsertArc(grafo,6,10); 
    GRAPHinsertArc(grafo,7,3);
    GRAPHinsertArc(grafo,7,6);
    GRAPHinsertArc(grafo,7,11);
    GRAPHinsertArc(grafo,8,4);
    GRAPHinsertArc(grafo,8,9);
    GRAPHinsertArc(grafo,8,12);
    GRAPHinsertArc(grafo,9,5);
    GRAPHinsertArc(grafo,9,8);
    GRAPHinsertArc(grafo,9,10);
    GRAPHinsertArc(grafo,9,13);
    GRAPHinsertArc(grafo,10,6);
    GRAPHinsertArc(grafo,10,9);
    GRAPHinsertArc(grafo,10,11);
    GRAPHinsertArc(grafo,10,14);
    GRAPHinsertArc(grafo,11,7);
    GRAPHinsertArc(grafo,11,10);
    GRAPHinsertArc(grafo,11,15);
    GRAPHinsertArc(grafo,12,8);
    GRAPHinsertArc(grafo,12,13);
    GRAPHinsertArc(grafo,12,16);
    GRAPHinsertArc(grafo,13,9);
    GRAPHinsertArc(grafo,13,12);
    GRAPHinsertArc(grafo,13,14);
    GRAPHinsertArc(grafo,13,17);
    GRAPHinsertArc(grafo,14,10);
    GRAPHinsertArc(grafo,14,13);
    GRAPHinsertArc(grafo,14,15);
    GRAPHinsertArc(grafo,14,18);
    GRAPHinsertArc(grafo,15,11);
    GRAPHinsertArc(grafo,15,14);
    GRAPHinsertArc(grafo,15,19);
    GRAPHinsertArc(grafo,16,12);
    GRAPHinsertArc(grafo,16,17);
    GRAPHinsertArc(grafo,17,13);
    GRAPHinsertArc(grafo,17,16);
    GRAPHinsertArc(grafo,17,18);
    GRAPHinsertArc(grafo,18,14);
    GRAPHinsertArc(grafo,18,17);
    GRAPHinsertArc(grafo,18,19);
    GRAPHinsertArc(grafo,19,15);
    GRAPHinsertArc(grafo,19,18); // associa os vértices para fazer as ligacoes desejadas

    grafo->eventoatual[10] = "I";
    GRAPHshow(grafo); 

    int i;
    for (i=0; i< 2; i++){
        printf("%d) %d %s\n",i,itens[i].prio, itens[i].nome);
        insere_FilaPrio(fp,itens[i].nome,itens[i].prio,itens[i].timedelay,itens[i].p,itens[i].repeat);
    }

    printf("=================================\n");

    simulacaoEvento(grafo,fp,tempofinal);
    
    //grafo->eventoatual[4] = "R";
    //printaEvento(grafo);

    imprime_FilaPrio(fp);



    printf("=================================\n");

    libera_FilaPrio(fp);

    system("pause");
    return 0;
}
