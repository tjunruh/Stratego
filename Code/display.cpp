#include "display.h"
#include <ascii_io.h>
#include <frame.h>
#include <ascii_board.h>
#include <label.h>
#include <string>
#include <menu.h>
#include "file_managment.h"

stratego_display::stratego_display(frame* main_display, frame* multipurpose_display, frame* load_game_display, frame* settings_display, controls* master_game_controls) :
	board_heading(main_display),
	board(main_display, "board_configs/stratego_board.txt", "default", "new line"),
	pieces_out_label(main_display, "new line"),
	multipurpose_label(multipurpose_display),
	multipurpose_text_box(multipurpose_display, "new line", 3),
	load_game_label(load_game_display),
	load_game_menu(load_game_display, "new line"),
	settings_label(settings_display),
	settings_menu(settings_display, "new line")
{
	main_frame = main_display;
	board_heading.set_alignment("center");
	board.set_alignment("center block");
	pieces_out_label.set_alignment("center block");
	board.load_board_translation("reverse", "board_configs/stratego_reverse_board.txt");
	game_controls = master_game_controls;
	bool bold = game_controls->get_key("bold foreground");
	board.add_configuration("hide", -1, -1, "*X*", '*', build_central_element_color_structure(game_controls->get_key("hidden piece color"), bold));
	board.add_configuration("0", -1, -1, "*f*", '*', build_central_element_color_structure(game_controls->get_key("flag color"), bold));
	board.add_configuration("-1", -1, -1, "*s*", '*', build_central_element_color_structure(game_controls->get_key("spy color"), bold));
	board.add_configuration("-2", -1, -1, "*b*", '*', build_central_element_color_structure(game_controls->get_key("bomb color"), bold));
	board.add_configuration("1", -1, -1, "*1*", '*', build_central_element_color_structure(game_controls->get_key("1 color"), bold));
	board.add_configuration("2", -1, -1, "*2*", '*', build_central_element_color_structure(game_controls->get_key("2 color"), bold));
	board.add_configuration("3", -1, -1, "*3*", '*', build_central_element_color_structure(game_controls->get_key("3 color"), bold));
	board.add_configuration("4", -1, -1, "*4*", '*', build_central_element_color_structure(game_controls->get_key("4 color"), bold));
	board.add_configuration("5", -1, -1, "*5*", '*', build_central_element_color_structure(game_controls->get_key("5 color"), bold));
	board.add_configuration("6", -1, -1, "*6*", '*', build_central_element_color_structure(game_controls->get_key("6 color"), bold));
	board.add_configuration("7", -1, -1, "*7*", '*', build_central_element_color_structure(game_controls->get_key("7 color"), bold));
	board.add_configuration("8", -1, -1, "*8*", '*', build_central_element_color_structure(game_controls->get_key("8 color"), bold));
	board.add_configuration("9", -1, -1, "*9*", '*', build_central_element_color_structure(game_controls->get_key("9 color"), bold));
	board.add_configuration("cursor", -1, -1, "(*)", '*', build_cursor_color_structure(game_controls->get_key("cursor color"), bold));
	board.add_configuration("up_cursor", -1, -1, "^*^", '*', build_cursor_color_structure(game_controls->get_key("cursor arrow color"), bold));
	board.add_configuration("down_cursor", -1, -1, "v*v", '*', build_cursor_color_structure(game_controls->get_key("cursor arrow color"), bold));
	board.add_configuration("left_cursor", -1, -1, "<*<", '*', build_cursor_color_structure(game_controls->get_key("cursor arrow color"), bold));
	board.add_configuration("right_cursor", -1, -1, ">*>", '*', build_cursor_color_structure(game_controls->get_key("cursor arrow color"), bold));
	board.add_configuration("scout_up", -1, -1, "*^*", '*', build_central_element_color_structure(game_controls->get_key("scout arrow color"), bold));
	board.add_configuration("scout_down", -1, -1, "*v*", '*', build_central_element_color_structure(game_controls->get_key("scout arrow color"), bold));
	board.add_configuration("scout_left", -1, -1, "*<*", '*', build_central_element_color_structure(game_controls->get_key("scout arrow color"), bold));
	board.add_configuration("scout_right", -1, -1, "*>*", '*', build_central_element_color_structure(game_controls->get_key("scout arrow color"), bold));

	multipurpose_frame = multipurpose_display;
	multipurpose_text_box.set_width_multiplier(1.0);
	multipurpose_text_box.use_spacing_width_multipliers(true);
	multipurpose_text_box.set_spacing_width_multipliers(1.0, 1.0);
	multipurpose_label.set_alignment("center block");

	main_frame->enable_dec(game_controls->get_key("enable line drawing"));
	multipurpose_frame->enable_dec(game_controls->get_key("enable line drawing"));

	main_frame->enable_color(game_controls->get_key("enable color"));
	multipurpose_frame->enable_color(game_controls->get_key("enable color"));

	main_frame->set_default_background_color(game_controls->get_key("background color"));
	main_frame->set_default_foreground_color(game_controls->get_key("foreground color"));
	multipurpose_frame->set_default_background_color(game_controls->get_key("background color"));
	multipurpose_frame->set_default_foreground_color(game_controls->get_key("foreground color"));

	load_game_frame = load_game_display;
	load_game_label.set_spacing(2, 0, 0, 0);
	load_game_label.set_alignment("center");
	load_game_menu.set_alignment("center");
	load_game_menu.add_border(true);
	load_game_menu.enable_quit();

	settings_frame = settings_display;
	settings_label.set_alignment("center");
	settings_label.set_output("Settings Menu");
	settings_menu.enable_quit();
	settings_menu.separate_items(true);
	settings_menu.set_alignment("center");
	settings_menu.add_border(true);

	initialize_settings_menu();
}

