#include "display.h"
#include "ascii_io.h"
#include "frame.h"
#include "ascii_board.h"
#include "label.h"
#include <string>
#include "menu.h"

stratego_display::stratego_display(frame* main_display, frame* multipurpose_display) :
board_heading(main_display),
board(main_display, "board_configs/stratego_board.txt", "default", "new line"),
pieces_out_label(main_display, "new line"),
multipurpose_label(multipurpose_display),
left_text_box_spacer(multipurpose_display, 1, "new line"),
multipurpose_text_box(multipurpose_display, "none", 3),
right_text_box_spacer(multipurpose_display, 1)
{
	main_frame = main_display;
	board_heading.set_alignment("center");
	board.set_alignment("center block");
	pieces_out_label.set_alignment("center block");
	board.load_board_translation("reverse", "board_configs/stratego_reverse_board.txt");
	board.add_configuration("hide", -1, -1, "*X*", '*');
	board.add_configuration("0", -1, -1, "*f*", '*');
	board.add_configuration("-1", -1, -1, "*s*", '*');
	board.add_configuration("-2", -1, -1, "*b*", '*');
	board.add_configuration("1", -1, -1, "*1*", '*');
	board.add_configuration("2", -1, -1, "*2*", '*');
	board.add_configuration("3", -1, -1, "*3*", '*');
	board.add_configuration("4", -1, -1, "*4*", '*');
	board.add_configuration("5", -1, -1, "*5*", '*');
	board.add_configuration("6", -1, -1, "*6*", '*');
	board.add_configuration("7", -1, -1, "*7*", '*');
	board.add_configuration("8", -1, -1, "*8*", '*');
	board.add_configuration("9", -1, -1, "*9*", '*');
	board.add_configuration("cursor", -1, -1, "(*)", '*');
	board.add_configuration("up_cursor", -1, -1, "^*^", '*');
	board.add_configuration("down_cursor", -1, -1, "v*v", '*');
	board.add_configuration("left_cursor", -1, -1, "<*<", '*');
	board.add_configuration("right_cursor", -1, -1, ">*>", '*');
	board.add_configuration("scout_up", -1, -1, "*^*", '*');
	board.add_configuration("scout_down", -1, -1, "*v*", '*');
	board.add_configuration("scout_left", -1, -1, "*<*", '*');
	board.add_configuration("scout_right", -1, -1, "*>*", '*');

	multipurpose_frame = multipurpose_display;
	multipurpose_frame->set_coordinate_width_multiplier(1, 0, 1);
	multipurpose_frame->set_coordinate_width_multiplier(1, 1, 1);
	multipurpose_label.set_alignment("center block");
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

	board.sync();

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
	multipurpose_frame->display();
	do
	{
		input = multipurpose_text_box.write();
	} while (input != ascii_io::enter);
	player1_name = multipurpose_text_box.get_text();
	ascii_io::hide_cursor();
	multipurpose_text_box.clear();
}

void stratego_display::display_get_player2_name()
{
	int input = ascii_io::undefined;
	multipurpose_label.set_output("Enter your name player 2");
	multipurpose_label.set_spacing(15, 0, 0, 0);
	multipurpose_frame->display();
	do
	{
		input = multipurpose_text_box.write();
	} while (input != ascii_io::enter);
	player2_name = multipurpose_text_box.get_text();
	ascii_io::hide_cursor();
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
	if (_players_move == 1) {
		execute_show_player2();
		execute_hide_player1();
		invert_arrows();
		if ((_losing_piece.get_owner() == 1) && _losing_piece.get_inPlay()) {
			reveal_piece(_losing_piece.get_row(), _losing_piece.get_column());
			execute_reveal_piece();
		}
		board.use_translation("reverse");
		screen_shot = board.get_board();
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
		screen_shot = board.get_board();
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
	output = output + screen_shot;
	multipurpose_label.set_output(output);
	multipurpose_label.set_spacing(0, 0, 0, 0);
	multipurpose_frame->display();
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

std::string stratego_display::display_load_game_menu(std::vector<std::string> saved_game_names) {
	int x = 0;
	int y = 0;
	ascii_io::get_terminal_size(x, y);
	bool reduced_menu_size = false;
	if ((y - 4) > 10)
	{
		y = y - 5;
		reduced_menu_size = true;
	}
	else if((y - 1) > 0)
	{
		y = y - 1;
	}
	frame* menu_frame = new frame();
	label saved_games_label(menu_frame);
	menu saved_games_menu(menu_frame, "new line", y);
	saved_games_label.set_alignment("center");
	saved_games_label.set_output("Saved Games");
	saved_games_menu.set_alignment("center");
	saved_games_menu.add_border();
	saved_games_menu.enable_quit();
	if (reduced_menu_size)
	{
		saved_games_label.set_spacing(2, 0, 0, 0);
	}
	for (unsigned int i = 0; i < saved_game_names.size(); i++)
	{
		saved_games_menu.append_item(saved_game_names[i]);
	}
	saved_games_menu.sync();
	menu_frame->display();
	std::string selection = saved_games_menu.get_selection();
	return selection;
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
