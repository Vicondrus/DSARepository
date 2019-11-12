#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

enum {UNVISITED,VISITED};
extern void printMatrix(int **matrix, int size);
extern void bfs(int nodes, int **arcs, int startNode,FILE *g);
extern int dfs(int nodes, int **arcs, int crtNode, int *vis,FILE *g);

#endif // FUNCTIONS_H_INCLUDED
