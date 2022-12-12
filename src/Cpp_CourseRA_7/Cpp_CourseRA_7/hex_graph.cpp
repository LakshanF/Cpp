#include "hex_graph.h"
#include <iostream>

using namespace std;
using namespace HexGraph;

hex_node::hex_node(int id) :id(id), piece_type(piece::empty) {}
piece hex_node::get_piece() { return piece_type; }
void hex_node::set_piece(piece piecetype) { piece_type = piecetype; }

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
			switch (GetNode(i * size_one_side + j).get_piece())
			{
			case piece::empty:
				cout << ".";
				break;
			case piece::blue:
				cout << "B";
				break;
			case piece::red:
				cout << "R";
				break;
			}
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
/// Blue goes first, and need to create a path from east-west
/// Red goes from south-north
/// 0 - no
/// 1 - blue won
/// 2 - red won
/// </summary>
/// <returns></returns>
int hex_graph::game_finished()
{
	// short cut first to see that all columns (blue) or rows (red) have at least 

	// blue first
	bool blue_found = false;
	for (int i = 0; i < size_one_side; i++)
	{
		blue_found = false;
		for (int j = 0; j < size_one_side; j++)
		{
			int col_pos = (j * size_one_side) + i;
			if (nodes[col_pos].get_piece() == piece::blue)
			{
				blue_found = true;
				break;
			}
		}
	}

	if (blue_found)
	{
		// need to check with a breadth first search if there is path
	}

	// red next
	bool red_found = false;
	for (int i = 0; i < size_one_side; i++)
	{
		red_found = false;
		for (int j = 0; j < size_one_side; j++)
		{
			int red_pos = i * size_one_side + j;
			if (nodes[red_pos].get_piece() == piece::red)
			{
				red_found = true;
				break;
			}
		}
	}

	if (red_found)
	{
		// need to check with a breadth first search if there is path
	}


	return 0;
}

/// <summary>
/// Dumb strategy first: make a move on an empty square
/// </summary>
/// <returns></returns>
int hex_graph::make_computer_move()
{
	return 0;
}

hex_node hex_graph::GetNode(int position)
{
	return nodes[position];
}
