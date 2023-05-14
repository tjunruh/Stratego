#include "logic.h"

bool stratego_logic::is_valid_curser_position(int row, int column) {
	
	if ((row < 0) || (row >= 10) || (column < 0) || (column >= 10)) {
		return false;
	}
	else if (((row == 4) || (row == 5)) && ((column == 2) || (column == 3) || (column == 6) || (column == 7))) {
		return false;
	}
	else {
		return true;
	}
}

bool stratego_logic::is_valid_piece_position(int row, int column) {
	if ((row < 0) || (row >= 10) || (column < 0) || (column >= 10)) {
		return false;
	}
	else if (((row == 4) || (row == 5)) && ((column == 2) || (column == 3) || (column == 6) || (column == 7))) {
		return false;
	}
	else if (board.players_piece_at_position(row, column, player_turn) && !((row == board.get_piece_data(selected_piece_id).get_row()) && (column == board.get_piece_data(selected_piece_id).get_column()))) {
		return false;
	}
	else {
		return true;
	}
}

bool stratego_logic::is_valid_position_to_place_piece(int row) {
	if ((player_turn == 1) && (row > 5)) {
		return true;
	}
	else if ((player_turn == 2) && (row < 4)){
		return true;
	}
	else {
		return false;
	}
}

bool stratego_logic::path_clear(int start_row, int start_column, direction _direction, int distance) {
	if (((player_turn == 1) && (_direction == up)) || ((player_turn == 2) && (_direction == down)))  {
		for (int row = (start_row - 1); row > (start_row - distance); row--) {
			if (board.players_piece_at_position(row, start_column, 1) || board.players_piece_at_position(row, start_column, 2)) {
				return false;
			}
		}
	}
	else if (((player_turn == 1) && (_direction == down)) || ((player_turn == 2) && (_direction == up))) {
		for (int row = (start_row + 1); row < (start_row + distance); row++) {
			if (board.players_piece_at_position(row, start_column, 1 || board.players_piece_at_position(row, start_column, 2))) {
				return false;
			}
		}
	}
	else if (((player_turn == 1) && (_direction == right)) || ((player_turn == 2) && (_direction == left))) {
		for (int column = (start_column + 1); column < (start_column + distance); column++) {
			if (board.players_piece_at_position(start_row, column, 1) || board.players_piece_at_position(start_row, column, 2)) {
				return false;
			}
		}
	}
	else if (((player_turn == 1) && (_direction == left)) || ((player_turn == 2) && (_direction == right))) {
		for (int column = (start_column - 1); column > (start_column - distance); column--) {
			if (board.players_piece_at_position(start_row, column, 1) || board.players_piece_at_position(start_row, column, 2)) {
				return false;
			}
		}
	}
	else {
		return true;
	}
}

int stratego_logic::determine_loser(int piece1_id, int piece2_id) {
	stratego_piece piece1 = board.get_piece_data(piece1_id);
	stratego_piece piece2 = board.get_piece_data(piece2_id);
	if ((piece1.get_rank() == piece2.get_rank())) {
		if ((player_turn == 1) && (piece1.get_owner() == 1)) {
			return piece2_id;
		}
		else if ((player_turn == 1) && (piece1.get_owner() == 2)) {
			return piece1_id;
		}
		else if ((player_turn == 2) && (piece2.get_owner() == 1)) {
			return piece2_id;
		}
		else if ((player_turn == 2) && (piece2.get_owner() == 2)) {
			return piece1_id;
		}
	}
	else if ((piece1.get_rank() >= 0) && (piece2.get_rank() >= 0)) {
		if (piece1.get_rank() > piece2.get_rank()) {
			return piece2_id;
		}
		else if (piece1.get_rank() < piece2.get_rank()) {
			return piece1_id;
		}
	}
	else if ((piece1.get_rank() == 2) && (piece2.get_rank() == -2)) {
		return piece2_id;
	}
	else if ((piece1.get_rank() == -2) && (piece2.get_rank() == 2)) {
		return piece1_id;
	}
	else if (piece1.get_rank() == -1) {
		if (piece2.get_rank() == board.get_best_rank(piece2.get_owner())) {
			return piece2_id;
		}
		else {
			return piece1_id;
		}
	}
	else if (piece2.get_rank() == -1) {
		if (piece1.get_rank() == board.get_best_rank(piece1.get_owner())) {
			return piece1_id;
		}
		else {
			return piece2_id;
		}
	}
}

