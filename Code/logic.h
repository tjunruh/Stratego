#pragma once
#include "pieces.h"
#include "logic_input.h"
#include "direction.h"

enum game_state {
	placing_pieces = 0,
	move_made,
	turn_ended,
	moving_curser,
	piece_selected,
	scout_selected,
	battling
};

class stratego_logic {

private:
	int curser_row = 0;
	int curser_column = 0;
	stratego_pieces board;
	int player_turn;
	int selected_piece_id;
	int new_row;
	int new_column;
	int _distance;
	direction _direction;
	game_state state_of_game;
	stratego_piece defending_piece;
	stratego_piece losing_piece;
	bool _battle;
	int loser_id;

public:
	bool is_valid_curser_position(int row, int column);
	bool is_valid_piece_position(int row, int column);
	bool is_valid_position_to_place_piece(int row);
	bool path_clear(int start_row, int start_column, direction _direction, int distance);
	int determine_loser(int piece1_id, int piece2_id);
	void move_curser(input user_input);
	void select_piece(int row, int column);
	void unselect_piece();
	void move_piece(input user_input);
	void adjust_scout_position(input user_input);
	void adjust_piece_position(input user_input);
	game_state get_game_state();
	void set_game_state(game_state _game_state);
	direction get_direction();
	void set_direction(direction piece_direction);
	void set_direction(int start_row, int start_column, int stop_row, int stop_column);
	void end_turn();
	void reset_board();
	bool player1_pieces_placed();
	bool player2_pieces_placed();
	int get_curser_row();
	int get_curser_column();
	void set_curser_row(int row);
	void set_curser_column(int column);
	void get_board_info(stratego_piece (&board_info)[80]);
	void place_piece(input user_input);
	void set_turn(int turn);
	bool player1_won();
	bool player2_won();
	int get_distance();
	int get_turn();
	int get_selected_piece_row();
	int get_selected_piece_column();
	bool battle();
	stratego_piece get_defending_piece_data();
	stratego_piece get_losing_piece_data();
	void finalize_move();
	void set_board_info(stratego_piece board_info[80]);
};