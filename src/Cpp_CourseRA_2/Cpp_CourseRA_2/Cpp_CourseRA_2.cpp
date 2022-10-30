// Cpp_CourseRA_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
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

    int size = 50;
    double density = 0.4;

    matrix_graph graph(size, density);
    
    ofstream out("graph_data5.txt");
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());

    graph.print();
    cout.flush();
    
    cout.rdbuf(coutbuf);

    int shortestPath = graph.shortest_path_dijkstra();

    cout << "Shorted Path: " << shortestPath << "\n";
}
