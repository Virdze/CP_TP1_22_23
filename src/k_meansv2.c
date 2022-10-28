#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utilsv2.h"


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
        pontos[i].cluster = -1;
    }


    //Inicialização dos clusters
    clusters = malloc(sizeof(struct cluster) * K);

    for(int i = 0; i < K ; i++){
        clusters[i].centroid.x = pontos[i].x;
        clusters[i].centroid.y = pontos[i].y;
        clusters[i].nr_pontos = 0;
    }

}

void add_point_to_cluster(int cluster_number, int index){
    pontos[index].cluster = cluster_number;
    clusters[cluster_number].nr_pontos++;
}

void change_point_from_cluster(int cluster_ant,int cluster_now, int index){
    pontos[index].cluster = cluster_now;
    clusters[cluster_ant].nr_pontos--;
    clusters[cluster_now].nr_pontos++;
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
                if(pontos[i].cluster != cluster && pontos[i].cluster != -1){
                    change_point_from_cluster(pontos[i].cluster,cluster,i);
                }else if(pontos[i].cluster != cluster && pontos[i].cluster == -1){
                    add_point_to_cluster(cluster,i);
                }

    }
}

void update_cluster_centroid(int cluster_number){

    float acc_x = 0, // Acumulador para todas os x dos pontos associados ao cluster
        acc_y = 0; // Acumulador para todas os y dos pontos associados ao cluster


    for(int i = 0; i < N ; i++){
        if(pontos[i].cluster == cluster_number){
            acc_x += pontos[i].x;
            acc_y += pontos[i].y;
        }
    }
    clusters[cluster_number].centroid.x = acc_x/clusters[cluster_number].nr_pontos;
    clusters[cluster_number].centroid.y = acc_y/clusters[cluster_number].nr_pontos;
}

void calculate_centroids(){
    for(int i = 0; i < K; i++){
        update_cluster_centroid(i); // Calcula e atualiza centroid de cada cluster
    }
}


int verify_centroids(Tuple t1, Tuple t2){
    return (t1.x == t2.x && t1.y == t2.y);
}

int centroids_changed(Tuple * old_centroids){
    int counter = 0;
    for(int i = 0; i < K; i++){
        if(verify_centroids(old_centroids[i], clusters[i].centroid) == 1)
        counter++;
    }
    if(counter == 4)
        return 1;
    else
        return 0;
}



void k_means(){
    iterations = 0; //Porque a primeira iteração faz parte da inicialização
    Tuple * old_centroids = malloc(sizeof(struct tuple) * K);
    assign_points(); //2. Primeiro pontos associados ao cluster
    calculate_centroids();  //3. Calculo do centroide inicial
                            // Repetição desta filosofia dentro do ciclo mas com a verificação do caso de paragem
                            // Goal : 39 ITERATIONS
    int flag = 0;
    while(!flag){
        for(int i = 0; i < K ; i++){
        old_centroids[i] = clusters[i].centroid;
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

int main(){
    init();
    k_means();
    return 0;
}

