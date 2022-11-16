#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../include/utilsv2.h"




Tuple * pontos; // Vector with the points
Cluster * clusters; // Vector with the clusters
int iterations;
int N; //Number of points
int K; //Number of clusters

static inline float euclidean_distance(Tuple p1, Tuple p2){
    return ((p2.y - p1.y)*(p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
}

void init(){

    //Initialization of points
    pontos = malloc(sizeof(struct tuple) * N);

    srand(10);
    for(int i = 0; i < N; i++){
        pontos[i].x  = (float) rand() / RAND_MAX;
        pontos[i].y = (float) rand() / RAND_MAX;
        pontos[i].cluster = -1;
    }

    //Initialization of clusters
    clusters = malloc(sizeof(struct cluster) * K);

    for(int i = 0; i < K ; i++){
        clusters[i].centroid.x = pontos[i].x;
        clusters[i].centroid.y = pontos[i].y;
        clusters[i].nr_pontos = 0;
        clusters[i].soma_x = 0;
        clusters[i].soma_y = 0;
    }

}

//Adds points to cluster
void assign_points(){
    for(int i = 0; i < N; i++){
        float min_dist = euclidean_distance(pontos[i], clusters[0].centroid); //Calcula distancia euclediana do Ponto ao primeiro cluster
        int cluster = 0;
        for(int j = 1; j < K; j++){

            float dist = euclidean_distance(pontos[i], clusters[j].centroid);
            if (min_dist > dist){
                min_dist = dist;
                cluster = j;
            }
        }

        if(pontos[i].cluster == cluster){
            clusters[cluster].soma_x += pontos[i].x;
            clusters[cluster].soma_y += pontos[i].y;
            clusters[cluster].nr_pontos++;
        }else if(pontos[i].cluster != cluster){
            //Adiciona o ponto ao novo cluster, e adiciona o seu valor a soma dos pontos do cluster
            pontos[i].cluster = cluster;
            clusters[cluster].nr_pontos++;
            clusters[cluster].soma_x += pontos[i].x;
            clusters[cluster].soma_y += pontos[i].y;
        }
    }
}

//Calculates centroids
void calculate_centroids(){
    for(int i = 0; i < K; i++){
        clusters[i].centroid.x = clusters[i].soma_x/clusters[i].nr_pontos;
        clusters[i].centroid.y = clusters[i].soma_y/clusters[i].nr_pontos;
    }
}

//Checks for convergence
int centroids_changed(Tuple * old_centroids){
    int counter = 0;
    for(int i = 0; i < K; i++){
        if(old_centroids[i].x == clusters[i].centroid.x && old_centroids[i].y == clusters[i].centroid.y)
            counter++;
    }
    if(counter == K)
        return 1;
    else
        return 0;
}


// K-Means Algorithm
void k_means(){
    iterations = 0; //Porque a primeira iteração faz parte da inicialização
    Tuple * old_centroids = malloc(sizeof(struct tuple) * K);
    assign_points(); //2. Primeiro pontos associados ao cluster
    calculate_centroids();  //3. Calculo do centroide inicial
                            // Repetição desta filosofia dentro do ciclo mas com a verificação do caso de paragem
                            // Goal : 39 ITERATIONS
    int flag = 0;
    while(!flag && iterations < 20){
        for(int i = 0; i < K ; i++){
        old_centroids[i] = clusters[i].centroid;
        clusters[i].soma_x = 0;
        clusters[i].soma_y = 0;
        clusters[i].nr_pontos = 0;
        }
        assign_points(); // Atribuir cada ponto ao respetivo cluster
        calculate_centroids(); //Calcular centroids de cada cluster
        if(centroids_changed(old_centroids) == 1) flag = 1;
        //Contador de iterações
        iterations++;
    }
    printf("N = %d, K = %d\n", N, K);
    for(int i = 0; i<K; i++)
        printf("Center: (%.3f, %.3f) : Size: %d\n", clusters[i].centroid.x, clusters[i].centroid.y, clusters[i].nr_pontos);
    printf("Iterations: %d\n", iterations);
    free(pontos);
    free(clusters);
}

int main(int argc, char * argv[]){
    N = atoi(argv[1]);
    K = atoi(argv[2]);
    float initial_time = clock();
    init();
    k_means();
    float final_time = clock();
    printf("Tempo: %f\n", (final_time - initial_time)/pow(10,6));
    return 0;
}

