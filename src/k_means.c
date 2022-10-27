#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utils.h"


#define N 10000000 //Numero de amostras
#define K 4 //Number of clusters

Tuple * pontos; // Vetor com os pontos
Cluster * clusters; // Vetor com os clusters
int iterations;


void init(){

    //Inicialização do vetor de pontos
    pontos = malloc(sizeof(struct tuple) * N); 
    
    srand(10);
    for(int i = 0; i < N; i++){
        pontos[i].x  = (float) rand() / RAND_MAX;
        pontos[i].y = (float) rand() / RAND_MAX;
    }


    //Inicialização dos clusters
    clusters = malloc(sizeof(struct cluster) * K);

    for(int i = 0; i < K ; i++){
        clusters[i].pontos = NULL;
        clusters[i].centroid.x = pontos[i].x;
        clusters[i].centroid.y = pontos[i].y;
        clusters[i].nr_pontos = 0;
    }

}

void add_point_to_cluster(Tuple point,int cluster_number){
    int n = clusters[cluster_number].nr_pontos;

    if(clusters[cluster_number].pontos == NULL){
        clusters[cluster_number].pontos = malloc(sizeof(int));
        clusters[cluster_number].pontos[n] = point;
        //printf("(%f,%f)\n", clusters[cluster_number].pontos[n].x,clusters[cluster_number].pontos[n].x);
        clusters[cluster_number].nr_pontos++;
    }
    else{
        clusters[cluster_number].pontos = realloc(clusters[cluster_number].pontos, sizeof(struct tuple) * (n+1));
        clusters[cluster_number].pontos[n] = point;
        //printf("(%f,%f)\n", clusters[cluster_number].pontos[n].x,clusters[cluster_number].pontos[n].x);
        clusters[cluster_number].nr_pontos++;
    }

}

//Adiciona pontos ao cluster correto
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
            add_point_to_cluster(pontos[i],cluster);
    }
    
}

void update_cluster_centroid(int cluster_number){

    float acc_x = 0, // Acumulador para todas os x dos pontos associados ao cluster
        acc_y = 0; // Acumulador para todas os y dos pontos associados ao cluster


    for(int i = 0; i < clusters[cluster_number].nr_pontos ; i++){
        acc_x += clusters[cluster_number].pontos[i].x;
        acc_y += clusters[cluster_number].pontos[i].y;
    }
    clusters[cluster_number].centroid.x = acc_x/clusters[cluster_number].nr_pontos;
    clusters[cluster_number].centroid.y = acc_y/clusters[cluster_number].nr_pontos;
}

void calculate_centroids(){
    for(int i = 0; i < K; i++){
        update_cluster_centroid(i); // Calcula e atualiza centroid de cada cluster
    }
}

void reset_clusters_points(){
    for(int i = 0; i < K ; i++){
        clusters[i].pontos = NULL;
        clusters[i].nr_pontos = 0;
    }
}

int verify_centroids(Tuple t1, Tuple t2){
    int flag = 0;
    if (t1.x == t2.x && t1.y == t2.y)
        flag = 1;
    return flag;
}

int centroids_changed(Cluster * old_clusters, Cluster * new_clusters){
    int counter = 0;
    for(int i = 0; i < K; i++){
        if(verify_centroids(old_clusters[i].centroid, new_clusters[i].centroid) == 1)
            counter++;
    }
    printf("ok\n");
    if(counter == 4)
        return 1;
    else
        return 0;
}



void k_means(){
    iterations = 0; //Porque a primeira iteração faz parte da inicialização
    Cluster * old_clusters = malloc(sizeof(struct cluster) * K);
    assign_points(); //2. Primeiro pontos associados ao cluster
    calculate_centroids();  //3. Calculo do centroide inicial 
                            // Repetição desta filosofia dentro do ciclo mas com a verificação do caso de paragem
                            // Goal : 39 ITERATIONS
    int flag = 0;
    while(!flag){
        reset_clusters_points(); //Reset cluster points
        for(int i = 0; i < K ; i++){
        old_clusters[i] = clusters[i];
        }
        assign_points(); // Atribuir cada ponto ao respetivo cluster
        calculate_centroids(); //Calcular centroids de cada cluster
        if(centroids_changed(old_clusters,clusters) == 1) flag = 1;
        //Contador de iterações
        iterations++;
    }
}

int main(){
    init();
    k_means();
    printf("N = %d, K = %d\n", N, K);
    for(int i = 0; i<K; i++)
        printf("Center: (%.3f, %.3f) : Size: %d\n", clusters[i].centroid.x, clusters[i].centroid.y, clusters[i].nr_pontos);
    printf("Iterations: %d\n", iterations);
    return 0;
}