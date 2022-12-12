#pragma once
#include <vector>

using namespace std;

namespace HexGraph
{
	enum class piece: short { empty, blue, red };
	enum class path_color : short { white, grey, black };

	class hex_node
	{
		int id;
		piece piece_type;
		path_color color;
		friend class hex_graph;
	public:
		hex_node():id(0), piece_type(piece::empty), color(path_color::white){}
		hex_node(int id);
		piece get_piece();
		void set_piece(piece piecetype);
	};

	class hex_graph
	{
		int size_one_side;
		hex_node* nodes;
		bool path_found(hex_node root);
		vector<int> GetAdjacentNodes(int node_id);
	public:
		hex_graph(int size);
		~hex_graph();
		void print_board();
		bool add_user_move(int row, int col);
		int game_finished();
		int make_computer_move();
	};
}