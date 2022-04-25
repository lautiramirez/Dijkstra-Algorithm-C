#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "dijkstra.h"
#include "graph.h"

vertex_t find_min_cost(cost_t *arr, set conj){
	vertex_t res;
	cost_t min = cost_inf();
	set saux = set_copy(conj);
	while(!set_is_empty(saux)){
		vertex_t s = set_get(saux);
		if(cost_le(arr[s], min)){
			min = arr[s];
			res = s;
		}
		saux = set_elim(saux, s);
	}
	saux = set_destroy(saux);
	return res;
}


cost_t *dijkstra(graph_t graph, vertex_t init){

	unsigned int n = graph_max_size(graph);
	cost_t *arr_ret = (cost_t *)calloc(n, sizeof(cost_t));

	set set_vertices = set_empty();
	for(vertex_t i = 0; i < n; i++){
		set_vertices = set_add(set_vertices, i);
		arr_ret[i] = graph_get_cost(graph, init, i);
	}
	set_vertices = set_elim(set_vertices, init); 

	while(!set_is_empty(set_vertices)){
		vertex_t c_min = find_min_cost(arr_ret, set_vertices);
		set_vertices = set_elim(set_vertices, c_min);

		set saux = set_copy(set_vertices);
		while(!set_is_empty(saux)){

			vertex_t j = set_get(saux);
			cost_t sum = cost_sum(arr_ret[c_min], graph_get_cost(graph, c_min, j));

			if(cost_lt(sum, arr_ret[j])){
				arr_ret[j] = sum;
			}

			saux = set_elim(saux, j);
		}		
		saux = set_destroy(saux);
	}
	set_vertices = set_destroy(set_vertices);

	return arr_ret;
}
