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
#define vertex int
#define max 20

typedef struct TEvento{
    char *nome;
    float p; // probabilidade
    int timedelay;// infeccao 1, recuperacao 5
    int time;
    int repeat; // 0 nao, 1 sim
} Evento;

typedef struct TFila{
   int qtd;
   Evento eventos[max];
} Fila; //criando a struct para fila de prioridade

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa um grafo. 
O campo adj é um ponteiro para a matriz de adjacências do grafo. 
O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
typedef struct graph {
   int V; 
   int A; 
   int **adj; 
   char eventoatual[max];
} *Graph;
/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */

Fila* criaFila(){
   Fila *fp;
   fp = (Fila*) malloc(sizeof(struct TFila));
   if(fp != NULL)
        fp->qtd = 0;
    return fp;
}

void ordenarElemento(Fila* fp, int filho){
   int pai;
   struct TEvento aux;
   pai = (filho-1)/2;
   while((filho > 0) && (fp->eventos[pai].time <= fp->eventos[filho].time)){
      aux = fp->eventos[filho];
      fp->eventos[filho] = fp->eventos[pai];
      fp->eventos[pai] = aux;
      filho = pai;
      pai = (pai-1)/2;
   }
}

/*
int t - time
int td - timedelay
float p - probabilidade
int r - repeat
*/
int insereFila(Fila* fp, char *nome, int t, int td, float p, int r){
   if(fp == NULL)
        return 0;
    if(fp->qtd == max)//fila cheia
        return 0;
   //insere primeira posicao livre
   strcpy(fp->eventos[fp->qtd].nome,nome);
   fp->eventos[fp->qtd].time = t;
   fp->eventos[fp->qtd].timedelay = td;
   fp->eventos[fp->qtd].p = p;
   fp->eventos[fp->qtd].repeat = r;

   //desloca para a posicao correta
   ordenarElemento(fp,fp->qtd);

   //aumenta numero de elementos
   fp->qtd++;
   return 1;
}

void rebaixarElemento(Fila* fp, int pai){
    struct TEvento aux;
    int filho = 2 * pai + 1;
    while(filho < fp->qtd){

        if(filho < fp->qtd-1) /* verifica se tem 2 filhos */
            if(fp->eventos[filho].time < fp->eventos[filho+1].time)
                filho++; /*filho aponta para filho menor */

        if(fp->eventos[pai].time >= fp->eventos[filho].time)
            break; /* encontrou lugar */

        aux = fp->eventos[pai];
        fp->eventos[pai] = fp->eventos[filho];
        fp->eventos[filho] = aux;

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
    fp->eventos[0] = fp->eventos[fp->qtd];
    rebaixarElemento(fp,0);
    return 1;
}

int estaVaziaFila(Fila* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == 0);
}

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
        G->eventoatual[i] = 'S';
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
      printf("Evento: (%d) - %c\n",i,G->eventoatual[i]); 
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
      Evento e = fp->eventos[0];
      printf("e.time:%d\n",e.time);
      printf("e.nome: %s\n",e.nome);
      printf("e.p:%f\n",e.p);
      printf("e.repeat: %d\n",e.repeat);
      printf("e.timedelay:%d\n",e.timedelay);
      char *I = "I";
      char *R = "R";
      char *S = "S";
      while(e.time <= tempo){
         /* srand(time(NULL)); // para o computador gerar o numero mais aleatorio possivel, isso é, não repetir sempre os mesmos numeros gerados
         float x = rand()%10; // gerando um numero aleatorio entre 0 e 10
         float randnprob = x/10; // dividindo o numero aleatorio por 10 para chegar no valor desejado entre 0 e 1 */
            for(int i = 0 ; i<20; i++){
               for(int j = 0; j<20; j++){ 
                  printf("ola\n"); 
                  srand(time(NULL)); // para o computador gerar o numero mais aleatorio possivel, isso é, não repetir sempre os mesmos numeros gerados
                  float x = 0;
                  x = rand()%10; // gerando um numero aleatorio entre 0 e 10
                  float randnprob = 0;
                  randnprob = x/10;  // dividindo o numero aleatorio por 10 para chegar no valor desejado entre 0 e 1
                  printf("numero aleatorio gerado:%f, numero aleatorio predefindo: %f\n",randnprob,e.p);
                  if(randnprob > e.p ){ // (strcmp(G->eventoatual[i],R) == 0) && (strcmp(G->eventoatual[j],I) == 0) && G->adj[i][j] == 1 && (strcmp(e.nome[i],I) == 0) &&
                     char *EventoX;
                     EventoX = G->eventoatual[i];
                     strcpy(EventoX,I);
                     printaEvento(G);
                  }  
                  if(randnprob < e.p){ //(strcmp(G->eventoatual[i],I) == 0) && (strcmp(e.nome[i],R) == 0)
                     char *EventoX;
                     EventoX = G->eventoatual[i];
                     strcpy(EventoX,R);
                     printaEvento(G);
                  }  
               } 
            }
         
         removeFila(fp);
         if(e.repeat == 1){
            e.time = tempo + e.timedelay;
            insereFila(fp,e.nome,e.time,e.timedelay,e.p,e.repeat);   
         }
         e = fp->eventos[0];
      }
      for(int i = 0; i<20; i++){
         char *EventoX;
         EventoX = G->eventoatual[i];
         if((strcmp(EventoX,R) == 0)){
            contadorR++;
         } else if((strcmp(EventoX,I) == 0)){
            contadorI++;
         }
      }
      int PorcI = contadorI/20;
      int PorcR = contadorR/20;
      printf("Porcentagem infectados: %f %% \n",PorcI/20);
      printf("Porcentagem recuperados: %f %%\n",PorcR/20);
   }
   
   printf("Terminou a simulacao\n");
}

void imprime_FilaPrio(Fila* fp){
    if(fp == NULL)
        return;
    int i;
    for(i=0; i < fp->qtd ; i++){
        printf("%d) Prio: %d \tNome: %s\n",i,fp->eventos[i].time,fp->eventos[i].nome);
    }
}


int main(){

   int tempofinal = 30; // tempo em dias da simulacao
   Fila* fp; // fila de prioridade
   fp = criaFila();
   Graph grafo = GRAPHinit(20); // inicia o grafo com 20 vértices, valor padrao escolhida pela dupla
   char *I = "I";
   char *R = "R";
   char *S = "S";

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

   GRAPHshow(grafo);   

   Evento infec;
   infec.nome = "I";
   infec.p = 0.5;
   infec.repeat=1;
   infec.time=1;
   infec.timedelay=1;

   Evento recup;
   recup.nome ="R";
   recup.p = 0.4;
   recup.repeat = 1;
   recup.time =5;
   recup.timedelay=5;

   insereFila(fp,infec.nome,infec.time,infec.timedelay,infec.p,infec.repeat);
   //insereFila(fp,recup.nome,recup.time,recup.timedelay,recup.p,recup.repeat);
   
   imprime_FilaPrio(fp);

   simulacaoEvento(grafo,fp,tempofinal);

   return 0;
}