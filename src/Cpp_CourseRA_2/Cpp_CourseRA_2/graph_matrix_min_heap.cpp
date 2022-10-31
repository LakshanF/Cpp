#include "graph_matrix_min_heap.h"

using namespace MyGraph;
using namespace std;

graph_matrix_node::graph_matrix_node(int id, int cost):id(id), cost(cost) {}

graph_matrix_min_heap::graph_matrix_min_heap(int size):heap_size(size)
{
    nodes = new graph_matrix_node * [heap_size];
    nodes[0] = new graph_matrix_node(0, 0);
    for (auto i = 1; i < heap_size; i++)
    {
        nodes[i] = new graph_matrix_node(i, 100000);
    }
}

graph_matrix_min_heap::~graph_matrix_min_heap()
{
    for (auto i = 0; i < heap_size; i++)
    {
        delete nodes[i];
    }
    delete nodes;
}

int graph_matrix_min_heap::extract_min_node_id()
{
    int min_node_id = nodes[0]->id;
    delete nodes[0];
    nodes[0] = nodes[heap_size-1];
    
    heap_size--;
    heapify(0);

    return min_node_id;
}

/// <summary>
/// We will walk the nodes, find the node, extract, exchange with last and call heapify
/// </summary>
/// <returns></returns>
int graph_matrix_min_heap::extract_node_id(int id)
{
    int index = -1;
    do 
    {
        index++;
        if (nodes[index]->id == id)
        {
            delete nodes[index];
            nodes[index] = nodes[heap_size - 1];
            heap_size--;
            heapify(index);
            return id;
        }
    } while (index < heap_size);

    return -1;
}


int graph_matrix_min_heap::left_index(int index)
{
    return index * 2 + 1;
}

int graph_matrix_min_heap::right_index(int index)
{
    return (index + 1) * 2;
}

int graph_matrix_min_heap::parent_index(int index)
{
    return (index + 1) / 2 - 1;
}

/// <summary>
/// See CLR Algo page 150, but comparison reversed since this is a min heap
/// </summary>
/// <param name="node"></param>
void graph_matrix_min_heap::insert_node(int id, int cost)
{
    heap_size++;
    int index = heap_size - 1;
    while (index > 0 && (nodes[parent_index(index)]->cost > cost))
    {
        nodes[index] = nodes[parent_index(index)];
        index = parent_index(index);
    }
    nodes[index] = new graph_matrix_node(id, cost);
}

/// <summary>
/// See CLR Algo page 143, but comparison reversed since this is a min heap
/// </summary>
/// <param name="index"></param>
void graph_matrix_min_heap::heapify(int index)
{
    bool loop = true;
    while (index < (heap_size - 1) && loop)
    {

        int smallest = -1;

        int left = left_index(index);
        int right = right_index(index);

        if (left < (heap_size - 1) && (nodes[left]->cost < nodes[index]->cost))
        {
            smallest = left;
        }
        else
        {
            smallest = index;
        }

        if (right < (heap_size - 1) && (nodes[right]->cost < nodes[smallest]->cost))
        {
            smallest = right;
        }

        if (smallest != index)
        {
            graph_matrix_node* temp = nodes[index];
            nodes[index] = nodes[smallest];
            nodes[smallest] = temp;
            index = smallest;
        }
        else 
        {
            loop = false;
        }
    }
}