void stratego_logic::move_curser(input user_input) {
	int temp_curser_row = curser_row;
	int temp_curser_column = curser_column;
	if (((player_turn == 1) && (user_input == _up)) || ((player_turn == 2) && (user_input == _down))) {
		temp_curser_row--;
	}
	else if (((player_turn == 1) && (user_input == _down)) || ((player_turn == 2) && (user_input == _up))) {
		temp_curser_row++;
	}
	else if (((player_turn == 1) && (user_input == _right)) || ((player_turn == 2) && (user_input == _left))) {
		temp_curser_column++;
	}
	else if (((player_turn == 1) && (user_input == _left)) || ((player_turn == 2) && (user_input == _right))) {
		temp_curser_column--;
	}
	
	if (is_valid_curser_position(temp_curser_row, temp_curser_column)) {
		curser_row = temp_curser_row;
		curser_column = temp_curser_column;
	}
}

void stratego_logic::set_game_state(game_state _game_state) {
	state_of_game = _game_state;
}

game_state stratego_logic::get_game_state() {
	return state_of_game;
}

void stratego_logic::select_piece(int row, int column) {
	int temp_selected_piece_id = board.get_id_with_location(row, column);
	if (temp_selected_piece_id >= 0) {
		stratego_piece selected_piece = board.get_piece_data(temp_selected_piece_id);
		if ((selected_piece.get_rank() != 0) && (selected_piece.get_rank() != -2) && (selected_piece.get_owner() == player_turn)) {
			selected_piece_id = temp_selected_piece_id;
			if (selected_piece.get_rank() == 1) {
				set_game_state(scout_selected);
				set_direction(neutral);
			}
			else {
				set_game_state(piece_selected);
				set_direction(neutral);
			}
		}
	}
}

void stratego_logic::unselect_piece() {
	selected_piece_id = -1;
	set_game_state(moving_curser);
}

void stratego_logic::adjust_scout_position(input user_input) {
	int temp_row = 0;
	int temp_column = 0;
	stratego_piece selected_piece = board.get_piece_data(selected_piece_id);

	if (get_direction() == neutral) {
		temp_row = selected_piece.get_row();
		temp_column = selected_piece.get_column();
	}
	else {
		temp_row = new_row;
		temp_column = new_column;
	}
	
	if((player_turn == 1) && (user_input == _up) && ((get_direction() == up) || (get_direction() == neutral) || (get_direction() == down)))  {
		temp_row--;
	}
	else if ((player_turn == 1) && (user_input == _down) && ((get_direction() == down) || (get_direction() == neutral) || (get_direction() == up))) {
		temp_row++;
	}
	else if ((player_turn == 1) && (user_input == _right) && ((get_direction() == right) || (get_direction() == neutral) || (get_direction() == left))) {
		temp_column++;
	}
	else if ((player_turn == 1) && (user_input == _left) && ((get_direction() == left) || (get_direction() == neutral) || (get_direction() == right))) {
		temp_column--;
	}
	else if ((player_turn == 2) && (user_input == _up) && ((get_direction() == up) || (get_direction() == neutral) || (get_direction() == down))) {
		temp_row++;
	}
	else if ((player_turn == 2) && (user_input == _down) && ((get_direction() == down) || (get_direction() == neutral) || (get_direction() == up))) {
		temp_row--;
	}
	else if ((player_turn == 2) && (user_input == _right) && ((get_direction() == right) || (get_direction() == neutral) || (get_direction() == left))) {
		temp_column--;
	}
	else if ((player_turn == 2) && (user_input == _left) && ((get_direction() == left) || (get_direction() == neutral) || (get_direction() == right))) {
		temp_column++;
	}
	int temp_distance = 0;
	if (temp_column != selected_piece.get_column()) {
		temp_distance = selected_piece.get_column() - temp_column;
		if (temp_distance < 0) {
			temp_distance = temp_distance * -1;
		}
	}
	else if (temp_row != selected_piece.get_row()) {
		temp_distance = selected_piece.get_row() - temp_row;
		if (temp_distance < 0) {
			temp_distance = temp_distance * -1;
		}
	}

	if (is_valid_piece_position(temp_row, temp_column) && path_clear(selected_piece.get_row(), selected_piece.get_column(), get_direction(), temp_distance)) {
		_distance = temp_distance;
		new_row = temp_row;
		new_column = temp_column;
		set_direction(selected_piece.get_row(), selected_piece.get_column(), new_row, new_column);
	}
}