std::vector<format_tools::index_format> stratego_display::build_cursor_color_structure(int color, bool bold)
{
	std::vector<format_tools::index_format> colors;
	if (color != format_tools::none)
	{
		format_tools::index_format color1;
		color1.format.foreground_format = color;
		color1.format.bold = bold;
		color1.index = 0;
		format_tools::index_format color2;
		color2.format.foreground_format = format_tools::none;
		color2.index = 1;
		format_tools::index_format color3;
		color3.format.foreground_format = color;
		color3.format.bold = bold;
		color3.index = 2;
		colors.push_back(color1);
		colors.push_back(color2);
		colors.push_back(color3);
	}
	return colors;
}

std::vector<format_tools::index_format> stratego_display::build_central_element_color_structure(int color, bool bold)
{
	std::vector<format_tools::index_format> colors;
	if (color != format_tools::none)
	{
		format_tools::index_format color1;
		color1.format.foreground_format = color;
		color1.format.bold = bold;
		color1.index = 1;
		colors.push_back(color1);
	}
	return colors;
}

void stratego_display::reset_color(std::string control_name, int color_code)
{
	for (unsigned int i = 0; i < color_group_map.size(); i++)
	{
		if (color_group_map[i].color == control_name)
		{
			for (unsigned int j = 0; j < color_group_map[i].groups.size(); j++)
			{
				std::vector<format_tools::index_format> color;
				if (color_group_map[i].groups[j].type == central)
				{
					color = build_central_element_color_structure(color_code, game_controls->get_key("bold foreground"));
				}
				else if (color_group_map[i].groups[j].type == cursor)
				{
					color = build_cursor_color_structure(color_code, game_controls->get_key("bold foreground"));
				}
				board.set_sub_configuration_color(color_group_map[i].groups[j].name_id, color_group_map[i].groups[j].value, color);
			}
		}
	}
}

void stratego_display::initialize_settings_menu()
{
	settings_menu.set_lines_count(-6);
	std::vector<int> menu_select_buttons;
	menu_select_buttons.push_back(game_controls->get_key("select"));
	settings_menu.set_controls(menu_select_buttons, game_controls->get_key("up"), game_controls->get_key("down"), game_controls->get_key("quit"));

	for (unsigned int i = 0; i < control_settings_menu_items.size(); i++)
	{
		settings_menu.append_item(control_settings_menu_items[i].name_id);
		std::string label_name;
		if (control_settings_menu_items[i].type == regular)
		{
			label_name = ascii_io::get_key_name(game_controls->get_key(control_settings_menu_items[i].name_id));
		}
		else if (control_settings_menu_items[i].type == color)
		{
			label_name = format_tools::get_color_name(game_controls->get_key(control_settings_menu_items[i].name_id));
		}
		else if (control_settings_menu_items[i].type == boolean)
		{
			if (game_controls->get_key(control_settings_menu_items[i].name_id) == 0)
			{
				label_name = "No";
			}
			else if (game_controls->get_key(control_settings_menu_items[i].name_id) == 1)
			{
				label_name = "Yes";
			}
		}
		settings_menu.set_item_label(control_settings_menu_items[i].name_id, label_name);
	}
}

