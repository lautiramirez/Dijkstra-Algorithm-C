#include <stdio.h>
#include <stdlib.h>

#include "cost.h"
#include "dijkstra.h"
#include "graph.h"
#include "set.h"

set possible_cities(graph_t graph, vertex_t init, set cities, cost_t liters){
    unsigned int dim = graph_max_size(graph);
    cost_t *cost = dijkstra(graph, init);
    set poss_cities = set_empty(); 
    for (unsigned int i = 0; i < dim; i++){
        if(cost_le(cost[i], liters) && set_member(i, cities)){
            poss_cities = set_add(poss_cities, i);
        }
    }
    free(cost);
    return poss_cities;
}

int main(int argc, char *argv[]){

    if (argc < 2) {
        printf("Usage: ./star input/example_graph_1.in\n\n");
        exit(EXIT_FAILURE);
    }
    graph_t graph = graph_from_file(argv[1]);

    unsigned int dim = graph_max_size(graph);

    cost_t liters = 0;
    vertex_t init;
    printf("Enter your maximum number of available liters: ");
    scanf("%d", &liters);
    printf("Enter your starting city: ");
    scanf("%u", &init);

    set all_cities = set_empty();
    for(vertex_t j = 0; j < dim; j++){
        all_cities = set_add(all_cities, j);
    }
    
    set poss_cities = possible_cities(graph, init, all_cities, liters);

    printf("\tWith %d liters of naphtha you can go from %u to: { ", liters, init);
    while (!set_is_empty(poss_cities))
    {   
        vertex_t city = set_get(poss_cities);
        printf("%d ", city);
        poss_cities = set_elim(poss_cities, city);
    }
    printf("}\n");
    
    graph = graph_destroy(graph);
    all_cities = set_destroy(all_cities);
    poss_cities = set_destroy(poss_cities);

    return 0;
}