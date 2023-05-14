#include "pieces.h"

void stratego_pieces::initialize_player1_pieces() {
	for (int piece = 0; piece < 40; piece++) {
		board[piece].set_row(-1);
		board[piece].set_column(-1);
		board[piece].set_owner(1);
		board[piece].set_inPlay(false);
		if (piece < 1) {
			board[piece].set_rank(9);
			board[piece].set_piece(get_symbol(9));

		}
		else if (piece < 2) {
			board[piece].set_rank(8);
			board[piece].set_piece(get_symbol(8));
		}
		else if (piece < 4) {
			board[piece].set_rank(7);
			board[piece].set_piece(get_symbol(7));
		}
		else if (piece < 7) {
			board[piece].set_rank(6);
			board[piece].set_piece(get_symbol(6));
		}
		else if (piece < 11) {
			board[piece].set_rank(5);
			board[piece].set_piece(get_symbol(5));
		}
		else if (piece < 15) {
			board[piece].set_rank(4);
			board[piece].set_piece(get_symbol(4));
		}
		else if (piece < 19) {
			board[piece].set_rank(3);
			board[piece].set_piece(get_symbol(3));
		}
		else if (piece < 24) {
			board[piece].set_rank(2);
			board[piece].set_piece(get_symbol(2));
		}
		else if (piece < 32) {
			board[piece].set_rank(1);
			board[piece].set_piece(get_symbol(1));
		}
		else if (piece < 33) {
			board[piece].set_rank(-1);
			board[piece].set_piece(get_symbol(-1));
		}
		else if (piece < 39) {
			board[piece].set_rank(-2);
			board[piece].set_piece(get_symbol(-2));
		}
		else if (piece == 39) {
			board[piece].set_rank(0);
			board[piece].set_piece(get_symbol(0));
		}
	}
}

void stratego_pieces::initialize_player2_pieces() {
	for (int piece = 40; piece < 80; piece++) {
		board[piece].set_row(-1);
		board[piece].set_column(-1);
		board[piece].set_owner(2);
		board[piece].set_inPlay(false);
		if (piece < 41) {
			board[piece].set_rank(9);
			board[piece].set_piece(get_symbol(9));
		}
		else if (piece < 42) {
			board[piece].set_rank(8);
			board[piece].set_piece(get_symbol(8));
		}
		else if (piece < 44) {
			board[piece].set_rank(7);
			board[piece].set_piece(get_symbol(7));
		}
		else if (piece < 47) {
			board[piece].set_rank(6);
			board[piece].set_piece(get_symbol(6));
		}
		else if (piece < 51) {
			board[piece].set_rank(5);
			board[piece].set_piece(get_symbol(5));
		}
		else if (piece < 55) {
			board[piece].set_rank(4);
			board[piece].set_piece(get_symbol(4));
		}
		else if (piece < 59) {
			board[piece].set_rank(3);
			board[piece].set_piece(get_symbol(3));
		}
		else if (piece < 64) {
			board[piece].set_rank(2);
			board[piece].set_piece(get_symbol(2));
		}
		else if (piece < 72) {
			board[piece].set_rank(1);
			board[piece].set_piece(get_symbol(1));
		}
		else if (piece < 73) {
			board[piece].set_rank(-1);
			board[piece].set_piece(get_symbol(-1));
		}
		else if (piece < 79) {
			board[piece].set_rank(-2);
			board[piece].set_piece(get_symbol(-2));
		}
		else if (piece == 79) {
			board[piece].set_rank(0);
			board[piece].set_piece(get_symbol(0));
		}
	}
}

int stratego_pieces::get_id_with_location(int row, int column) {
	for (int id = 0; id < 80; id++) {
		if ((board[id].get_row() == row) && (board[id].get_column() == column) && board[id].get_inPlay()) {
			return id;
		}
	}
	return -1;
}

int stratego_pieces::get_id_with_rank(int rank, int owner) {
	for (int id = 0; id < 80; id++) {
		if ((board[id].get_rank() == rank) && (board[id].get_owner() == owner)) {
			return id;
		}
	}
	return -1;
}

bool stratego_pieces::players_piece_at_position(int row, int column, int owner) {
	for (int piece = 0; piece < 80; piece++) {
		if ((board[piece].get_row() == row) && (board[piece].get_column() == column) && (board[piece].get_owner() == owner) && board[piece].get_inPlay()) {
			return true;
		}
	}
	return false;
}