direction stratego_logic::get_direction() {
	return _direction;
}

void stratego_logic::set_direction(direction piece_direction) {
	_direction = piece_direction;
}

void stratego_logic::set_direction(int start_row, int start_column, int stop_row, int stop_column) {
	if (player_turn == 1) {
		if (start_row > stop_row) {
			_direction = up;
		}
		else if (start_row < stop_row) {
			_direction = down;
		}
		else if (start_column < stop_column) {
			_direction = right;
		}
		else if (start_column > stop_column) {
			_direction = left;
		}
		else {
			_direction = neutral;
		}
	}
	else if (player_turn == 2) {
		if (start_row > stop_row) {
			_direction = down;
		}
		else if (start_row < stop_row) {
			_direction = up;
		}
		else if (start_column < stop_column) {
			_direction = left;
		}
		else if (start_column > stop_column) {
			_direction = right;
		}
		else {
			_direction = neutral;
		}
	}
}

void stratego_logic::adjust_piece_position(input user_input) {
	if ((user_input == _up) || (user_input == _down) || (user_input == _right) || (user_input == _left)) {
		stratego_piece selected_piece = board.get_piece_data(selected_piece_id);

		int temp_row = selected_piece.get_row();
		int temp_column = selected_piece.get_column();

		if ((player_turn == 1) && (user_input == _up)) {
			temp_row--;
		}
		else if ((player_turn == 1) && (user_input == _down)) {
			temp_row++;
		}
		else if ((player_turn == 1) && (user_input == _right)) {
			temp_column++;
		}
		else if ((player_turn == 1) && (user_input == _left)) {
			temp_column--;
		}
		else if ((player_turn == 2) && (user_input == _up)) {
			temp_row++;
		}
		else if ((player_turn == 2) && (user_input == _down)) {
			temp_row--;
		}
		else if ((player_turn == 2) && (user_input == _right)) {
			temp_column--;
		}
		else if ((player_turn == 2) && (user_input == _left)) {
			temp_column++;
		}

		if (is_valid_piece_position(temp_row, temp_column)) {
			new_row = temp_row;
			new_column = temp_column;
			set_direction(selected_piece.get_row(), selected_piece.get_column(), new_row, new_column);
		}
	}
}

void stratego_logic::move_piece(input user_input) { 
	_battle = false;
	if ((user_input == enter) && (get_direction() != neutral)) {
		int other_player = -1;
		if (player_turn == 1) {
			other_player = 2;
		}
		else if (player_turn == 2) {
			other_player = 1;
		}

		if (board.players_piece_at_position(new_row, new_column, other_player)) {
			int defending_piece_id = board.get_id_with_location(new_row, new_column);
			defending_piece = board.get_piece_data(defending_piece_id);
			loser_id = determine_loser(selected_piece_id, defending_piece_id);
			losing_piece = board.get_piece_data(loser_id);
			_battle = true;
			set_game_state(battling);
		}
		else {
			board.change_piece_position(selected_piece_id, new_row, new_column);
			set_game_state(move_made);
			selected_piece_id = -1;
			_direction = neutral;
		}
		
	}
}

