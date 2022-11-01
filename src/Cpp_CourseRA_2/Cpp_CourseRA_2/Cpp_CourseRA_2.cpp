// Cpp_CourseRA_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include "matrix_graph.h"

using namespace std;
using namespace MyGraph;

int main()
{
    //int size = 15;
    //double density;
    //cout << "graph size:" << endl;
    //cin >> size;
    //cout << "graph density (0, 1):" << endl;
    //cin >> density;

    int size = 5000;
    double density = 0.1;

    matrix_graph graph(size, density);
    
    ofstream out("graph_shortest_path_dijkstra_data.txt");
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());

    graph.print();
    cout << endl;

    cout << "Shortest Path Information: First Run" << endl;
    int shortestPath = graph.shortest_path_dijkstra();
    cout << endl;

    for (auto i = 0; i < 10; i++)
    {
        cout << "Shortest Path Information: " << (i+2) << " run" << endl;
        assert(graph.shortest_path_dijkstra()==shortestPath);
        cout << endl;
    }

    cout.flush();
    
    cout.rdbuf(coutbuf);
    cout << "Shorted Path: " << shortestPath << endl;
}
