// Cpp_CourseRA_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

    int size = 5;
    double density = 0.9;

    matrix_graph graph(size, density);

    ofstream out("graph_minimum_spanning_tree_prim_data.txt");
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());

    graph.print();
    cout << endl;

    cout << "Prim MST Cost: First Run" << endl;
    int shortestPath = graph.minimum_spanning_tree_prim();
    cout << endl;

    for (auto i = 0; i < 3; i++)
    {
        cout << "Prim MST Cost: " << (i + 2) << " run" << endl;
        assert(graph.minimum_spanning_tree_prim() == shortestPath);
        cout << endl;
    }

    cout.flush();

    cout.rdbuf(coutbuf);
    cout << "Prim MST Cost: " << shortestPath << endl;
}