void stratego_logic::end_turn() {
	if (get_game_state() == turn_ended) {
		if (player_turn == 1) {
			player_turn == 2;
		}
		else if (player_turn == 2) {
			player_turn == 1;
		}
	}
}

void stratego_logic::reset_board() {
	board.initialize_player1_pieces();
	board.initialize_player2_pieces();
}

bool stratego_logic::player1_pieces_placed() {
	return board.player_pieces_placed(1);
}

bool stratego_logic::player2_pieces_placed() {
	return board.player_pieces_placed(2);
}

int stratego_logic::get_curser_row() {
	return curser_row;
}

int stratego_logic::get_curser_column() {
	return curser_column;
}

void stratego_logic::set_curser_row(int row) {
	if ((row >= 0) && (row < 10)) {
		curser_row = row;
	}
}

void stratego_logic::set_curser_column(int column) {
	if ((column >= 0) && (column < 10)) {
		curser_column = column;
	}
}

void stratego_logic::get_board_info(stratego_piece(&board_info)[80]) {
	for (int piece = 0; piece < 80; piece++) {
		board_info[piece] = board.get_piece_data(piece);
	}
}

void stratego_logic::place_piece(input user_input) {
	if (is_valid_position_to_place_piece(curser_row)) {
		if (user_input == one) {
			board.add_piece(9, player_turn, curser_row, curser_column);
		}
		else if (user_input == two) {
			board.add_piece(8, player_turn, curser_row, curser_column);
		}
		else if (user_input == three) {
			board.add_piece(7, player_turn, curser_row, curser_column);
		}
		else if (user_input == four) {
			board.add_piece(6, player_turn, curser_row, curser_column);
		}
		else if (user_input == five) {
			board.add_piece(5, player_turn, curser_row, curser_column);
		}
		else if (user_input == six) {
			board.add_piece(4, player_turn, curser_row, curser_column);
		}
		else if (user_input == seven) {
			board.add_piece(3, player_turn, curser_row, curser_column);
		}
		else if (user_input == eight) {
			board.add_piece(2, player_turn, curser_row, curser_column);
		}
		else if (user_input == nine) {
			board.add_piece(1, player_turn, curser_row, curser_column);
		}
		else if (user_input == b) {
			board.add_piece(-2, player_turn, curser_row, curser_column);
		}
		else if (user_input == s) {
			board.add_piece(-1, player_turn, curser_row, curser_column);
		}
		else if (user_input == f) {
			board.add_piece(0, player_turn, curser_row, curser_column);
		}
	}
}

void stratego_logic::set_turn(int turn) {
	player_turn = turn;
}

bool stratego_logic::player1_won() {
	return board.player_flag_out_of_play(2);
}

bool stratego_logic::player2_won() {
	return board.player_flag_out_of_play(1);
}

int stratego_logic::get_distance() {
	return _distance;
}

int stratego_logic::get_turn() {
	return player_turn;
}

int stratego_logic::get_selected_piece_row() {
	return board.get_piece_data(selected_piece_id).get_row();
}

int stratego_logic::get_selected_piece_column() {
	return board.get_piece_data(selected_piece_id).get_column();
}

bool stratego_logic::battle() {
	return _battle;
}

stratego_piece stratego_logic::get_defending_piece_data() {
	return defending_piece;
}

void stratego_logic::finalize_move() {
	if (_battle) {
		board.remove_piece(loser_id);
		if (selected_piece_id != loser_id) {
			board.change_piece_position(selected_piece_id, new_row, new_column);
			set_game_state(move_made);
			selected_piece_id = -1;
			_direction = neutral;
			losing_piece.set_inPlay(false);
		}
	}
}

stratego_piece stratego_logic::get_losing_piece_data() {
	return losing_piece;
}

void stratego_logic::set_board_info(stratego_piece board_info[80]) {
	board.set_pieces(board_info);
}