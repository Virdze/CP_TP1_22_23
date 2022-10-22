#include <stdio.h>
#include <stdlib.h>

#define N 10000000 //Numero de amostras
#define K 4 //Number of clusters

typedef struct tuple{
    float x;
    float y;
} Tuple;

Tuple * pontos;
Tuple * clusters;

void init(){  
    pontos = malloc(sizeof(struct tuple) * N);
    clusters = malloc(sizeof(struct tuple) * K);
    srand(10);
    for(int i = 0; i < N; i++){
        pontos[i].x = (float) rand() / RAND_MAX;
        pontos[i].y = (float) rand() / RAND_MAX;
    }
    for(int i = 0; i < K ; i++){
        clusters[i].x = pontos[i].x;
        clusters[i].y = pontos[i].y;
    }   
}


//void k_means(){}


void main(){
    init();
    //k_means();
    printf("Ok");
    for(int i = 0; i<K; i++)
        printf("(%f,%f)\n", clusters[i].x, clusters[i].y);
}