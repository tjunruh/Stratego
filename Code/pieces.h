#pragma once
#include "piece.h"

class stratego_pieces {
private:
	stratego_piece board[80];
	char most_powerful_piece = '1';
public:
	void initialize_player1_pieces();
	void initialize_player2_pieces();
	int get_id_with_location(int row, int column);
	int get_id_with_rank(int rank, int owner);
	bool players_piece_at_position(int row, int column, int owner);
	void remove_piece(int row, int column, int owner);
	void remove_piece(int id);
	void add_piece(int rank, int owner, int row, int column);
	void set_most_powerful_piece(char symbol);
	char get_symbol(int rank);
	stratego_piece get_piece_data(int id);
	int get_best_rank(int owner);
	void change_piece_position(int id, int new_row, int new_column);
	bool player_pieces_placed(int owner);
	bool player_flag_out_of_play(int player);
	void set_pieces(stratego_piece pieces[80]);
};