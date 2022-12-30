#pragma once

#include <string>
#include <iostream>
#include <windows.h>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ZERO 48
#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53
#define SIX 54
#define SEVEN 55
#define EIGHT 56
#define NINE 57
#define B 98
#define F 102
#define S 115
#define ESC 27
#define SPACE 32

struct boardChip {
	char piece;
	int x_position;
	int y_position;
	bool inPlay;
};

class stratego_operations {
private:
	

	string board[10][10];
	string saved_board[10][10];
	int curser_x_position = 0;
	int curser_y_position = 0;
	boardChip player1_pieces[40];
	boardChip player2_pieces[40];
	char player1_powerful_piece;
	char player2_powerful_piece;
	char placment_piece;
	string file_path1;
	string file_path2;
	string file_path3;
	string file_path4;
	int player_turn;
	bool game_loaded = false;

	void add_curser_to_board();

	void remove_curser_from_board();

public:
	void initialize_board();
	void initialize_saved_board();
	void initialize_player1_pieces();
	void initialize_player2_pieces();
	void initialize_game_saver(string working_directory);
	void move_curser_position(int direction);
	void set_up_handler(int command);
	int get_pieces_out_of_play(char piece);
	void place_piece(char piece);
	void display_player1_out_of_play_pieces();
	void display_player2_out_of_play_pieces();
	void battle(boardChip player1_piece, boardChip player2_piece);
	void show_player1();
	void show_player2();
	void hide_player1();
	void hide_player2();
	void update_player1_powerful_piece();
	void update_player2_powerful_piece();
	void display_board();
	void display_saved_board();
	void game_setup_loop();
	int get_total_pieces_out_of_play();
	void assign_curser_position_to_player1_piece(char piece);
	void assign_curser_position_to_player2_piece(char piece);
	void remove_player1_piece_from_curser_position();
	void remove_player2_piece_from_curser_position();
	void display_board_in_setup_configuration();
	bool wait_for_player1_game_loop();
	bool wait_for_player2_game_loop();
	void wait_for_player1_setup_loop();
	void wait_for_player2_setup_loop();
	bool select_piece_and_move();
	boardChip get_piece_at_curser_position();
	void save_board();
	void move_player1_piece_at_curser_position_right(int distance);
	void move_player1_piece_at_curser_position_left(int distance);
	void move_player1_piece_at_curser_position_up(int distance);
	void move_player1_piece_at_curser_position_down(int distance);
	void move_player2_piece_at_curser_position_right(int distance);
	void move_player2_piece_at_curser_position_left(int distance);
	void move_player2_piece_at_curser_position_up(int distance);
	void move_player2_piece_at_curser_position_down(int distance);
	void update_piece_positions();
	bool board_chip_clear(int x_position, int y_position);
	bool player1_piece_at_location(int x_position, int y_position);
	bool player2_piece_at_location(int x_position, int y_position);
	void reveal_piece(boardChip board_piece);
	bool player1_win();
	bool player2_win();
	void game_loop();
	void fill_board();
	int move_scout_up();
	int move_scout_down();
	int move_scout_right();
	int move_scout_left();
	boardChip get_piece_at_position(int x_position, int y_position);
	void invert_arrows();
	void save_game(string file_path);
	bool write_file(string file_path, string message);
	string get_board(int player_turn);
	string get_saved_board(int player_turn);
	string read_file(string file_path);
	bool load_game(string file_path);
	bool menu_loop();
};
