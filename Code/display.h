#pragma once
#include <string>
#include <vector>
#include "piece.h"
#include "direction.h"
#include <ascii_board.h>
#include <label.h>
#include <text_box.h>
#include <menu.h>
#include <controls.h>
#include <format_tools.h>

class stratego_display {
private:
	// data on game pieces
	stratego_piece _board_pieces[80];

	std::string screen_shot;

	std::vector<format_tools::index_format> screen_shot_colors;

	// curser functions
	int _curser_row;
	int _curser_column;
	bool add_curser = false;
	std::string cursor_config;

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

	void execute_add_curser();
	void execute_hide_player1();
	void execute_hide_player2();
	void execute_reveal_piece();
	void execute_add_scout_arrows();
	void display_pieces_out_of_play(int player1_pieces_out[12], int player2_pieces_out[12]);
	void determine_pieces_out_of_play(int(&player1_pieces_out)[12], int(&player2_pieces_out)[12]);
	void execute_save_move();
	void execute_show_player1();
	void execute_show_player2();
	void invert_arrows();
	void reset_color(std::string control_name, int color_code);
	void initialize_settings_menu();
	label board_heading;
	ascii_board board;
	label pieces_out_label;
	frame* main_frame;

	label multipurpose_label;
	text_box multipurpose_text_box;
	frame* multipurpose_frame;

	label load_game_label;
	menu load_game_menu;
	frame* load_game_frame;

	label settings_label;
	menu settings_menu;
	frame* settings_frame;

	controls* game_controls;

	enum setting_type
	{
		regular,
		boolean,
		color
	};

	struct control_settings_menu_item
	{
		std::string name_id = "";
		setting_type type = regular;
	};

	const std::vector<control_settings_menu_item> control_settings_menu_items
	{
		{"up", regular},
		{"down", regular},
		{"right", regular},
		{"left", regular},
		{"spy", regular},
		{"flag", regular},
		{"1", regular},
		{"2", regular},
		{"3", regular},
		{"4", regular},
		{"5", regular},
		{"6", regular},
		{"7", regular},
		{"8", regular},
		{"9", regular},
		{"bomb", regular},
		{"select", regular},
		{"quit", regular},
		{"delete", regular},
		{"new turn", regular},
		{"finalize", regular},
		{"help", regular},
		{"save", regular},
		{"enable line drawing", boolean},
		{"enable color", boolean},
		{"background color", color},
		{"foreground color", color},
		{"cursor color", color},
		{"cursor arrow color", color},
		{"scout arrow color", color},
		{"spy color", color},
		{"flag color", color},
		{"1 color", color},
		{"2 color", color},
		{"3 color", color},
		{"4 color", color},
		{"5 color", color},
		{"6 color", color},
		{"7 color", color},
		{"8 color", color},
		{"9 color", color},
		{"bomb color", color},
		{"hidden piece color", color},
		{"bold foreground", boolean}
	};

	struct config_name_color_pair
	{
		std::string name_id = "";
		std::string value = "";
	};

	struct config_color_group
	{
		std::string color = "";
		std::vector<config_name_color_pair> groups;
	};

	const std::vector<config_color_group> color_group_map
	{
		{"cursor color", {{"cursor", "(*)"}}},
		{"cursor arrow color", {{"up_cursor", "^*^"}, {"down_cursor", "v*v"}, {"left_cursor", "<*<"}, {"right_cursor", ">*>"}}},
		{"scout arrow color", {{"scout_up", "*^*"}, {"scout_down", "*v*"}, {"scout_left", "*<*"}, {"scout_right", "*>*"}}},
		{"spy color", {{"-1", "*s*"}}},
		{"flag color", {{"0", "*f*"}}},
		{"1 color", {{"1", "*1*"}}},
		{"2 color", {{"2", "*2*"}}},
		{"3 color", {{"3", "*3*"}}},
		{"4 color", {{"4", "*4*"}}},
		{"5 color", {{"5", "*5*"}}},
		{"6 color", {{"6", "*6*"}}},
		{"7 color", {{"7", "*7*"}}},
		{"8 color", {{"8", "*8*"}}},
		{"9 color", {{"9", "*9*"}}},
		{"bomb color", {{"-2", "*b*"}}},
		{"hidden piece color", {{"hide", "*X*"}}}
	};

public:
	stratego_display(frame* main_display, frame* multipurpose_display, frame* load_game_display, frame* settings_display, controls* game_controls);
	void add_move_up_curser(int curser_row, int curser_column);
	void add_move_down_curser(int curser_row, int curser_column);
	void add_move_right_curser(int curser_row, int curser_column);
	void add_move_left_curser(int curser_row, int curser_column);
	void add_standard_curser(int curser_row, int curser_column);
	void add_heading(std::string heading);
	void orient_for_player(int player);
	void hide_player1();
	void hide_player2();
	void reveal_piece(int row, int column);
	void add_scout_arrows(int start_row, int start_column, direction direction, int distance, int player);
	void add_pieces_out_of_play();
	void display_board(stratego_piece board_pieces[80]);
	void display_get_player1_name();
	void display_get_player2_name();
	void display_player1_preturn_menu();
	void display_player2_preturn_menu();
	void display_player_won(int player);
	std::string display_save_game();
	void display_controls();
	void set_player1_name(std::string name);
	void set_player2_name(std::string name);
	void display_load_game_menu(std::vector<std::string> saved_game_names, std::string& selection, int& key_stroke);
	void save_move(int player, stratego_piece losing_piece);
	void display_saved_move(int player);
	bool screen_shot_empty();
	std::string get_screen_shot();
	void set_screen_shot(std::string shot);
	void reset();
	std::string get_player1_name();
	std::string get_player2_name();
	void erase_screen_shot();
	void display_set_controls();
};