void stratego_display::add_move_up_curser(int curser_row, int curser_column) {
	cursor_config = "up_cursor";
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_move_down_curser(int curser_row, int curser_column) {
	cursor_config = "down_cursor";
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_move_right_curser(int curser_row, int curser_column) {
	cursor_config = "right_cursor";
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_move_left_curser(int curser_row, int curser_column) {
	cursor_config = "left_cursor";
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_standard_curser(int curser_row, int curser_column) {
	cursor_config = "cursor";
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_heading(std::string heading)
{
	board_heading.set_output(heading);
}

void stratego_display::orient_for_player(int player) {
	_player_for_orientation = player;
}


void stratego_display::hide_player1() {
	_hide_player1 = true;
}

void stratego_display::hide_player2() {
	_hide_player2 = true;
}

void stratego_display::reveal_piece(int row, int column) {
	_reveal_piece_row = row;
	_reveal_piece_column = column;
	_reveal_piece = true;
}

void stratego_display::execute_hide_player1() {
	for (int piece = 0; piece < 80; piece++) {
		if ((_board_pieces[piece].get_owner() == 1) && _board_pieces[piece].get_inPlay()) {
			board.activate_configuration("hide", _board_pieces[piece].get_row(), _board_pieces[piece].get_column());
		}
	}
}

void stratego_display::execute_hide_player2() {
	for (int piece = 0; piece < 80; piece++) {
		if ((_board_pieces[piece].get_owner() == 2) && _board_pieces[piece].get_inPlay()) {
			board.activate_configuration("hide", _board_pieces[piece].get_row(), _board_pieces[piece].get_column());
		}
	}
}

void stratego_display::execute_reveal_piece() {
	for (int piece = 0; piece < 80; piece++) {
		if (_board_pieces[piece].get_inPlay() && (_board_pieces[piece].get_row() == _reveal_piece_row) && (_board_pieces[piece].get_column() == _reveal_piece_column))
			board.activate_configuration(std::to_string(_board_pieces[piece].get_rank()), _reveal_piece_row, _reveal_piece_column);
	}
}

void stratego_display::execute_add_curser() {
	board.activate_configuration(cursor_config, _curser_row, _curser_column);
}

void stratego_display::determine_pieces_out_of_play(int(&player1_pieces_out)[12], int(&player2_pieces_out)[12]) {
	for (int player = 1; player < 3; player++) {
		int present_pieces[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		for (int piece = 0; piece < 80; piece++) {
			if ((_board_pieces[piece].get_owner() == player) && (!_board_pieces[piece].get_inPlay())) {
				int current_piece = _board_pieces[piece].get_rank();
				if (current_piece == 9) {
					present_pieces[9]++;
				}
				else if (current_piece == 8) {
					present_pieces[8]++;
				}
				else if (current_piece == 7) {
					present_pieces[7]++;
				}
				else if (current_piece == 6) {
					present_pieces[6]++;
				}
				else if (current_piece == 5) {
					present_pieces[5]++;
				}
				else if (current_piece == 4) {
					present_pieces[4]++;
				}
				else if (current_piece == 3) {
					present_pieces[3]++;
				}
				else if (current_piece == 2) {
					present_pieces[2]++;
				}
				else if (current_piece == 1) {
					present_pieces[1]++;
				}
				else if (current_piece == -1) {
					present_pieces[10]++;
				}
				else if (current_piece == -2) {
					present_pieces[11]++;
				}
				else if (current_piece == 0) {
					present_pieces[0]++;
				}
			}
		}
		for (int i = 0; i < 12; i++) {
			if (player == 1) {
				player1_pieces_out[i] = present_pieces[i];
			}
			else if (player == 2) {
				player2_pieces_out[i] = present_pieces[i];
			}
			present_pieces[i] = 0;
		}
		
	}
}

void stratego_display::display_pieces_out_of_play(int player1_pieces_out[12], int player2_pieces_out[12]) {
	std::string player1_disp = get_player1_name() + "'s pieces out of play:                   \n";
	std::string player2_disp = get_player2_name() + "'s pieces out of play:                   \n";
	for (int piece_type = 0; piece_type < 12; piece_type++) {
		if (piece_type == 0) {
			if (player1_pieces_out[piece_type] != 0) {
				player1_disp = player1_disp + "fx" + std::to_string(player1_pieces_out[piece_type]) + " ";
			}
			
			if (player2_pieces_out[piece_type] != 0) {
				player2_disp = player2_disp + "fx" + std::to_string(player2_pieces_out[piece_type]) + " ";
			}
		}
		else if (piece_type == 10) {
			if (player1_pieces_out[piece_type] != 0) {
				player1_disp = player1_disp + "sx" + std::to_string(player1_pieces_out[piece_type]) + " ";
			}

			if (player2_pieces_out[piece_type] != 0) {
				player2_disp = player2_disp + "sx" + std::to_string(player2_pieces_out[piece_type]) + " ";
			}
		}
		else if (piece_type == 11) {
			if (player1_pieces_out[piece_type] != 0) {
				player1_disp = player1_disp + "bx" + std::to_string(player1_pieces_out[piece_type]) + " ";
			}

			if (player2_pieces_out[piece_type] != 0) {
				player2_disp = player2_disp + "bx" + std::to_string(player2_pieces_out[piece_type]) + " ";
			}
		}
		else {
			if (player1_pieces_out[piece_type] != 0) {
				player1_disp = player1_disp + std::to_string(piece_type) + "x" + std::to_string(player1_pieces_out[piece_type]) + " ";
			}

			if (player2_pieces_out[piece_type] != 0) {
				player2_disp = player2_disp + std::to_string(piece_type) + "x" + std::to_string(player2_pieces_out[piece_type]) + " ";
			}
		}
	}
	pieces_out_label.set_output(player1_disp + "\n" + player2_disp);
}

void stratego_display::add_pieces_out_of_play() {
	_display_pieces_out_of_play = true;
}

void stratego_display::add_scout_arrows(int start_row, int start_column, direction direction, int distance, int player) {
	scout_start_row = start_row;
	scout_start_column = start_column;
	scout_direction = direction;
	scout_distance = distance;
	_player_for_scout_arrows = player;
	_add_scout_arrows = true;
}

void stratego_display::execute_add_scout_arrows() {
	int moving_coordinate = 0;
	if (scout_direction == up) {
		if (_player_for_scout_arrows == 1) {
			for (moving_coordinate = scout_start_row - 1; moving_coordinate > (scout_start_row - scout_distance); moving_coordinate--) {
				board.activate_configuration("scout_up", moving_coordinate, scout_start_column);
			}
		}
		else if (_player_for_scout_arrows == 2) {
			for (moving_coordinate = scout_start_row + 1; moving_coordinate < (scout_start_row + scout_distance); moving_coordinate++) {
				board.activate_configuration("scout_up", moving_coordinate, scout_start_column);
			}
		}
	}
	else if (scout_direction == down) {
		if (_player_for_scout_arrows == 1) {
			for (moving_coordinate = scout_start_row + 1; moving_coordinate < (scout_start_row + scout_distance); moving_coordinate++) {
				board.activate_configuration("scout_down", moving_coordinate, scout_start_column);
			}
		}
		else if (_player_for_scout_arrows == 2) {
			for (moving_coordinate = scout_start_row - 1; moving_coordinate > (scout_start_row - scout_distance); moving_coordinate--) {
				board.activate_configuration("scout_down", moving_coordinate, scout_start_column);
			}
		}
	}
	else if (scout_direction == right) {
		if (_player_for_scout_arrows == 1) {
			for (moving_coordinate = scout_start_column + 1; moving_coordinate < (scout_start_column + scout_distance); moving_coordinate++) {
				board.activate_configuration("scout_right", scout_start_row, moving_coordinate);
			}
		}
		else if (_player_for_scout_arrows == 2) {
			for (moving_coordinate = scout_start_column - 1; moving_coordinate > (scout_start_column - scout_distance); moving_coordinate--) {
				board.activate_configuration("scout_right", scout_start_row, moving_coordinate);
			}
		}
	}
	else if (scout_direction == left) {
		if (_player_for_scout_arrows == 1) {
			for (moving_coordinate = scout_start_column - 1; moving_coordinate > (scout_start_column - scout_distance); moving_coordinate--) {
				board.activate_configuration("scout_left", scout_start_row, moving_coordinate);
			}
		}
		else if (_player_for_scout_arrows == 2) {
			for (moving_coordinate = scout_start_column + 1; moving_coordinate < (scout_start_column + scout_distance); moving_coordinate++) {
				board.activate_configuration("scout_left", scout_start_row, moving_coordinate);
			}
		}
	}
}

void stratego_display::reset() {
	add_curser = false;
	_hide_player1 = false;
	_hide_player2 = false;
	_add_scout_arrows = false;
	_reveal_piece = false;
	_display_pieces_out_of_play = false;
	_save_move = false;
	board_heading.set_output("");
	board.clear_all();
}

void stratego_display::display_board(stratego_piece board_pieces[80]) {
	for (int i = 0; i < 80; i++) {
		_board_pieces[i] = board_pieces[i];
	}

	if (_hide_player1) {
		execute_hide_player1();
		execute_show_player2();
	}
	else if (_hide_player2) {
		execute_hide_player2();
		execute_show_player1();
	}
	else
	{
		execute_show_player1();
		execute_show_player2();
	}

	if (_reveal_piece) {
		execute_reveal_piece();
	}

	if (add_curser) {
		execute_add_curser();
	}

	if (_add_scout_arrows) {
		execute_add_scout_arrows();
	}

	if (_player_for_orientation == 1) {
		board.use_translation("default");
	}
	else if (_player_for_orientation == 2) {
		board.use_translation("reverse");
	}

	board.build();

	if (_display_pieces_out_of_play) {
		int player1_pieces_out[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int player2_pieces_out[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		determine_pieces_out_of_play(player1_pieces_out, player2_pieces_out);
		display_pieces_out_of_play(player1_pieces_out, player2_pieces_out);
	}

	main_frame->display();

	if (_save_move) {
		execute_save_move();
	}
	
	reset();
}

void stratego_display::display_get_player1_name()
{
	int input = ascii_io::undefined;
	multipurpose_label.set_output("Enter your name player 1");
	multipurpose_label.set_spacing(15, 0, 0, 0);
	multipurpose_text_box.add_border(true);
	multipurpose_frame->display();
	do
	{
		input = multipurpose_text_box.write();
	} while (input != ascii_io::enter);
	player1_name = multipurpose_text_box.get_text();
	ascii_io::hide_cursor();
	multipurpose_text_box.add_border(false);
	multipurpose_text_box.clear();
}

void stratego_display::display_get_player2_name()
{
	int input = ascii_io::undefined;
	multipurpose_label.set_output("Enter your name player 2");
	multipurpose_label.set_spacing(15, 0, 0, 0);
	multipurpose_text_box.add_border(true);
	multipurpose_frame->display();
	do
	{
		input = multipurpose_text_box.write();
	} while (input != ascii_io::enter);
	player2_name = multipurpose_text_box.get_text();
	ascii_io::hide_cursor();
	multipurpose_text_box.add_border(false);
	multipurpose_text_box.clear();
}

void stratego_display::display_player1_preturn_menu() {
	multipurpose_label.set_output(player1_name + "'s turn. Press space to begin.");
	multipurpose_label.set_spacing(15, 0, 0, 0);
	multipurpose_frame->display();
}

void stratego_display::display_player2_preturn_menu() {
	multipurpose_label.set_output(player2_name + "'s turn. Press space to begin.");
	multipurpose_label.set_spacing(15, 0, 0, 0);
	multipurpose_frame->display();
}

void stratego_display::display_player_won(int player)
{
	std::string output = "";
	if (player == 1)
	{
		output = player1_name + " won!";
	}
	else if (player == 2)
	{
		output = player2_name + " won!";
	}

	multipurpose_label.set_spacing(15, 0, 0, 0);
	multipurpose_label.set_output(output);
	multipurpose_frame->display();
	int input = ascii_io::undefined;
	do
	{
		input = ascii_io::getchar();
	} while (input != ascii_io::enter);
}

std::string stratego_display::display_save_game()
{
	multipurpose_label.set_spacing(15, 0, 0, 0);
	multipurpose_label.set_output("Enter a name (duplicate names will be rejected):");
	multipurpose_text_box.add_border(true);
	multipurpose_frame->display();
	int input = ascii_io::undefined;
	do
	{
		input = multipurpose_text_box.write();
	} while (input != ascii_io::enter);
	std::string game_name = multipurpose_text_box.get_text();
	ascii_io::hide_cursor();
	multipurpose_text_box.add_border(false);
	multipurpose_text_box.clear();
	return game_name;
}

void stratego_display::display_controls() {
	ascii_io::print("CONTROLS:\n\n");
	ascii_io::print("Go back   : q\n\n");
	ascii_io::print("MOVING CURSER\n");
	ascii_io::print("Operation : Button\n");
	ascii_io::print("Move up   : Up arrow\n");
	ascii_io::print("Move down : Down arrow\n");
	ascii_io::print("Move right: Right arrow\n");
	ascii_io::print("Move left : Left arrow\n");
	ascii_io::print("\n");
	ascii_io::print("GAME SETUP\n");
	ascii_io::print("Operation : Button\n");
	ascii_io::print("Place 1   : 1\n");
	ascii_io::print("Place 2   : 2\n");
	ascii_io::print("Place 3   : 3\n");
	ascii_io::print("Place 4   : 4\n");
	ascii_io::print("Place 5   : 5\n");
	ascii_io::print("Place 6   : 6\n");
	ascii_io::print("Place 7   : 7\n");
	ascii_io::print("Place 8   : 8\n");
	ascii_io::print("Place 9   : 9\n");
	ascii_io::print("Place s   : s\n");
	ascii_io::print("Place b   : b\n");
	ascii_io::print("Place f   : f\n");
	ascii_io::print("If you want to remove a piece from the board, place another piece on top of it.\nThis will replace the piece on the board with the new piece.\n");
	ascii_io::print("\n");
	ascii_io::print("GAME PLAY PIECE MANIPULATION\n");
	ascii_io::print("Operation : Button\n");
	ascii_io::print("Select    : Enter\n");
	ascii_io::print("Unselect  : q\n");
	ascii_io::print("Move up   : Up arrow\n");
	ascii_io::print("Move down : Down arrow\n");
	ascii_io::print("Move right: Right arrow\n");
	ascii_io::print("Move left : Left arrow\n");
	ascii_io::print("Finalize  : Enter\n");
	ascii_io::print("Save      : S\n");
	ascii_io::print("Note that you can only save the game at a preturn menu.\n\n");
	ascii_io::print("To delete a game, you can press d while the game is selected\n in the load menu.");
}

void stratego_display::set_player1_name(std::string name) {
	player1_name = name;
}

void stratego_display::set_player2_name(std::string name) {
	player2_name = name;
}

void stratego_display::execute_save_move() {
	screen_shot = "";
	screen_shot_colors.clear();
	if (_players_move == 1) {
		execute_show_player2();
		execute_hide_player1();
		invert_arrows();
		if ((_losing_piece.get_owner() == 1) && _losing_piece.get_inPlay()) {
			reveal_piece(_losing_piece.get_row(), _losing_piece.get_column());
			execute_reveal_piece();
		}
		board.use_translation("reverse");
		board.build();
		board.get_board_and_colors(screen_shot, screen_shot_colors);
	}
	else if (_players_move == 2) {
		execute_show_player1();
		execute_hide_player2();
		invert_arrows();
		if ((_losing_piece.get_owner() == 2) && _losing_piece.get_inPlay()) {
			reveal_piece(_losing_piece.get_row(), _losing_piece.get_column());
			execute_reveal_piece();
		}
		board.use_translation("default");
		board.build();
		board.get_board_and_colors(screen_shot, screen_shot_colors);
	}
}

void stratego_display::execute_show_player1() {
	for (int piece = 0; piece < 80; piece++) {
		if ((_board_pieces[piece].get_owner() == 1) && _board_pieces[piece].get_inPlay()) {
			board.activate_configuration(std::to_string(_board_pieces[piece].get_rank()), _board_pieces[piece].get_row(), _board_pieces[piece].get_column());
		}
	}
}

void stratego_display::execute_show_player2() {
	for (int piece = 0; piece < 80; piece++) {
		if ((_board_pieces[piece].get_owner() == 2) && _board_pieces[piece].get_inPlay()) {
			board.activate_configuration(std::to_string(_board_pieces[piece].get_rank()), _board_pieces[piece].get_row(), _board_pieces[piece].get_column());
		}
	}
}

void stratego_display::save_move(int player, stratego_piece losing_piece) {
	_save_move = true;
	if ((player == 1) || (player == 2)) {
		_players_move = player;
		_losing_piece = losing_piece;
	}
}

void stratego_display::display_saved_move(int player) {
	std::string output = "";
	
	if (player == 1)
	{
		output = player1_name + "'s move. Press enter to continue.\n";
	}
	else if (player == 2)
	{
		output = player2_name + "'s move. Press enter to continue.\n";
	}
	screen_shot_colors = format_tools::shift_index(screen_shot_colors, output.length());
	output = output + screen_shot;
	multipurpose_label.set_output(output);
	multipurpose_label.set_colors(screen_shot_colors);
	multipurpose_label.set_spacing(0, 0, 0, 0);
	multipurpose_frame->display();
	std::vector<format_tools::index_format> clear_colors;
	multipurpose_label.set_colors(clear_colors);
	int input = ascii_io::undefined;
	do
	{
		input = ascii_io::getchar();
	} while (input != ascii_io::enter);
}

void stratego_display::invert_arrows() {
	if (add_curser) {
		if (cursor_config == "up_cursor") {
			board.modify_configuration("up_cursor", "down_cursor");
		}
		else if (cursor_config == "down_cursor") {
			board.modify_configuration("down_cursor", "up_cursor");
		}
		else if (cursor_config == "right_cursor") {
			board.modify_configuration("right_cursor", "left_cursor");
		}
		else if (cursor_config == "left_cursor") {
			board.modify_configuration("left_cursor", "right_cursor");
		}
	}
	
	if (_add_scout_arrows) {
		if (scout_direction == up) {
			board.modify_configuration("scout_up", "scout_down");
		}
		else if (scout_direction == down) {
			board.modify_configuration("scout_down", "scout_up");
		}
		else if (scout_direction == right) {
			board.modify_configuration("scout_right", "scout_left");
		}
		else if (scout_direction == left) {
			board.modify_configuration("scout_left", "scout_right");
		}
	}
}

bool stratego_display::screen_shot_empty() {
	if (screen_shot == "") {
		return true;
	}
	else {
		return false;
	}
}

void stratego_display::display_load_game_menu(std::vector<std::string> saved_game_names, std::string& selection, int& key_stroke) {
	int x = 0;
	int y = 0;
	ascii_io::get_terminal_size(x, y);
	y = y / 2;
	if ((y - 5) > 10)
	{
		y = y - 5;
	}
	load_game_menu.set_lines_count(-6);
	load_game_frame->enable_dec(game_controls->get_key("enable line drawing"));

	if (game_controls->get_key("enable color"))
	{
		load_game_frame->set_default_background_color(game_controls->get_key("background color"));
		load_game_frame->set_default_foreground_color(game_controls->get_key("foreground color"));
	}

	std::vector<int> menu_select_buttons;
	menu_select_buttons.push_back(game_controls->get_key("select"));
	menu_select_buttons.push_back(game_controls->get_key("delete"));
	load_game_menu.set_controls(menu_select_buttons, game_controls->get_key("up"), game_controls->get_key("down"), game_controls->get_key("quit"));
	
	load_game_label.set_output("Saved Games");
	unsigned int cursor_item = load_game_menu.get_cursor_item();
	load_game_menu.remove_all_items();
	for (unsigned int i = 0; i < saved_game_names.size(); i++)
	{
		load_game_menu.append_item(saved_game_names[i]);
	}
	load_game_menu.set_cursor_item(cursor_item);
	load_game_menu.build();
	load_game_frame->display();
	selection = "";
	key_stroke = ascii_io::undefined;
	load_game_menu.get_selection(selection, key_stroke);
}

std::string stratego_display::get_screen_shot() {
	return screen_shot;
}

void stratego_display::set_screen_shot(std::string shot) {
	screen_shot = shot;
}

std::string stratego_display::get_player1_name() {
	return player1_name;
}

std::string stratego_display::get_player2_name() {
	return player2_name;
}

void stratego_display::erase_screen_shot()
{
	screen_shot = "";
}

void stratego_display::display_set_controls()
{
	settings_frame->enable_dec(game_controls->get_key("enable line drawing"));

	if (game_controls->get_key("enable color"))
	{
		settings_frame->set_default_background_color(game_controls->get_key("background color"));
		settings_frame->set_default_foreground_color(game_controls->get_key("foreground color"));
	}

	settings_menu.build();
	settings_frame->display();
	std::string selection = "";
	int key_stroke = ascii_io::undefined;
	do
	{
		settings_menu.get_selection(selection, key_stroke);
		settings_menu.build();
		for (unsigned int i = 0; i < control_settings_menu_items.size(); i++)
		{
			if (selection == control_settings_menu_items[i].name_id)
			{
				if (control_settings_menu_items[i].type == regular)
				{
					settings_label.set_output("Press key to bind to " + selection);
					settings_label.refresh();
					int key = ascii_io::getchar();
					game_controls->unbind(control_settings_menu_items[i].name_id);
					game_controls->bind(control_settings_menu_items[i].name_id, key);
					settings_menu.set_item_label(selection, ascii_io::get_key_name(key));
					settings_label.set_output("");
					settings_label.refresh();
				}
				else if(control_settings_menu_items[i].type == color)
				{
					settings_label.set_output("b -> blue, c -> cyan, d -> black, g -> green, m -> magenta, r -> red, w -> white, y -> yellow");
					settings_label.refresh();
					int key = ascii_io::getchar();
					int selected_color = format_tools::none;
					switch (key)
					{
						case ascii_io::b:
							selected_color = format_tools::blue;
							break;
						case ascii_io::c:
							selected_color = format_tools::cyan;
							break;
						case ascii_io::d:
							selected_color = format_tools::black;
							break;
						case ascii_io::g:
							selected_color = format_tools::green;
							break;
						case ascii_io::m:
							selected_color = format_tools::magenta;
							break;
						case ascii_io::r:
							selected_color = format_tools::red;
							break;
						case ascii_io::w:
							selected_color = format_tools::white;
							break;
						case ascii_io::y:
							selected_color = format_tools::yellow;
							break;
					}
					game_controls->unbind(control_settings_menu_items[i].name_id);
					game_controls->bind(control_settings_menu_items[i].name_id, selected_color);
					reset_color(control_settings_menu_items[i].name_id, selected_color);
					settings_menu.set_item_label(selection, format_tools::get_color_name(selected_color));
					settings_label.set_output("");
					settings_label.refresh();
				}
				else if (control_settings_menu_items[i].type == boolean)
				{
					bool value = game_controls->get_key(control_settings_menu_items[i].name_id);
					value = !value;
					game_controls->unbind(control_settings_menu_items[i].name_id);
					game_controls->bind(control_settings_menu_items[i].name_id, value);
					std::string label_name = "";
					if (value == 0)
					{
						label_name = "No";
					}
					else if (value == 1)
					{
						label_name = "Yes";
					}
					settings_menu.set_item_label(selection, label_name);
					main_frame->enable_dec(game_controls->get_key("enable line drawing"));
					multipurpose_frame->enable_dec(game_controls->get_key("enable line drawing"));
					settings_frame->enable_dec(game_controls->get_key("enable line drawing"));
					if (control_settings_menu_items[i].name_id == "bold foreground")
					{
						for (unsigned int j = 0; j < color_group_map.size(); j++)
						{
							reset_color(color_group_map[j].color, game_controls->get_key(color_group_map[j].color));
						}
					}
				}
				settings_menu.build();
				settings_frame->display();
			}
		}
	} while (selection != "");
	stratego_file_managment::save_controls("controls.json", game_controls);

	main_frame->enable_color(game_controls->get_key("enable color"));
	multipurpose_frame->enable_color(game_controls->get_key("enable color"));

	if (game_controls->get_key("enable color"))
	{
		main_frame->set_default_background_color(game_controls->get_key("background color"));
		main_frame->set_default_foreground_color(game_controls->get_key("foreground color"));
		multipurpose_frame->set_default_background_color(game_controls->get_key("background color"));
		multipurpose_frame->set_default_foreground_color(game_controls->get_key("foreground color"));
	}
}
