#ifndef UTILSV2_HEADER
#define UTILSV2_HEADER


typedef struct tuple{
    float x;
    float y;
    int cluster;
} Tuple;

typedef struct cluster{
    int nr_pontos;
    Tuple centroid;
    float soma_x;
    float soma_y; 
} Cluster;

int verify_centroids(Tuple t1, Tuple t2);

#endif