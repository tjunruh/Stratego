#include "display.h"
#include <string>

void stratego_display::add_move_up_curser(int curser_row, int curser_column) {
	curser_character_L = '^';
	curser_character_R = '^';
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_move_down_curser(int curser_row, int curser_column) {
	curser_character_L = 'v';
	curser_character_R = 'v';
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_move_right_curser(int curser_row, int curser_column) {
	curser_character_L = '>';
	curser_character_R = '>';
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_move_left_curser(int curser_row, int curser_column) {
	curser_character_L = '<';
	curser_character_R = '<';
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
}

void stratego_display::add_standard_curser(int curser_row, int curser_column) {
	curser_character_L = '(';
	curser_character_R = ')';
	_curser_row = curser_row;
	_curser_column = curser_column;
	add_curser = true;
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
		if (_board_pieces[piece].get_owner() == 1) {
			_board_pieces[piece].set_piece('X');
		}
	}
}

void stratego_display::execute_hide_player2() {
	for (int piece = 0; piece < 80; piece++) {
		if (_board_pieces[piece].get_owner() == 2) {
			_board_pieces[piece].set_piece('X');
		}
	}
}

void stratego_display::execute_reveal_piece() {
	for (int piece = 0; piece < 80; piece++) {
		if ((_board_pieces[piece].get_row() == _reveal_piece_row) && (_board_pieces[piece].get_column() == _reveal_piece_column))
			_board_pieces[piece].set_owner(0);
	}
}

void stratego_display::add_terrain() {
	board_spaces[4][2] = "|||";
	board_spaces[5][2] = "|||";
	board_spaces[4][3] = "|||";
	board_spaces[5][3] = "|||";
	board_spaces[4][6] = "|||";
	board_spaces[5][6] = "|||";
	board_spaces[4][7] = "|||";
	board_spaces[5][7] = "|||";
}

void stratego_display::execute_add_curser() {
	(board_spaces[_curser_row][_curser_column])[0] = curser_character_L;
	(board_spaces[_curser_row][_curser_column])[2] = curser_character_R;
}

void stratego_display::determine_pieces_out_of_play(int(&player1_pieces_out)[12], int(&player2_pieces_out)[12]) {
	for (int player = 1; player < 3; player++) {
		int present_pieces[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		for (int piece = 0; piece < 80; piece++) {
			if ((_board_pieces[piece].get_owner() == player) && (!_board_pieces[piece].get_inPlay())) {
				int current_piece = _board_pieces[piece].get_rank();
				if (current_piece == 1) {
					present_pieces[9]++;
				}
				else if (current_piece == 2) {
					present_pieces[8]++;
				}
				else if (current_piece == 3) {
					present_pieces[7]++;
				}
				else if (current_piece == 4) {
					present_pieces[6]++;
				}
				else if (current_piece == 5) {
					present_pieces[5]++;
				}
				else if (current_piece == 6) {
					present_pieces[4]++;
				}
				else if (current_piece == 7) {
					present_pieces[3]++;
				}
				else if (current_piece == 8) {
					present_pieces[2]++;
				}
				else if (current_piece == 9) {
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
	player1_disp = player1_disp + "    \n";
	player2_disp = player2_disp + "    \n";
	io.print(player1_disp);
	io.print(player2_disp);
}

void stratego_display::add_board_pieces_to_spaces() {
	for (int row = 0; row < 10; row++) {
		for (int column = 0; column < 10; column++) {
			board_spaces[row][column] = "   ";
		}
	}
	add_terrain();
	for (int piece = 0; piece < 80; piece++) {
		if (_board_pieces[piece].get_inPlay()) {
			(board_spaces[_board_pieces[piece].get_row()][_board_pieces[piece].get_column()])[1] = _board_pieces[piece].get_piece();
		}
	}
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
				(board_spaces[moving_coordinate][scout_start_column])[1] = '^';
			}
		}
		else if (_player_for_scout_arrows == 2) {
			for (moving_coordinate = scout_start_row + 1; moving_coordinate < (scout_start_row + scout_distance); moving_coordinate++) {
				(board_spaces[moving_coordinate][scout_start_column])[1] = '^';
			}
		}
	}
	else if (scout_direction == down) {
		if (_player_for_scout_arrows == 1) {
			for (moving_coordinate = scout_start_row + 1; moving_coordinate < (scout_start_row + scout_distance); moving_coordinate++) {
				(board_spaces[moving_coordinate][scout_start_column])[1] = 'v';
			}
		}
		else if (_player_for_scout_arrows == 2) {
			for (moving_coordinate = scout_start_row - 1; moving_coordinate > (scout_start_row - scout_distance); moving_coordinate--) {
				(board_spaces[moving_coordinate][scout_start_column])[1] = 'v';
			}
		}
	}
	else if (scout_direction == right) {
		if (_player_for_scout_arrows == 1) {
			for (moving_coordinate = scout_start_column + 1; moving_coordinate < (scout_start_column + scout_distance); moving_coordinate++) {
				(board_spaces[scout_start_row][moving_coordinate])[1] = '>';
			}
		}
		else if (_player_for_scout_arrows == 2) {
			for (moving_coordinate = scout_start_column - 1; moving_coordinate > (scout_start_column - scout_distance); moving_coordinate--) {
				(board_spaces[scout_start_row][moving_coordinate])[1] = '>';
			}
		}
	}
	else if (scout_direction == left) {
		if (_player_for_scout_arrows == 1) {
			for (moving_coordinate = scout_start_column - 1; moving_coordinate > (scout_start_column - scout_distance); moving_coordinate--) {
				(board_spaces[scout_start_row][moving_coordinate])[1] = '<';
			}
		}
		else if (_player_for_scout_arrows == 2) {
			for (moving_coordinate = scout_start_column + 1; moving_coordinate < (scout_start_column + scout_distance); moving_coordinate++) {
				(board_spaces[scout_start_row][moving_coordinate])[1] = '<';
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
	_add_hint = false;
}

void stratego_display::display_board(stratego_piece board_pieces[80]) {
	printable_board = "";
	for (int i = 0; i < 80; i++) {
		_board_pieces[i] = board_pieces[i];
	}

	if (_reveal_piece) {
		execute_reveal_piece();
	}

	if (_hide_player1) {
		execute_hide_player1();
	}

	if (_hide_player2) {
		execute_hide_player2();
	}

	add_board_pieces_to_spaces();

	if (add_curser) {
		execute_add_curser();
	}

	if (_add_scout_arrows) {
		execute_add_scout_arrows();
	}

	if (_player_for_orientation == 1) {
		for (int row = 0; row < 10; row++) {
			printable_board  = printable_board + ".---.---.---.---.---.---.---.---.---.---.\n";
			for (int column = 0; column < 10; column++) {
				printable_board = printable_board + "|" + board_spaces[row][column];
			}
			printable_board = printable_board + "|\n";
		}
		printable_board = printable_board + ".---.---.---.---.---.---.---.---.---.---.\n";
	}
	else if (_player_for_orientation == 2) {
		for (int row = 9; row >= 0; row--) {
			printable_board = printable_board + ".---.---.---.---.---.---.---.---.---.---.\n";
			for (int column = 9; column >= 0; column--) {
				printable_board = printable_board + "|" + board_spaces[row][column];
			}
			printable_board = printable_board + "|\n";
		}
		printable_board = printable_board + ".---.---.---.---.---.---.---.---.---.---.\n";
	}

	io.print(printable_board);

	if (_display_pieces_out_of_play) {
		int player1_pieces_out[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int player2_pieces_out[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		determine_pieces_out_of_play(player1_pieces_out, player2_pieces_out);
		display_pieces_out_of_play(player1_pieces_out, player2_pieces_out);
	}

	if (_add_hint) {
		execute_add_hint();
	}

	if (_save_move) {
		execute_save_move();
	}
	
	reset();
}


void stratego_display::set_menu_selection(menu_options menu_selection) {
	_menu_selection = menu_selection;
}

void stratego_display::display_menu() {
	display_logo();
	if (get_menu_selection() == new_game) {
		std::string display = "                                                          ";
		display = display + "* New Game\n";
		display = display + "                                                          ";
		display = display + "  Load Game \n";
		display = display + "                                                          ";
		display = display + "  exit \n";
		io.print(display);
	}
	else if (get_menu_selection() == load_game) {
		std::string display = "                                                          ";
		display = display + "  New Game\n";
		display = display + "                                                          ";
		display = display + "* Load Game \n";
		display = display + "                                                          ";
		display = display + "  exit \n";
		io.print(display);
	}
	else if (get_menu_selection() == exit_game) {
		std::string display = "                                                          ";
		display = display + "  New Game\n";
		display = display + "                                                          ";
		display = display + "  Load Game \n";
		display = display + "                                                          ";
		display = display + "* exit \n";
		io.print(display);
	}
}

void stratego_display::display_player1_preturn_menu() {
	io.print(player1_name + "'s turn. Press space to begin.");
}

void stratego_display::display_player2_preturn_menu() {
	io.print(player2_name + "'s turn. Press space to begin.");
}

menu_options stratego_display::get_menu_selection() {
	return _menu_selection;
}

void stratego_display::display_rules() {

}

void stratego_display::display_controls() {
	io.print("Go back   : q\n\n");
	io.print("MOVING CURSER\n");
	io.print("Operation : Button\n");
	io.print("Move up   : Up arrow\n");
	io.print("Move down : Down arrow\n");
	io.print("Move right: Right arrow\n");
	io.print("Move left : Left arrow\n");
	io.print("\n");
	io.print("GAME SETUP\n");
	io.print("Operation : Button\n");
	io.print("Place 1   : 1\n");
	io.print("Place 2   : 2\n");
	io.print("Place 3   : 3\n");
	io.print("Place 4   : 4\n");
	io.print("Place 5   : 5\n");
	io.print("Place 6   : 6\n");
	io.print("Place 7   : 7\n");
	io.print("Place 8   : 8\n");
	io.print("Place 9   : 9\n");
	io.print("Place s   : s\n");
	io.print("Place b   : b\n");
	io.print("Place f   : f\n");
	io.print("If you want to remove a piece from the board, place another piece on top of it.\nThis will replace the piece on the board with the new piece.\n");
	io.print("\n");
	io.print("GAME PLAY PIECE MANIPULATION\n");
	io.print("Operation : Button\n");
	io.print("Select    : Enter\n");
	io.print("Unselect  : q\n");
	io.print("Move up   : Up arrow\n");
	io.print("Move down : Down arrow\n");
	io.print("Move right: Right arrow\n");
	io.print("Move left : Left arrow\n");
	io.print("Finalize  : Enter\n");
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
		if ((_losing_piece.get_owner() == 1) && _losing_piece.get_inPlay()) {
			reveal_piece(_losing_piece.get_row(), _losing_piece.get_column());
			execute_reveal_piece();
		}
		execute_show_player2();
		execute_hide_player1();
		invert_arrows();

		for (int piece = 0; piece < 80; piece++) {
			if (_board_pieces[piece].get_inPlay()) {
				(board_spaces[_board_pieces[piece].get_row()][_board_pieces[piece].get_column()])[1] = _board_pieces[piece].get_piece();
			}
		}

		for (int row = 9; row >= 0; row--) {
			screen_shot = screen_shot + ".---.---.---.---.---.---.---.---.---.---.\n";
			for (int column = 9; column >= 0; column--) {
				screen_shot = screen_shot + "|" + board_spaces[row][column];
			}
			screen_shot = screen_shot + "|\n";
		}
		screen_shot = screen_shot + ".---.---.---.---.---.---.---.---.---.---.\n";
	}
	else if (_players_move == 2) {
		if ((_losing_piece.get_owner() == 2) && _losing_piece.get_inPlay()) {
			reveal_piece(_losing_piece.get_row(), _losing_piece.get_column());
			execute_reveal_piece();
		}
		execute_show_player1();
		execute_hide_player2();
		invert_arrows();

		for (int piece = 0; piece < 80; piece++) {
			if (_board_pieces[piece].get_inPlay()) {
				(board_spaces[_board_pieces[piece].get_row()][_board_pieces[piece].get_column()])[1] = _board_pieces[piece].get_piece();
			}
		}

		for (int row = 0; row < 10; row++) {
			screen_shot = screen_shot + ".---.---.---.---.---.---.---.---.---.---.\n";
			for (int column = 0; column < 10; column++) {
				screen_shot = screen_shot + "|" + board_spaces[row][column];
			}
			screen_shot = screen_shot + "|\n";
		}
		screen_shot = screen_shot + ".---.---.---.---.---.---.---.---.---.---.\n";
	}
}

void stratego_display::execute_show_player1() {
	for (int piece = 0; piece < 80; piece++) {
		if (_board_pieces[piece].get_owner() == 1) {
			if (_board_pieces[piece].get_rank() == -2) {
				_board_pieces[piece].set_piece('b');
			}
			else if (_board_pieces[piece].get_rank() == -1) {
				_board_pieces[piece].set_piece('s');
			}
			else if (_board_pieces[piece].get_rank() == 0) {
				_board_pieces[piece].set_piece('f');
			}
			else if (_board_pieces[piece].get_rank() == 1) {
				_board_pieces[piece].set_piece('9');
			}
			else if (_board_pieces[piece].get_rank() == 2) {
				_board_pieces[piece].set_piece('8');
			}
			else if (_board_pieces[piece].get_rank() == 3) {
				_board_pieces[piece].set_piece('7');
			}
			else if (_board_pieces[piece].get_rank() == 4) {
				_board_pieces[piece].set_piece('6');
			}
			else if (_board_pieces[piece].get_rank() == 5) {
				_board_pieces[piece].set_piece('5');
			}
			else if (_board_pieces[piece].get_rank() == 6) {
				_board_pieces[piece].set_piece('4');
			}
			else if (_board_pieces[piece].get_rank() == 7) {
				_board_pieces[piece].set_piece('3');
			}
			else if (_board_pieces[piece].get_rank() == 8) {
				_board_pieces[piece].set_piece('2');
			}
			else if (_board_pieces[piece].get_rank() == 9) {
				_board_pieces[piece].set_piece('1');
			}
		}
	}
}

void stratego_display::execute_show_player2() {
	for (int piece = 0; piece < 80; piece++) {
		if (_board_pieces[piece].get_owner() == 2) {
			if (_board_pieces[piece].get_rank() == -2) {
				_board_pieces[piece].set_piece('b');
			}
			else if (_board_pieces[piece].get_rank() == -1) {
				_board_pieces[piece].set_piece('s');
			}
			else if (_board_pieces[piece].get_rank() == 0) {
				_board_pieces[piece].set_piece('f');
			}
			else if (_board_pieces[piece].get_rank() == 1) {
				_board_pieces[piece].set_piece('9');
			}
			else if (_board_pieces[piece].get_rank() == 2) {
				_board_pieces[piece].set_piece('8');
			}
			else if (_board_pieces[piece].get_rank() == 3) {
				_board_pieces[piece].set_piece('7');
			}
			else if (_board_pieces[piece].get_rank() == 4) {
				_board_pieces[piece].set_piece('6');
			}
			else if (_board_pieces[piece].get_rank() == 5) {
				_board_pieces[piece].set_piece('5');
			}
			else if (_board_pieces[piece].get_rank() == 6) {
				_board_pieces[piece].set_piece('4');
			}
			else if (_board_pieces[piece].get_rank() == 7) {
				_board_pieces[piece].set_piece('3');
			}
			else if (_board_pieces[piece].get_rank() == 8) {
				_board_pieces[piece].set_piece('2');
			}
			else if (_board_pieces[piece].get_rank() == 9) {
				_board_pieces[piece].set_piece('1');
			}
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

void stratego_display::display_saved_move() {
	io.print(screen_shot);
}

void stratego_display::invert_arrows() {
	if (add_curser) {
		if ((curser_character_L == '^') && (curser_character_R == '^')) {
			curser_character_L = 'v';
			curser_character_R = 'v';
		}
		else if ((curser_character_L == 'v') && (curser_character_R == 'v')) {
			curser_character_L = '^';
			curser_character_R = '^';
		}
		else if ((curser_character_L == '>') && (curser_character_R == '>')) {
			curser_character_L = '<';
			curser_character_R = '<';
		}
		else if ((curser_character_L == '<') && (curser_character_R == '<')) {
			curser_character_L = '>';
			curser_character_R = '>';
		}
		execute_add_curser();
	}
	
	if (_add_scout_arrows) {
		if (_player_for_scout_arrows == 1) {
			_player_for_scout_arrows = 2;
		}
		else if (_player_for_scout_arrows == 2) {
			_player_for_scout_arrows = 1;
		}

		if (scout_direction == up) {
			scout_direction = down;
		}
		else if (scout_direction == down) {
			scout_direction = up;
		}
		else if (scout_direction == right) {
			scout_direction = left;
		}
		else if (scout_direction == left) {
			scout_direction = right;
		}
		execute_add_scout_arrows();
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

void stratego_display::display_load_game_menu(std::vector<std::string> saved_game_names, int selected_game) {
	std::string saved_game_list = "";
	for (int saved_game = 0; saved_game < saved_game_names.size(); saved_game++) {
		if (saved_game == selected_game) {
			saved_game_list = saved_game_list + "* " + saved_game_names[saved_game] + "\n";
		}
		else {
			saved_game_list = saved_game_list + "  " + saved_game_names[saved_game] + "\n";
		}
	}
	io.print(saved_game_list);
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

void stratego_display::display_logo() {
	io.print(R"(_____/\\\\\\\\\\\______________________________________________________________________________________________________)"
	        "\n"
	        R"( ___/\\\/////////\\\____________________________________________________________________________________________________  )"
	        "\n"
	        R"(  __\//\\\______\///______/\\\_______________________________________/\\\_______________________/\\\\\\\\________________)"
	        "\n"
	        R"(   ___\////\\\__________/\\\\\\\\\\\__/\\/\\\\\\\___/\\\\\\\\\_____/\\\\\\\\\\\_____/\\\\\\\\___/\\\////\\\_____/\\\\\____)"
	        "\n"
	        R"(    ______\////\\\______\////\\\////__\/\\\/////\\\_\////////\\\___\////\\\////____/\\\/////\\\_\//\\\\\\\\\___/\\\///\\\__)"
	        "\n"
	        R"(     _________\////\\\______\/\\\______\/\\\___\///____/\\\\\\\\\\_____\/\\\_______/\\\\\\\\\\\___\///////\\\__/\\\__\//\\\_)"
	        "\n"
	        R"(      __/\\\______\//\\\_____\/\\\_/\\__\/\\\__________/\\\/////\\\_____\/\\\_/\\__\//\\///////____/\\_____\\\_\//\\\__/\\\__)"
	        "\n"
	        R"(       _\///\\\\\\\\\\\/______\//\\\\\___\/\\\_________\//\\\\\\\\/\\____\//\\\\\____\//\\\\\\\\\\_\//\\\\\\\\___\///\\\\\/___)"
	        "\n"
	        R"(        ___\///////////_________\/////____\///___________\////////\//______\/////______\//////////___\////////______\/////_____)"
	        "\n\n\n");
}

void stratego_display::add_hint() {
	_add_hint = true;
}

void stratego_display::execute_add_hint() {
	stratego_io io;
	io.print("Press Enter.\n");
}