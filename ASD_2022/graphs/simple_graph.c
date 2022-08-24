#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct graph{
    bool** graph;
    unsigned int numOfEdges;
}graph_t;

void createGraph(graph_t* graph){
    graph->graph = (bool**) calloc(graph->numOfEdges, sizeof(bool*));
    for(int i = 0; i < graph->numOfEdges; i++)
        graph->graph[i] = (bool*) calloc(graph->numOfEdges, sizeof(bool));
}

void connnectEdges(graph_t* graph, unsigned int from, unsigned int to){
    if(from > graph->numOfEdges)
    if(graph->graph[from-1][to-1] == 1){
        return;
    }
    graph->graph[from-1][to-1] = 1;
}

void printGraph(graph_t graph){
    for(int a = 0; a < graph.numOfEdges; a++){
        for(int b = 0; b < graph.numOfEdges; b++){ 
            if(graph.graph[a][b] == 1) 
                printf("%d -> %d\n", a+1, b+1);
        }
    }
}

int main(){
    graph_t graph;
    graph.numOfEdges = 4;

    createGraph(&graph);

    connnectEdges(&graph, 1, 2);
    connnectEdges(&graph, 2, 1);
    connnectEdges(&graph, 1, 3);
    connnectEdges(&graph, 3, 4);
    connnectEdges(&graph, 4, 2);
    connnectEdges(&graph, 2, 1);

    printGraph(graph);

    return 0;
}