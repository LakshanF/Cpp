#pragma once
// graph_matrix_min_heap.h
namespace MyGraph
{
    class graph_matrix_node
    {
        int cost;
        int id;
        int lowest_cost_node;
        friend class graph_matrix_min_heap;
        friend class matrix_graph;
    public:
        graph_matrix_node(int id, int cost);
    };

    /// <summary>
    /// Will keep a matrix_graph nodes where the cost is the key. 
    /// Services
    ///      - extract_min_node
    ///      - extract_node
    ///      - insert_node
    /// </summary>
    class graph_matrix_min_heap
    {
        graph_matrix_node** nodes;
        int heap_size;

        void heapify(int index);
        int left_index(int index);
        int right_index(int index);
        int parent_index(int index);
        ~graph_matrix_min_heap();
    public:
        graph_matrix_min_heap(int size);
        int extract_min_node();
        int extract_node(int id);
        void insert_node(int id, int cost);
    };
}