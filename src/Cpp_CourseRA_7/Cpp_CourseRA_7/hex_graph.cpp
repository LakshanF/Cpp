#include "hex_graph.h"
#include <iostream>

using namespace std;
using namespace HexGraph;

hex_node::hex_node(int id) :id(id), piece_type(0) {}
int hex_node::get_piece() { return piece_type; }
void hex_node::set_piece(int piece) { piece_type = piece; }

hex_graph::hex_graph(int size) :size_one_side(size)
{
	nodes = new hex_node[size * size];
}

hex_graph::~hex_graph()
{
	delete nodes;
}

void hex_graph::print_board()
{
	for (int i = 0; i < size_one_side; i++)
	{
		for (int j = 0; j < i; j++)
			cout << "  "; // 2 spaces
		if (i != 0)
		{
			for (int j = 0; j < size_one_side; j++)
			{
				cout << "\\ /";
			}
			cout << "\\\n";
		}
		for (int j = 0; j < i; j++)
			cout << "  "; // 2 spaces
		for (int j = 0; j < size_one_side; j++)
		{
			cout << ".";
			if (j != (size_one_side - 1))
				cout << " - ";
		}
		cout << '\n';
	}
}

bool hex_graph::add_user_move(int position, int piece_type)
{
	return false;
}

/// <summary>
/// 0 - no
/// 1 - red won
/// 2 - blue won
/// </summary>
/// <returns></returns>
int hex_graph::game_finished()
{
	return 0;
}

int hex_graph::make_computer_move()
{
	return 0;
}
