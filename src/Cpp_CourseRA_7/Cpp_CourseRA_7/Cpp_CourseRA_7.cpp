// Cpp_CourseRA_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "hex_graph.h"
#include <iostream>


using namespace HexGraph;
using namespace std;

int main()
{
    int board_size = 3;
    hex_graph graph(board_size);
    int row, col;
    for (int i = 0; i < board_size * board_size; i++)
    {
        graph.print_board();
        while (true)
        {
            cout << "Please make a move (row, column): " << endl;
            cin >> row >> col;
            if (graph.add_user_move(row, col))
                break;
        }
        if (graph.game_finished())
        {
            cout << "You Won!" << endl;
            graph.print_board();
            break;
        }
        graph.make_computer_move();
        if (graph.game_finished())
        {
            cout << "Computer Won!" << endl;
            graph.print_board();
            break;
        }
    }
}
