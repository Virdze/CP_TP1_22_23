#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/k_means.h"
#include "../bin/utils.h"


#define N 10000000 //Numero de amostras
#define K 4 //Number of clusters

Tuple * pontos;
Cluster * clusters;

void init(){
    //Initializing

    pontos = malloc(sizeof(struct tuple) * N); //OK 
    clusters = malloc(sizeof(struct cluster) * K);
    
    for(int i = 0; i < K; i++){
        clusters[i].pontos = (Tuple *) malloc(sizeof(struct tuple));
        clusters[i].nr_pontos = 0;
    }

     
    srand(10);
    for(int i = 0; i < N; i++){
        pontos[i].x = (float) rand() / RAND_MAX;
        pontos[i].y = (float) rand() / RAND_MAX;
    }

    for(int i = 0; i < K ; i++){
        clusters[i].centroid.x = pontos[i].x;
        clusters[i].centroid.y = pontos[i].y;
        add_point_to_cluster(clusters[i], pontos[i]);
    }   
}

float euclidean_distance(Tuple p1, Tuple p2){
    return sqrt(pow(p2.x - p1.y, 2) + pow(p2.y - p1.y,2))
}

int calculate_cluster(float min, int point_index){
    int cluster = 0;
    for(int i = 1; i < K; i++){
        float dist = euclidean_distance(clusters[i].centroid, pontos[point_index];
        if (min < dist){
            min = dist;
            cluster = i; 
        }
    }
    return cluster;
}

//Adiciona pontos ao cluster correto
void assign_points(){
    for(int i = 0; i < N; i++){
        float min_dist = euclidean_distance(clusters[0].centroid, pontos[i]); //Calcula distancia euclediana do Ponto ao primeiro cluster
        int cluster_number = calculate_cluster(min_dist,i); // Devolve numero do cluster com o centroid mais próximo.

        addPoint(clusters[cluster_number], pontos[i]);        
    }
}

void update_centroid(Cluster cluster){
    int mean = 0,
        acc_x = 0,
        acc_y = 0;
    for(int i = 0; i < cluster.nr_pontos ; i++){
        acc_x += cluster.pontos[i].x;
        acc_y += cluster.pontos[i].y;
    }
    cluster.centroid.x = acc_x/cluster.nr_pontos;
    cluster.centroid.y = acc_y/cluster.nr_pontos;
    
}

void calculate_centroids(){
    for(int i = 0; i < K; i++){
        update_centroid(clusters[i]); // Calcula e atualiza centroid de cada cluster
    }
}

void k_means(){
    int iterations = 0; //Vai guardar o número de iterações realizadas. OBJETIVO: 39
    Cluster * old_clusters = malloc(sizeof(struct cluster) * K);
    assign_points(); //Assing each point to each cluster
    
    while(!centroids_changed(old_clusters,clusters)){
        
        old_clusters = clusters; //Assign current clusters to old clusters.
        
        assign_points(); //Assing each point to each cluster
        calculate_centroid();


        //Add to iterations
        iterations++;   
    }

}

void main(){
    init();
    //k_means();
    printf("Ok");
    for(int i = 0; i<K; i++)
        printf("(%f,%f)\n", clusters[i].centroid.x, clusters[i].centroid.y);
}