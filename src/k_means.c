#include <stdio.h>
#include <stdlib.h>
#include <math.h>
<<<<<<< HEAD

#include "../include/utils.h"
=======
#include "../headers/k_means.h"
#include "../headers/utils.h"
>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7


#define N 10000000 //Numero de amostras
#define K 4 //Number of clusters

Tuple pontos; // Vetor com os pontos
Cluster clusters; // Vetor com os clusters
int iterations;


void init(){

    //Inicialização do vetor de pontos
    pontos = malloc(sizeof(struct tuple) * N); 
    
    srand(10);
    for(int i = 0; i < N; i++){
        pontos[i].x  = (float) rand() / RAND_MAX;
        pontos[i].y = (float) rand() / RAND_MAX;
        if(i < 10 || i == N-1)
            printf("Ponto nr %d : (%f, %f)\n",i,pontos[i].x,pontos[i].y);
    }


    //Inicialização dos clusters
    clusters = malloc(sizeof(struct cluster) * K);

    for(int i = 0; i < K ; i++){
        clusters[i].pontos = (Tuple) malloc(sizeof(struct tuple));
        clusters[i].centroid = (Tuple) malloc(sizeof(struct tuple));
        clusters[i].centroid->x = pontos[i].x;
        clusters[i].centroid->y = pontos[i].y;
        clusters[i].nr_pontos = 0;
        //printf("Centroid cluster nr %d : (%f, %f)\n",i,clusters[i].centroid->x,clusters[i].centroid->y);
    }

<<<<<<< HEAD
=======
float euclidean_distance(Tuple p1, Tuple p2){
    //return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y,2));            ver qual a mais eficiente
    return sqrt((p2.y-p1.y) * (p2.y-p1.y) + (p2.x-p1.x) * (p2.x-p1.x));

>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7
}


//Verifica as distancias de um ponto a cada cluster e devolve qual o cluster mais próximo do ponto. 
int calculate_cluster(float min, int point_index){
    int cluster = 0;
    for(int i = 1; i < K; i++){
<<<<<<< HEAD
        float dist = euclidean_distance(&pontos[point_index], clusters[i].centroid);
        if (min > dist){
=======
        float dist = euclidean_distance(clusters[i].centroid, pontos[point_index]);
        if (min < dist){
>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7
            min = dist;
            cluster = i; 
        }
    }
    return cluster;
}

void add_point_to_cluster(Tuple point,int cluster_number){
   
        
        printf("Ponto : (%f,%f)\n",point->x,point->y);
        int n = clusters[cluster_number].nr_pontos;
        clusters[cluster_number].pontos = realloc(clusters[cluster_number].pontos,(sizeof(struct tuple) * n) + sizeof(struct tuple));
        clusters[cluster_number].pontos[n].x = point->x;
        clusters[cluster_number].pontos[n].y = point->y;
        (clusters+cluster_number)->nr_pontos++;







        //(clusters+cluster_number)->pontos = malloc(sizeof(struct cluster) * sizeof((clusters+cluster_number)->pontos + sizeof(struct tuple)));

  //      tmp->pontos[clusters[cluster_number].nr_pontos-1].x = point->x;
//        tmp->pontos[clusters[cluster_number].nr_pontos-1].y = point->y;
        //(clusters+cluster_number)->pontos[(clusters+cluster_number)->nr_pontos].x = point->x;  
        //(clusters+cluster_number)->pontos[(clusters+cluster_number)->nr_pontos].y = point->y;
}

//Adiciona pontos ao cluster correto
void assign_points(){
    for(int i = 0; i < N; i++){
        float min_dist = euclidean_distance(&pontos[i], clusters[0].centroid); //Calcula distancia euclediana do Ponto ao primeiro cluster
        int cluster_number = calculate_cluster(min_dist,i); // Devolve numero do cluster com o centroid mais próximo.
        if(i < 10){
            add_point_to_cluster(&pontos[i],cluster_number);

<<<<<<< HEAD
            printf("Ponto nr %d : (%f, %f) | (Cluster , Nrº de pontos) : (%d,%d)\n",i,clusters[cluster_number].pontos[i].x,clusters[cluster_number].pontos[i].y, cluster_number,clusters[cluster_number].nr_pontos);
        }
=======
        add_point_to_cluster(clusters[cluster_number], pontos[i]);        
>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7
    }
    
}

void update_cluster_centroid(int cluster_number){

    float acc_x = 0, // Acumulador para todas os x dos pontos associados ao cluster
        acc_y = 0; // Acumulador para todas os y dos pontos associados ao cluster

    for(int i = 0; i < clusters[cluster_number].nr_pontos ; i++){
        acc_x += clusters[cluster_number].pontos[i].x;
        acc_y += clusters[cluster_number].pontos[i].y;
    }
    clusters[cluster_number].centroid->x = acc_x/clusters[cluster_number].nr_pontos;
    clusters[cluster_number].centroid->y = acc_y/clusters[cluster_number].nr_pontos;
}

void calculate_centroids(){
    for(int i = 0; i < K; i++){
        update_cluster_centroid(i); // Calcula e atualiza centroid de cada cluster
    }
}

void reset_clusters_points(){
    for(int i = 0; i < K ; i++){
        free(clusters[i].pontos);
        clusters[i].nr_pontos = 0;
    }
}

<<<<<<< HEAD
int verify_centroids(Tuple t1, Tuple t2){
    int flag = 0;
    if (t1->x == t2->x && t1->y == t2->y)
        flag = 1;
    return flag;
}

int centroids_changed(Cluster old_clusters, Cluster new_clusters){
    int flag = 0;
    for(int i = 0; !flag && i < K; i++){
        if(verify_centroids(old_clusters[i].centroid, new_clusters[i].centroid) == 1)
            flag = 1;
    }
    return flag;
}



=======
void output(int iteracoes){
    printf("N = %d, K = %d\n", N, K);
    for(int i=0; i < K; i++){
        printf("Center: (%.3f,%.3f) : Size: %d\n", clusters[i].centroid.x, clusters[i].centroid.y, clusters[i].nr_pontos);
    }
    printf("Iterations: %d\n", iteracoes);
}

>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7
void k_means(){
    iterations = 0;
    Cluster old_clusters = malloc(sizeof(struct cluster) * K);
    assign_points(); //Assing each point to each cluster
    //printf("Ponto nr 100 : (%d, %d)\n",clusters[0].nr_pontos,clusters[0].nr_pontos);
    int flag = 0;
    while(!flag){
        
        old_clusters = clusters; // Guardar o esto atual dos clusters antes o calculo dos centroids
        
        calculate_centroids(); //Calcular centroids de cada cluster
        
<<<<<<< HEAD
        reset_clusters_points(); //Reset cluster points
=======
        assign_points(); //Assing each point to each cluster
        calculate_centroids();
>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7

        assign_points(); // Atribuir cada ponto ao respetivo cluster

        if(centroids_changed(old_clusters,clusters) == 1) flag = 1;
        
        //Contador de iterações 
        iterations++;
    }
<<<<<<< HEAD
=======
    output(iterations);
>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7
}

void main(){
    init();
<<<<<<< HEAD
    //for(int i = 0; i < 100; i++)
    //    printf("%d: (%f,%f)\n", i, pontos[i].x, pontos[i].y);
    k_means();
=======
    k_means();
    printf("Ok");
>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7
    for(int i = 0; i<K; i++)
        printf("(%f,%f)\n", clusters[i].centroid->x, clusters[i].centroid->y);
    printf("Number of iterations: %d\n", iterations);
}