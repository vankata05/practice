#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

typedef struct graph{
    unsigned int** graph;
    unsigned int numOfEdges;
}graph_t;

void createGraph(graph_t* graph){
    graph->graph = (unsigned int**) calloc(graph->numOfEdges, sizeof(unsigned int*));
    for(int i = 0; i < graph->numOfEdges; i++)
        graph->graph[i] = (unsigned int*) calloc(graph->numOfEdges, sizeof(unsigned int));
}

void connnectEdges(graph_t* graph, unsigned int from, unsigned int to, unsigned int weight){
    if(from > graph->numOfEdges)
    if(graph->graph[from-1][to-1] != 1){
        return;
    }
    graph->graph[from-1][to-1] = weight;
}

void addEdge(graph_t* graph){
    graph->numOfEdges++;
    graph->graph = (unsigned int**) realloc(graph->graph, graph->numOfEdges*sizeof(unsigned int*));
    for(int i = 0; i < graph->numOfEdges; i++){
        graph->graph[i] = (unsigned int*) realloc(graph->graph, graph->numOfEdges*sizeof(unsigned int));
        graph->graph[i][graph->numOfEdges] = 0;
    }
}

void printGraph(graph_t graph){
    for(int a = 0; a < graph.numOfEdges; a++){
        for(int b = 0; b < graph.numOfEdges; b++){ 
            if(graph.graph[a][b] != 0) 
                printf("%d -> %d\n", a+1, b+1);
        }
    }
}

void dijkstra(graph_t graph, unsigned int to){
    int edges[graph.numOfEdges][2];
    //edges[x][0] - distance to the edge
    //edges[x][1] - previous edge

    for(int i = 1; i < graph.numOfEdges; i++){
        edges[i][0] = -1;
        edges[i][1] = -1;
    }

    edges[0][0] = 0;
    edges[0][1] = -1;

    for(int a = 0; a < graph.numOfEdges; a++){
        for(int b = 0; b < graph.numOfEdges; b++){ 
            if(graph.graph[a][b] != 0){
                if(edges[b][0] > edges[a][0]+1 || edges[b][0] == -1){
                    if(edges[a][0] != -1){
                        if(edges[b][0] == -1)
                            edges[b][0] = 0;
                        edges[b][0] = (edges[a][0] + graph.graph[a][b]);
                        edges[b][1] = a;
                    }
                }
            }
        }
    }
    /* Prints the shortest paths to all edges
    for(int i = 0; i < graph.numOfEdges; i++){
        printf("%d:\t%d|%d\n", i+1,  edges[i][0], edges[i][1]+1);
    }*/

    printf( "The shortest path to %d is %d<--", to, to);
    int i = edges[to-1][1];
    while(i != 0){
        printf("%d<--", i+1);
        i = edges[i][1];
    }
    printf("1 witch is %d units long\n", edges[to-1][0]);

}

int main(){
    graph_t graph;
    graph.numOfEdges = 5;

    createGraph(&graph);

    connnectEdges(&graph, 1, 2, 23);
    connnectEdges(&graph, 4, 2, 45);
    connnectEdges(&graph, 1, 3, 67);
    connnectEdges(&graph, 3, 4, 89);
    connnectEdges(&graph, 4, 4, 64);
    connnectEdges(&graph, 2, 4, 22);

    // addEdge(&graph);

    // connnectEdges(&graph, 5, 2);
    // connnectEdges(&graph, 4, 5);

    printGraph(graph);

    dijkstra(graph, 2);

    return 0;
}