// my_class.cpp
#include "matrix_graph.h"
#include "graph_matrix_min_heap.h"
#include <iostream>
#include <assert.h>
#include <unordered_set>

using namespace MyGraph;
using namespace std;

matrix_graph::matrix_graph(int size, double density):size(size), density(density)
{
    srand(time(0));

    graph = new bool* [size];
    color = new int* [size];
    edge_cost = new int* [size];
    node_cost = new int [size];
    node_low_cost_parent_id = new int[size];
    for (auto i = 0; i < size; i++)
    {
        graph[i] = new bool[size];
        color[i] = new int[size];
        edge_cost[i] = new int[size];
        node_cost[i] = MAX_VALUE;
        node_low_cost_parent_id[i] = -1;
    }
    // root node is 0
    node_cost[0] = 0;

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
                edge_cost[i][j] = edge_cost[j][i] = (prob() * 30) + 1;
            }
        }
    }
}

matrix_graph::~matrix_graph()
{
    for (auto i = 0; i < size; i++)
    {
        delete graph[i];
        delete color[i];
        delete edge_cost[i];
    }

    delete graph;
    delete color;
    delete edge_cost;
    delete node_cost;
    delete node_low_cost_parent_id;
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
                cout << i << '\t' << j << '\t' << edge_cost[i][j] << '\t' << color[i][j] << '\n';
            }
        }
    }
}

/// <summary>
/// Prim MST algorithm (See CLR Algo page 509)
///  Q->V
///  foreach u E Q
///     key[u] <- infinite
///  key[root] <- 0
///  parent[root] <- null
///  while Q != empty
///     do u->Extract-Min(Q)
///         for each vertex v E adj[u]
///             if v E Q and weight(u, v) < key[v]
///                 parent[v] <- u
///                 key[v] <- weight(u, v)
/// 
/// NOTES
///  - Will use a min-heap to extract min node
/// </summary>
/// <returns>shortest path</returns>
int matrix_graph::minimum_spanning_tree_prim()
{
    // Initialize algorithmic specific values
    for (auto i = 0; i < size; i++)
    {
        node_cost[i] = MAX_VALUE;
        node_low_cost_parent_id[i] = -1;
    }
    // root node is 0
    node_cost[0] = 0;

    // We will use a min_heap instead of a Q
    // The heap will be initialized correctly
    unordered_set<int> in_nodes;
    graph_matrix_min_heap* min_heap = new graph_matrix_min_heap(size);

    // We will iterate the (size-1) of the graph
    for (auto i = 0; i < (size-1); i++)
    {
        int min_node_id = min_heap->extract_min_node_id();
        int min_node_cost = node_cost[min_node_id];
        in_nodes.insert(min_node_id);
        // cout << "i: " << i << ", node_id: " << min_node_id << ", cost: " << min_node_cost << endl;
        for (auto j = 0; j < size; j++)
        {
            if (graph[min_node_id][j] && (in_nodes.count(j)==0))
            {
                int heap_j = min_heap->extract_node_id(j);
                assert(heap_j == j);
                int existing_edge_node_cost = node_cost[j];
                int this_edge_cost = edge_cost[min_node_id][j];
                if (existing_edge_node_cost > this_edge_cost)
                {
                    node_low_cost_parent_id[j] = min_node_id;
                    node_cost[j] = this_edge_cost;
                    existing_edge_node_cost = this_edge_cost;
                }
                // cout << "j: " << j << ", edge_node->cost: " << existing_edge_node_cost << endl;
                min_heap->insert_node(j, existing_edge_node_cost);
            }
        }
    }

    // find out the MST cost by adding all the costs
    int mstCost = 0;
    for (auto i = 1; i < size; i++)
    {
        cout << "node: " << i << ", cost: " << node_cost[i] << ", parent: " << node_low_cost_parent_id[i] << endl;
        mstCost += node_cost[i];
    }
    cout << "MST Cost: " << mstCost << endl;

    return mstCost;
}

double matrix_graph::prob()
{
    return (static_cast<double>(rand()) / RAND_MAX);
}