void stratego_pieces::remove_piece(int row, int column, int owner) {
	for (int piece = 0; piece < 80; piece++) {
		if ((board[piece].get_row() == row) && (board[piece].get_column() == column) && (board[piece].get_owner() == owner) && board[piece].get_inPlay()) {
			board[piece].set_inPlay(false);
		}
	}
}

void stratego_pieces::remove_piece(int id) {
	board[id].set_inPlay(false);
}

void stratego_pieces::add_piece(int rank, int owner, int row, int column) {
	for (int piece = 0; piece < 80; piece++) {
		if ((board[piece].get_owner() == owner) && (board[piece].get_rank() == rank) && (!board[piece].get_inPlay())) {
			remove_piece(row, column, owner);
			board[piece].set_row(row);
			board[piece].set_column(column);
			board[piece].set_inPlay(true);
			break;
		}
	}
}

void stratego_pieces::set_most_powerful_piece(char symbol) {
	most_powerful_piece = symbol;
}

char stratego_pieces::get_symbol(int rank) {
	if (rank == -2) {
		return 'b';
	}
	else if (rank == -1) {
		return 's';
	}
	else if (rank == 0) {
		return 'f';
	}
	else if (rank == 1) {
		if (most_powerful_piece == '1') {
			return '9';
		}
		else if (most_powerful_piece == '9') {
			return '1';
		}
	}
	else if (rank == 2) {
		if (most_powerful_piece == '1') {
			return '8';
		}
		else if (most_powerful_piece == '9') {
			return '2';
		}
	}
	else if (rank == 3) {
		if (most_powerful_piece == '1') {
			return '7';
		}
		else if (most_powerful_piece == '9') {
			return '3';
		}
	}
	else if (rank == 4) {
		if (most_powerful_piece == '1') {
			return '6';
		}
		else if (most_powerful_piece == '9') {
			return '4';
		}
	}
	else if (rank == 5) {
		if (most_powerful_piece == '1') {
			return '5';
		}
		else if (most_powerful_piece == '9') {
			return '5';
		}
	}
	else if (rank == 6) {
		if (most_powerful_piece == '1') {
			return '4';
		}
		else if (most_powerful_piece == '9') {
			return '6';
		}
	}
	else if (rank == 7) {
		if (most_powerful_piece == '1') {
			return '3';
		}
		else if (most_powerful_piece == '9') {
			return '7';
		}
	}
	else if (rank == 8) {
		if (most_powerful_piece == '1') {
			return '2';
		}
		else if (most_powerful_piece == '9') {
			return '8';
		}
	}
	else if (rank == 9) {
		if (most_powerful_piece == '1') {
			return '1';
		}
		else if (most_powerful_piece == '9') {
			return '9';
		}
	}
}

stratego_piece stratego_pieces::get_piece_data(int id) {
	return board[id];
}

int stratego_pieces::get_best_rank(int owner) {
	int top_rank = 1;
	for (int piece = 0; piece < 80; piece++) {
		if ((board[piece].get_owner() == owner) && (board[piece].get_rank() > top_rank) && board[piece].get_inPlay()) {
			top_rank = board[piece].get_rank();
		}
	}
	return top_rank;
}

void stratego_pieces::change_piece_position(int id, int new_row, int new_column) {
	board[id].set_row(new_row);
	board[id].set_column(new_column);
}

bool stratego_pieces::player_pieces_placed(int owner) {
	for (int piece = 0; piece < 80; piece++) {
		if ((board[piece].get_owner() == owner) && (board[piece].get_inPlay() == false)) {
			return false;
		}
	}
	return true;
}

bool stratego_pieces::player_flag_out_of_play(int player) {
	for (int piece = 0; piece < 80; piece++) {
		if ((board[piece].get_owner() == player) && (board[piece].get_rank() == 0) && (board[piece].get_inPlay() == false)) {
			return true;
		}
	}
	return false;
}

void stratego_pieces::set_pieces(stratego_piece pieces[80]) {
	for (int piece = 0; piece < 80; piece++) {
		board[piece].set_inPlay(pieces[piece].get_inPlay());
		board[piece].set_owner(pieces[piece].get_owner());
		board[piece].set_rank(pieces[piece].get_rank());
		board[piece].set_piece(pieces[piece].get_piece());
		board[piece].set_row(pieces[piece].get_row());
		board[piece].set_column(pieces[piece].get_column());
	}
}