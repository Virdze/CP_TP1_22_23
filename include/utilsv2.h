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


inline float euclidean_distance(Tuple p1, Tuple p2){
    return sqrt((p2.y - p1.y)*(p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
}

#endif