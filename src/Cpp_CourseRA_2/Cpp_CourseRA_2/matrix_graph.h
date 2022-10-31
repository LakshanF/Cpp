#pragma once

// matrix_graph.h
namespace MyGraph
{
    class matrix_graph
    {
        int size;
        double density;
        bool** graph;
        int** color;
        int** edge_cost;
        int* node_cost;
        int* node_low_cost_parent_id;
        double prob();
    public:
        ~matrix_graph();
        matrix_graph(int size, double density);
        void print();
        int shortest_path_dijkstra();
    };
}