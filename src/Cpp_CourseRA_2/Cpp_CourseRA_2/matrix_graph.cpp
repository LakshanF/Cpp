// my_class.cpp
#include "matrix_graph.h"
#include "graph_matrix_min_heap.h"
#include <iostream>
#include <assert.h>
#include <unordered_set>
//#include <queue>

const int MAX_VALUE = 100000;

using namespace MyGraph;
using namespace std;

double prob();

matrix_graph::matrix_graph(int size, double density):size(size), density(density)
{
    srand(time(0));

    graph = new bool* [size];
    color = new int* [size];
    cost = new int* [size];
    for (auto i = 0; i < size; i++)
    {
        graph[i] = new bool[size];
        color[i] = new int[size];
        cost[i] = new int[size];
    }

    for (auto i = 0; i < size; i++)
    {
        for (auto j = 0; j < size; j++)
        {
            if (i == j)
                graph[i][j] = false;
            else
            {
                graph[i][j] = graph[j][i] = (prob() < density);
            }
        }
    }

    for (auto i = 0; i < size; i++)
    {
        for (auto j = 0; j < size; j++)
        {
            if (graph[i][j])
            {
                color[i][j] = color[j][i] = rand() % 3;
                cost[i][j] = cost[j][i] = (prob() * 30) + 1;
            }
        }
    }
}

void matrix_graph::print()
{
    cout << size << "\n";
    for (auto i = 0; i < size; i++)
    {
        for (auto j = 0; j < size; j++)
        {
            if (graph[i][j])
            {
                cout << i << '\t' << j << '\t' << cost[i][j] << '\t' << color[i][j] << '\n';
            }
        }
    }
}

/// <summary>
/// Dijkstra algorithm (See CLR Algo page 527)
///  S->0
///  Q->V
///  while Q != empty
///     do u->Extract-Min(Q)
///         S->S  U {u}
///         for each vertex v E adj[u]
///             do Relax(u, v, w)
/// 
/// NOTES
///  - Will use a min-heap to extract min node
///     * heap will only keep nodes that are reachable
///     * will only keep valid nodes
///     * will allow additional operations
///          - Does node exist
///          - Extract node
/// </summary>
/// <returns>shortest path</returns>
int matrix_graph::shortest_path_dijkstra()
{
    // We will use a min_heap instead of a Q
    // The heap will be initialized correctly
    unordered_set<int> in_nodes;
    graph_matrix_node** nodes = new graph_matrix_node * [size];
    nodes[0] = new graph_matrix_node(0, 0);
    for (auto i = 1; i < size; i++)
    {
        nodes[i] = new graph_matrix_node(i, MAX_VALUE);
    }
    graph_matrix_min_heap* min_heap = new graph_matrix_min_heap(size);

    // We will iterate the size of the graph
    for (auto i = 0; i < size; i++)
    {
        graph_matrix_node* node = nodes[min_heap->extract_min_node()];
        in_nodes.insert(node->id);
        if (node->id == (size - 1))
            // We have reached the last node
            break; 
        //cout << "i: " << i << ", node_id: " << node->id << ", cost: " << node->cost << endl;
        // go over all the edges and relax
        for (auto j = 0; j < size; j++)
        {
            if (graph[node->id][j] && (in_nodes.count(j)==0))
            {
                int heap_j = min_heap->extract_node(j);
                assert(heap_j == j, "j %i:, heap_j: %i", j, heap_j);
                graph_matrix_node* edge_node = nodes[heap_j];
                if ((edge_node->cost == MAX_VALUE) || edge_node->cost > (node->cost + cost[node->id][j]))
                {
                    // This node has been initialized to its cost at all
                    edge_node->cost = node->cost + cost[node->id][j];
                    edge_node->lowest_cost_node = node->id;
                }
                //cout << "j: " << j << ", edge_node->cost: " << edge_node->cost << endl;
                min_heap->insert_node(edge_node->id, edge_node->cost);
            }
        }
    }

    // find out the shorted path cost by going to the last node and traversing
    cout << "lastNode: " << (size - 1) << ", cost: " << nodes[size - 1]->cost << endl;
    int parentNodeId = nodes[size - 1]->lowest_cost_node;
    int shortestPathCost = nodes[size - 1]->cost;
    while (parentNodeId != -1)
    {
        cout << "parentNodeId: " << parentNodeId << ", cost: " << nodes[parentNodeId]->cost << endl;
        shortestPathCost += nodes[parentNodeId]->cost;
        parentNodeId = nodes[parentNodeId]->lowest_cost_node;
    }
    return shortestPathCost;
}

double prob()
{
    return (static_cast<double>(rand()) / RAND_MAX);
}
