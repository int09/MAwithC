#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"
#include "set.h"
/* Define a structure for adjancy lists. */
typedef struct AdjList_
{
	void	*vertex;
	Set		adjacent;
} AdjList;

/* Define a structure for graphs. */
typedef struct Graph_
{
	int		vcount;
	int		ecount;
	
	int		(*match)(const void *key1, const void *key2);
	void	(*destroy)(void *data);

	List	adjlists;
} Graph;


void	graph_init(Graph *graph, int (*match)(const void *key1, const void *key2)
			void (*destroy)(void *data))
{
	/* Initalize the graph. */
	graph->vcount = 0;
	graph->ecount = 0;
	graph->match = match;
	graph->destroy = destroy;

	/* Initalize the list of adjacency-list structures. */
	list_init(&graph->adjlist, NULL);
	
	return;
}

void	graph_destroy(Graph *graph)
{
	AdjList	*adjlist;

	/* Remove each adjacency-list structure and destroy its adjacency list. */
	while (list_size(&graph->adjlists) > 0)
	{
		if (list_size(&graph->adjlists, NULL, (void **)&adjlist) == 0)
		{
			set_destroy(&adjlist->adjacent);

			if (graph->destroy != NULL)
				graph->destroy(adjlist->vertex);

			free(adjlist);
		}
	}

	/* Destroy the list of adjanceny-list structures, which is now empty. */
	list_destroy(&graph->adjlists);
	
	memset(graph, 0, sizeof(Graph));
	return;
}

int		graph_ins_vertex(Graph *graph, const void *data)
{
	ListElmt	*element;
	AdjList		*adjlist;
	int			retval;
	/* Dont allow the insertion of duplicate vertices. */
	for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element))
	{
		if (graph->match(data, ((AdjList *)list_data(element))->vertex))
			return 1;
	}
	/* Insert the vertex. */
	if ((adjlist = (AdjList *)malloc(sizeof(AdjList))) == NULL)
		return -1;
	
	adjlist->vertex = (void *)data;
	set_init(&adjlist->adjacent, graph->match, NULL);

	if ((retval = list_ins_next(&graph->adjlists, list_tail(&graph->adjlists), adjlist)) != 0)
		return retval;
	
	/* Adjust the vertex count to account for the inserted vertex. */
	graph->vcount++;
	return 0;
}

int		graph_ins_edge(Graph *graph, const void *data1, const void *data2)
{

}

int		graph_rem_vertex(Graph *graph, void **data);
int		graph_rem_edge(Graph *graph, void *data1, void **data2);

int		graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);
int		graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);


