#pragma once
#include <string>
#include <vector>
#include "piece.h"
#include "direction.h"

class stratego_display {
private:
	// data on game pieces
	stratego_piece _board_pieces[80];

	// visual appearance of all board spaces
	std::string board_spaces[10][10];

	std::string screen_shot;

	std::string printable_board;

	// curser functions
	int _curser_row;
	int _curser_column;
	bool add_curser = false;
	char curser_character_L;
	char curser_character_R;

	int _player_for_orientation = false;

	bool _hide_player1 = false;

	bool _hide_player2 = false;

	int scout_start_row;
	int scout_start_column;
	direction scout_direction;
	int scout_distance;
	bool _add_scout_arrows = false;
	int _player_for_scout_arrows;

	bool _reveal_piece = false;
	int _reveal_piece_row;
	int _reveal_piece_column;

	bool _display_pieces_out_of_play = false;

	bool _save_move = false;

	int _players_move;

	std::string player1_name = "player 1";
	std::string player2_name = "player 2";

	stratego_piece _losing_piece;

	std::string saved_game_name_to_load;

	bool _add_hint = false;

	void execute_add_curser();
	void execute_hide_player1();
	void execute_hide_player2();
	void execute_reveal_piece();
	void execute_add_scout_arrows();
	void display_pieces_out_of_play(int player1_pieces_out[12], int player2_pieces_out[12]);
	void determine_pieces_out_of_play(int(&player1_pieces_out)[12], int(&player2_pieces_out)[12]);
	void add_board_pieces_to_spaces();
	void add_terrain();
	void execute_save_move();
	void execute_show_player1();
	void execute_show_player2();
	void invert_arrows();
	void execute_add_hint();

public:

	void add_move_up_curser(int curser_row, int curser_column);
	void add_move_down_curser(int curser_row, int curser_column);
	void add_move_right_curser(int curser_row, int curser_column);
	void add_move_left_curser(int curser_row, int curser_column);
	void add_standard_curser(int curser_row, int curser_column);
	void orient_for_player(int player);
	void hide_player1();
	void hide_player2();
	void reveal_piece(int row, int column);
	void add_scout_arrows(int start_row, int start_column, direction direction, int distance, int player);
	void add_pieces_out_of_play();
	void display_board(stratego_piece board_pieces[80]);
	void display_player1_preturn_menu();
	void display_player2_preturn_menu();
	void display_controls();
	void display_load_game_menu(std::vector<std::string> saved_game_names, int selected_game);
	void set_player1_name(std::string name);
	void set_player2_name(std::string name);
	void save_move(int player, stratego_piece losing_piece);
	void display_saved_move();
	bool screen_shot_empty();
	std::string get_screen_shot();
	void set_screen_shot(std::string shot);
	void reset();
	std::string get_player1_name();
	std::string get_player2_name();
	void add_hint();
};
