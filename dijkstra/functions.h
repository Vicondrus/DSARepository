#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define INF 1000000

extern void printMatrix(int **matrix, int size);
extern int findInAr(int node, int *parent, int maxNode);
extern void printPath(int source, int *parent, int maxNode, int dest, int **arcs,FILE *g);
extern void dijkstra(int maxNodes, int source, int *S, int **arcs, int *dist,int *parent);
extern void dijkstraAgain(int maxNodes, int **arcs, int source, int *S, int *dist, int *parent);

#endif // FUNCTIONS_H_INCLUDED
