#include "hex_graph.h"
#include <iostream>
#include <queue>

using namespace std;
using namespace HexGraph;

hex_node::hex_node(int id) :id(id), piece_type(piece::empty), color(path_color::white){}
piece hex_node::get_piece() { return piece_type; }
void hex_node::set_piece(piece piecetype) { piece_type = piecetype; }

hex_graph::hex_graph(int size) :size_one_side(size)
{
	nodes = new hex_node[size * size];
	for (int i = 0; i < size_one_side* size_one_side; i++)
	{
		nodes[i].id = i;
	}
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
			switch (nodes[i * size_one_side + j].get_piece())
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

/// <summary>
/// Assumes first move, blue
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
/// <returns></returns>
bool hex_graph::add_user_move(int row, int col)
{
	int position = row * size_one_side + col;
	if(nodes[position].piece_type != piece::empty)
		return false;
	nodes[position].piece_type = piece::blue;
	return true;
}

/// <summary>
/// Dumb strategy first: make a move on an empty square
/// </summary>
/// <returns></returns>
int hex_graph::make_computer_move()
{
	for (int i = 0; i < size_one_side * size_one_side; i++)
	{
		if (nodes[i].piece_type == piece::empty)
		{
			nodes[i].piece_type = piece::red;
			return nodes[i].id;
		}
	}
	return -1;
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
		if (!blue_found)
			break;
	}

	if (blue_found)
	{
		// need to check with a breadth first search if there is a path
		// We will look at all the boxes in the left most column and check if there is a path to the right most column
		for (int i = 0; i < size_one_side; i++)
		{
			int col_pos = i * size_one_side;
			if (nodes[col_pos].get_piece() == piece::blue)
			{
				if (path_found(nodes[col_pos]))
					return 1;
			}
		}
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
		if (!red_found)
			break;
	}

	if (red_found)
	{
		// need to check with a breadth first search if there is a path
		// We will look at all the boxes in the first row and check if any has reached the last rown
		for (int i = 0; i < size_one_side; i++)
		{
			int row_pos = i;
			if (nodes[row_pos].get_piece() == piece::red)
			{
				if (path_found(nodes[row_pos]))
					return 2;
			}
		}
	}
	return 0;
}

/// <summary>
/// Given a starting position (westmost column or southmost row), determine if there is a traversing path
/// Blue travels from east to west (right)
/// Red travels from north to south (down)
/// Algorithm (Breadth search first, with dynamically getting adjacency nodes based on the position)
///  - Make all the nodes white
///  - Add source to Q
///  - While Q is not empty
///		+ Deque
///		+ if node is on the opposite side, return as true
///		+ Color node black
///		+ for all white adjacency nodes with the same piece
///			+ color node grey
///			+ add to Q
/// </summary>
/// <param name="position"></param>
/// <returns></returns>
bool hex_graph::path_found(hex_node root)
{
	queue<hex_node> node_queue;
	for (int i = 0; i < size_one_side * size_one_side; i++)
	{
		nodes[i].color = path_color::white;
	}
	root.color = path_color::grey;
	node_queue.push(root);

	while (!node_queue.empty())
	{
		hex_node node = node_queue.front();
		if (node.piece_type==piece::blue && (node.id % size_one_side == (size_one_side - 1)))
			return true;
		if (node.piece_type == piece::red && (node.id >= (size_one_side * size_one_side - size_one_side)))
			return true;
		vector<int> adjacentIds = GetAdjacentNodes(node.id);

		// @TODO: foreach?
		for (auto i = adjacentIds.begin(); i != adjacentIds.end(); ++i)
		{
			if (nodes[*i].piece_type == node.piece_type && nodes[*i].color == path_color::white)
			{
				nodes[*i].color = path_color::grey;
				node_queue.push(nodes[*i]);
			}
		}
		node.color = path_color::black;
		node_queue.pop();
	}

	return false;
}


vector<int> hex_graph::GetAdjacentNodes(int node_id)
{
	vector<int> ids;

	// based on the node_id, we return the neighbor nodes

	// Corners
	if (node_id == 0)
	{
		// corner (2 edges): top left
		ids.push_back(1);
		ids.push_back(size_one_side);
	}
	else if (node_id == (size_one_side * size_one_side - 1))
	{
		// corner (2 edges): bottom right
		ids.push_back(size_one_side * size_one_side - 2);
		ids.push_back(size_one_side * size_one_side - 1 - size_one_side);
	}
	else if (node_id == (size_one_side - 1))
	{
		// corner (3 edges): top right
		ids.push_back(size_one_side - 2);
		ids.push_back(size_one_side - 1 + size_one_side);
		ids.push_back(size_one_side - 1 + size_one_side - 1);
	}
	else if ( node_id == (size_one_side * size_one_side - size_one_side))
	{
		// corner (3 edges): bottom left
		ids.push_back(size_one_side * size_one_side - size_one_side + 1);
		ids.push_back(size_one_side * size_one_side - size_one_side - size_one_side);
		ids.push_back(size_one_side * size_one_side - size_one_side - size_one_side + 1);
	}
	// Edges
	else if (node_id % size_one_side == 0)
	{
		// left (4 edges)
		ids.push_back(node_id + size_one_side);
		ids.push_back(node_id - size_one_side);
		ids.push_back(node_id - size_one_side + 1);
		ids.push_back(node_id + 1);
	}
	else if (node_id % size_one_side == (size_one_side - 1))
	{
		// Right (4 edges)
		ids.push_back(node_id + size_one_side);
		ids.push_back(node_id + size_one_side - 1);
		ids.push_back(node_id - size_one_side);
		ids.push_back(node_id - 1);
	}
	else if (node_id < (size_one_side - 1) )
	{
		// top (4 edges)
		ids.push_back(node_id + 1);
		ids.push_back(node_id - 1);
		ids.push_back(node_id + size_one_side);
		ids.push_back(node_id + size_one_side - 1);
	}
	else if (node_id > (size_one_side * size_one_side - size_one_side))
	{
		// bottom (4 edges)
		ids.push_back(node_id + 1);
		ids.push_back(node_id - 1);
		ids.push_back(node_id - size_one_side);
		ids.push_back(node_id - size_one_side + 1);
	}
	// Middle nodes
	else
	{
		// (6 edges)
		ids.push_back(node_id + 1);
		ids.push_back(node_id - 1);
		ids.push_back(node_id - size_one_side);
		ids.push_back(node_id - size_one_side + 1);
		ids.push_back(node_id + size_one_side);
		ids.push_back(node_id + size_one_side - 1);
	}

	return ids;
}