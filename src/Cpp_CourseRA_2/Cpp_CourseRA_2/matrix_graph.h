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
        int** cost;
    public:
        matrix_graph(int size, double density);
        void print();
        int shortest_path_dijkstra();
    };
}