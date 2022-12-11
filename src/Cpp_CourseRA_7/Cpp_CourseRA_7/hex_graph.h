#pragma once

namespace HexGraph
{
	class hex_node
	{
		int id;
		int piece_type;// change to enum
	public:
		hex_node():id(0), piece_type(0){}
		hex_node(int id);
		int get_piece();
		void set_piece(int piece);
	};

	class hex_graph
	{
		int size_one_side;
		hex_node* nodes;
	public:
		hex_graph(int size);
		~hex_graph();
		void print_board();
		bool add_user_move(int position, int piece_type);
		int game_finished();
		int make_computer_move();
	};
}