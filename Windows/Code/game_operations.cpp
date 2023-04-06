#include <string>
#include <iostream>
//#include <windows.h>
#include "Stratego.h"
#include "game_operations.h"
#include <conio.h>
#include <fstream>
using namespace std;

void stratego_operations::add_curser_to_board() {
	(board[curser_y_position][curser_x_position])[0] = '(';
	(board[curser_y_position][curser_x_position])[2] = ')';
}

void stratego_operations::remove_curser_from_board() {
	(board[curser_y_position][curser_x_position])[0] = ' ';
	(board[curser_y_position][curser_x_position])[2] = ' ';
}


void stratego_operations::initialize_board() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = "   ";
		}
	}
	board[4][2] = "_-`";
	board[5][2] = "_-`";
	board[4][3] = "`-_";
	board[5][3] = "`-_";
	board[4][6] = "_-`";
	board[5][6] = "_-`";
	board[4][7] = "`-_";
	board[5][7] = "`-_";
}

void stratego_operations::initialize_saved_board() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			saved_board[i][j] = "   ";
		}
	}
}

void stratego_operations::initialize_player1_pieces() {
	for (int i = 0; i < 40; i++) {
		if (i < 1) {
			player1_pieces[i].piece = '1';
		}
		else if (i < 2) {
			player1_pieces[i].piece = '2';
		}
		else if (i < 4) {
			player1_pieces[i].piece = '3';
		}
		else if (i < 7) {
			player1_pieces[i].piece = '4';
		}
		else if (i < 11) {
			player1_pieces[i].piece = '5';
		}
		else if (i < 15) {
			player1_pieces[i].piece = '6';
		}
		else if (i < 19) {
			player1_pieces[i].piece = '7';
		}
		else if (i < 24) {
			player1_pieces[i].piece = '8';
		}
		else if (i < 32) {
			player1_pieces[i].piece = '9';
		}
		else if (i < 33) {
			player1_pieces[i].piece = 's';
		}
		else if (i < 39) {
			player1_pieces[i].piece = 'b';
		}
		else if (i == 39) {
			player1_pieces[i].piece = 'f';
		}
		player1_pieces[i].inPlay = false;
	}
}

void stratego_operations::initialize_player2_pieces() {
	for (int i = 0; i < 40; i++) {
		if (i < 1) {
			player2_pieces[i].piece = '1';
		}
		else if (i < 2) {
			player2_pieces[i].piece = '2';
		}
		else if (i < 4) {
			player2_pieces[i].piece = '3';
		}
		else if (i < 7) {
			player2_pieces[i].piece = '4';
		}
		else if (i < 11) {
			player2_pieces[i].piece = '5';
		}
		else if (i < 15) {
			player2_pieces[i].piece = '6';
		}
		else if (i < 19) {
			player2_pieces[i].piece = '7';
		}
		else if (i < 24) {
			player2_pieces[i].piece = '8';
		}
		else if (i < 32) {
			player2_pieces[i].piece = '9';
		}
		else if (i < 33) {
			player2_pieces[i].piece = 's';
		}
		else if (i < 39) {
			player2_pieces[i].piece = 'b';
		}
		else if (i == 39) {
			player2_pieces[i].piece = 'f';
		}
		player2_pieces[i].inPlay = false;
	}
}

void stratego_operations::initialize_game_saver(string working_directory) {
	file_path1 = working_directory + "game1";
	file_path2 = working_directory + "game2";
	file_path3 = working_directory + "game3";
	file_path4 = working_directory + "game4";
}

void stratego_operations::move_curser_position(int direction) {
	if (((player_turn == 1) && (direction == KEY_UP)) || ((player_turn == 2) && (direction == KEY_DOWN))) {
		if ((curser_y_position != 0) && ((curser_y_position != 6) || ((curser_x_position != 2) && (curser_x_position != 3) && (curser_x_position != 6) && (curser_x_position != 7)))) {
			remove_curser_from_board();
			curser_y_position--;
			add_curser_to_board();
		}
	}
	else if (((player_turn == 1) && (direction == KEY_DOWN)) || ((player_turn == 2) && (direction == KEY_UP))) {
		if ((curser_y_position != 9) && ((curser_y_position != 3) || ((curser_x_position != 2) && (curser_x_position != 3) && (curser_x_position != 6) && (curser_x_position != 7)))) {
			remove_curser_from_board();
			curser_y_position++;
			add_curser_to_board();
		}
	}
	else if (direction == KEY_RIGHT) {
		if ((curser_x_position != 9) && ((curser_x_position != 1) || ((curser_y_position != 4) && (curser_y_position != 5))) && ((curser_x_position != 5) || ((curser_y_position != 4) && (curser_y_position != 5)))) {
			remove_curser_from_board();
			curser_x_position++;
			add_curser_to_board();
		}
	}
	else if (direction == KEY_LEFT) {
		if ((curser_x_position != 0) && ((curser_x_position != 8) || ((curser_y_position != 4) && (curser_y_position != 5))) && ((curser_x_position != 4) || ((curser_y_position != 4) && (curser_y_position != 5)))) {
			remove_curser_from_board();
			curser_x_position--;
			add_curser_to_board();
		}
	}
}

void stratego_operations::set_up_handler(int command) {
	if (command == SPACE) {
		place_piece(' ');
		placment_piece = ' ';
		system("CLS");
		display_board_in_setup_configuration();
	}
	else if (command == ONE) {
		if (get_pieces_out_of_play('1') != 0) {
			place_piece('1');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == TWO) {
		if (get_pieces_out_of_play('2') != 0) {
			place_piece('2');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == THREE) {
		if (get_pieces_out_of_play('3') != 0) {
			place_piece('3');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == FOUR) {
		if (get_pieces_out_of_play('4') != 0) {
			place_piece('4');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == FIVE) {
		if (get_pieces_out_of_play('5') != 0) {
			place_piece('5');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == SIX) {
		if (get_pieces_out_of_play('6') != 0) {
			place_piece('6');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == SEVEN) {
		if (get_pieces_out_of_play('7') != 0) {
			place_piece('7');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == EIGHT) {
		if (get_pieces_out_of_play('8') != 0) {
			place_piece('8');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == NINE) {
		if (get_pieces_out_of_play('9') != 0) {
			place_piece('9');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == S) {
		if (get_pieces_out_of_play('s') != 0) {
			place_piece('s');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == B) {
		if (get_pieces_out_of_play('b') != 0) {
			place_piece('b');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if (command == F) {
		if (get_pieces_out_of_play('f') != 0) {
			place_piece('f');
			system("CLS");
			display_board_in_setup_configuration();
		}
	}
	else if ((command == KEY_RIGHT) || (command == KEY_LEFT) || (command == KEY_UP) || (command == KEY_DOWN)) {
		move_curser_position(command);
		system("CLS");
		display_board_in_setup_configuration();
	}
}

int stratego_operations::get_pieces_out_of_play(char piece) {
	int num_pieces = 0;
	for (int i = 0; i < 40; i++) {
		if (player_turn == 1) {
			if ((!player1_pieces[i].inPlay) && (player1_pieces[i].piece == piece)) {
				num_pieces++;
			}
		}
		else if (player_turn == 2) {
			if ((!player2_pieces[i].inPlay) && (player2_pieces[i].piece == piece)) {
				num_pieces++;
			}
		}
	}
	return num_pieces;
}

void stratego_operations::place_piece(char piece) {
	if (player_turn == 1) {
		if (curser_y_position > 5) {
			(board[curser_y_position][curser_x_position])[1] = piece;
			remove_player1_piece_from_curser_position();
			assign_curser_position_to_player1_piece(piece);
		}
	}
	else if (player_turn == 2) {
		if (curser_y_position < 4) {
			(board[curser_y_position][curser_x_position])[1] = piece;
			remove_player2_piece_from_curser_position();
			assign_curser_position_to_player2_piece(piece);
		}
	}
}

void stratego_operations::display_player1_out_of_play_pieces() {
	int ones = 0, twos = 0, threes = 0, fours = 0, fives = 0, sixes = 0, sevens = 0, eights = 0, nines = 0, spys = 0, bombs = 0, flags = 0;
	string display = "";
	cout << "Player 1's pieces out of play:" << endl;
	for (int i = 0; i < 40; i++) {
		if (!player1_pieces[i].inPlay) {
			if (player1_pieces[i].piece == '1') {
				ones++;
			}
			else if (player1_pieces[i].piece == '2') {
				twos++;
			}
			else if (player1_pieces[i].piece == '3') {
				threes++;
			}
			else if (player1_pieces[i].piece == '4') {
				fours++;
			}
			else if (player1_pieces[i].piece == '5') {
				fives++;
			}
			else if (player1_pieces[i].piece == '6') {
				sixes++;
			}
			else if (player1_pieces[i].piece == '7') {
				sevens++;
			}
			else if (player1_pieces[i].piece == '8') {
				eights++;
			}
			else if (player1_pieces[i].piece == '9') {
				nines++;
			}
			else if (player1_pieces[i].piece == 'b') {
				bombs++;
			}
			else if (player1_pieces[i].piece == 's') {
				spys++;
			}
			else if (player1_pieces[i].piece == 'f') {
				flags++;
			}
		}
	}
	
	if (ones != 0) {
		display = display + "1X" + to_string(ones) + " ";
	}
	if (twos != 0) {
		display = display + "2X" + to_string(twos) + " ";
	}
	if (threes != 0) {
		display = display + "3X" + to_string(threes) + " ";
	}
	if (fours != 0) {
		display = display + "4X" + to_string(fours) + " ";
	}
	if (fives != 0) {
		display = display + "5X" + to_string(fives) + " ";
	}
	if (sixes != 0) {
		display = display + "6X" + to_string(sixes) + " ";
	}
	if (sevens != 0) {
		display = display + "7X" + to_string(sevens) + " ";
	}
	if (eights != 0) {
		display = display + "8X" + to_string(eights) + " ";
	}
	if (nines != 0) {
		display = display + "9X" + to_string(nines) + " ";
	}
	if (spys != 0) {
		display = display + "sX" + to_string(spys) + " ";
	}
	if (bombs != 0) {
		display = display + "bX" + to_string(bombs) + " ";
	}
	if (flags != 0) {
		display = display + "fX" + to_string(flags) + " ";
	}

	cout << display << endl;
}

void stratego_operations::display_player2_out_of_play_pieces() {
	int ones = 0, twos = 0, threes = 0, fours = 0, fives = 0, sixes = 0, sevens = 0, eights = 0, nines = 0, spys = 0, bombs = 0, flags = 0;
	string display = "";
	cout << "Player 2's pieces out of play:" << endl;
	for (int i = 0; i < 40; i++) {
		if (!player2_pieces[i].inPlay) {
			if (player2_pieces[i].piece == '1') {
				ones++;
			}
			else if (player2_pieces[i].piece == '2') {
				twos++;
			}
			else if (player2_pieces[i].piece == '3') {
				threes++;
			}
			else if (player2_pieces[i].piece == '4') {
				fours++;
			}
			else if (player2_pieces[i].piece == '5') {
				fives++;
			}
			else if (player2_pieces[i].piece == '6') {
				sixes++;
			}
			else if (player2_pieces[i].piece == '7') {
				sevens++;
			}
			else if (player2_pieces[i].piece == '8') {
				eights++;
			}
			else if (player2_pieces[i].piece == '9') {
				nines++;
			}
			else if (player2_pieces[i].piece == 'b') {
				bombs++;
			}
			else if (player2_pieces[i].piece == 's') {
				spys++;
			}
			else if (player2_pieces[i].piece == 'f') {
				flags++;
			}
		}
	}

	if (ones != 0) {
		display = display + "1X" + to_string(ones) + " ";
	}
	if (twos != 0) {
		display = display + "2X" + to_string(twos) + " ";
	}
	if (threes != 0) {
		display = display + "3X" + to_string(threes) + " ";
	}
	if (fours != 0) {
		display = display + "4X" + to_string(fours) + " ";
	}
	if (fives != 0) {
		display = display + "5X" + to_string(fives) + " ";
	}
	if (sixes != 0) {
		display = display + "6X" + to_string(sixes) + " ";
	}
	if (sevens != 0) {
		display = display + "7X" + to_string(sevens) + " ";
	}
	if (eights != 0) {
		display = display + "8X" + to_string(eights) + " ";
	}
	if (nines != 0) {
		display = display + "9X" + to_string(nines) + " ";
	}
	if (spys != 0) {
		display = display + "sX" + to_string(spys) + " ";
	}
	if (bombs != 0) {
		display = display + "bX" + to_string(bombs) + " ";
	}
	if (flags != 0) {
		display = display + "fX" + to_string(flags) + " ";
	}

	cout << display << endl;
}

int stratego_operations::determine_winner(boardChip player1_piece, boardChip player2_piece) {
	int winner = 0;
	if ((isdigit(player1_piece.piece) != 0) && (isdigit(player2_piece.piece) != 0)) {
		if (atoi(&player1_piece.piece) < atoi(&player2_piece.piece)) {
			winner = 1;
		}
		else if (atoi(&player1_piece.piece) > atoi(&player2_piece.piece)) {
			winner = 2;
		}
		else if (player_turn == 1) {
			winner = 1;
		}
		else if (player_turn == 2) {
			winner = 2;
		}
	}
	else {
		update_player1_powerful_piece();
		update_player2_powerful_piece();
		if ((player1_piece.piece == 's') && (player2_piece.piece == player2_powerful_piece)) {
			winner = 1;
		}
		else if ((player1_piece.piece == 's') && (player2_piece.piece != player2_powerful_piece)) {
			winner = 2;
		}
		else if ((player2_piece.piece == 's') && (player1_piece.piece == player1_powerful_piece)) {
			winner = 2;
		}
		else if ((player2_piece.piece == 's') && (player1_piece.piece != player1_powerful_piece)) {
			winner = 1;
		}
		else if ((player1_piece.piece == 'b') && (player2_piece.piece == '8')) {
			winner = 2;
		}
		else if ((player1_piece.piece == 'b') && (player2_piece.piece != '8')) {
			winner = 1;
		}
		else if ((player2_piece.piece == 'b') && (player1_piece.piece == '8')) {
			winner = 1;
		}
		else if ((player2_piece.piece == 'b') && (player1_piece.piece != '8')) {
			winner = 2;
		}

		if (player1_piece.piece == 'f') {
			winner = 2;
		}
		if (player2_piece.piece == 'f') {
			winner = 1;
		}
	}

	return winner;
}

void stratego_operations::remove_piece(boardChip player_piece) {
	for (int i = 0; i < 40; i++) {
		if ((player2_pieces[i].x_position == player_piece.x_position) && (player2_pieces[i].y_position == player_piece.y_position)) {
			player2_pieces[i].x_position = -1;
			player2_pieces[i].y_position = -1;
			player2_pieces[i].inPlay = false;
			update_piece_positions();
			break;
		}
	}
		
	for (int i = 0; i < 40; i++) {
		if ((player1_pieces[i].x_position == player_piece.x_position) && (player1_pieces[i].y_position == player_piece.y_position)) {
			player1_pieces[i].x_position = -1;
			player1_pieces[i].y_position = -1;
			player1_pieces[i].inPlay = false;
			update_piece_positions();
			break;
		}
	}
}

void stratego_operations::show_player1() {
	for (int i = 0; i < 40; i++) {
		if (player1_pieces[i].inPlay) {
			(board[player1_pieces[i].y_position][player1_pieces[i].x_position])[1] = player1_pieces[i].piece;
		}
	}
}

void stratego_operations::show_player2() {
	for (int i = 0; i < 40; i++) {
		if (player2_pieces[i].inPlay) {
			(board[player2_pieces[i].y_position][player2_pieces[i].x_position])[1] = player2_pieces[i].piece;
		}
	}
}

void stratego_operations::hide_player1() {
	for (int i = 0; i < 40; i++) {
		if (player1_pieces[i].inPlay) {
			(board[player1_pieces[i].y_position][player1_pieces[i].x_position])[1] = 'X';
		}
	}
}

void stratego_operations::hide_player2() {
	for (int i = 0; i < 40; i++) {
		if (player2_pieces[i].inPlay) {
			(board[player2_pieces[i].y_position][player2_pieces[i].x_position])[1] = 'X';
		}
	}
}

void stratego_operations::update_player1_powerful_piece() {
	char powerful_piece = '9';
	for (int i = 0; i < 40; i++) {
		if (player1_pieces[i].inPlay && (isdigit(player1_pieces[i].piece))) {
			if (atoi(&player1_pieces[i].piece) < atoi(&powerful_piece)) {
				powerful_piece = player1_pieces[i].piece;
			}
		}
	}
	player1_powerful_piece = powerful_piece;
}

void stratego_operations::update_player2_powerful_piece() {
	char powerful_piece = '9';
	for (int i = 0; i < 40; i++) {
		if (player2_pieces[i].inPlay && (isdigit(player2_pieces[i].piece))) {
			if (atoi(&player2_pieces[i].piece) < atoi(&powerful_piece)) {
				powerful_piece = player2_pieces[i].piece;
			}
		}
	}
	player2_powerful_piece = powerful_piece;
}

void stratego_operations::display_board() {
	if (player_turn == 1) {
		for (int i = 0; i < 10; i++) {
			cout << ".---.---.---.---.---.---.---.---.---.---." << endl;
			for (int j = 0; j < 10; j++) {
				cout << "|" + board[i][j];
			}
			cout << "|" << endl;
		}
		cout << ".---.---.---.---.---.---.---.---.---.---." << endl;
	}
	else if (player_turn == 2) {
		for (int i = 9; i >= 0; i--) {
			cout << ".---.---.---.---.---.---.---.---.---.---." << endl;
			for (int j = 0; j < 10; j++) {
				cout << "|" + board[i][j];
			}
			cout << "|" << endl;
		}
		cout << ".---.---.---.---.---.---.---.---.---.---." << endl;
	}
}

void stratego_operations::display_saved_board() {
	if (player_turn == 1) {
		for (int i = 0; i < 10; i++) {
			cout << ".---.---.---.---.---.---.---.---.---.---." << endl;
			for (int j = 0; j < 10; j++) {
				cout << "|" + saved_board[i][j];
			}
			cout << "|" << endl;
		}
		cout << ".---.---.---.---.---.---.---.---.---.---." << endl;
	}
	else if (player_turn == 2) {
		for (int i = 9; i >= 0; i--) {
			cout << ".---.---.---.---.---.---.---.---.---.---." << endl;
			for (int j = 0; j < 10; j++) {
				cout << "|" + saved_board[i][j];
			}
			cout << "|" << endl;
		}
		cout << ".---.---.---.---.---.---.---.---.---.---." << endl;
	}
}

void stratego_operations::update_piece_positions() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (!(i == 4 && j == 2) && !(i == 5 && j == 2) && !(i == 4 && j == 3) && !(i == 5 && j == 3) && !(i == 4 && j == 6) && !(i == 5 && j == 6) && !(i == 4 && j == 7) && !(i == 5 && j == 7)) {
				(board[i][j])[1] = ' ';
			}
		}
	}
	for (int i = 0; i < 40; i++) {
		if (player1_pieces[i].inPlay) {
			(board[player1_pieces[i].y_position][player1_pieces[i].x_position])[1] = player1_pieces[i].piece;
		}
		if (player2_pieces[i].inPlay) {
			(board[player2_pieces[i].y_position][player2_pieces[i].x_position])[1] = player2_pieces[i].piece;
		}	
	}
}

void stratego_operations::game_setup_loop() {
	int input;
	player_turn = 1;
	system("CLS");
	display_board_in_setup_configuration();
	while (get_total_pieces_out_of_play() > 0) {
		input = _getch();
		set_up_handler(input);
	}
	player_turn = 2;
	system("CLS");
	hide_player1();
	wait_for_player2_setup_loop();
	system("CLS");
	display_board_in_setup_configuration();
	while (get_total_pieces_out_of_play() > 0) {
		input = _getch();
		set_up_handler(input);
	}
	player_turn = 1;
}

int stratego_operations::get_total_pieces_out_of_play() {
	int pieces_out_of_play = 0;
	if (player_turn == 1) {
		for (int i = 0; i < 40; i++) {
			if (!player1_pieces[i].inPlay) {
				pieces_out_of_play++;
			}
		}
	}
	else if (player_turn == 2) {
		for (int i = 0; i < 40; i++) {
			if (!player2_pieces[i].inPlay) {
				pieces_out_of_play++;
			}
		}
	}
	return pieces_out_of_play;
}

void stratego_operations::assign_curser_position_to_player1_piece(char piece) {
	for (int i = 0; i < 40; i++) {
		if ((player1_pieces[i].piece == piece) && (!player1_pieces[i].inPlay)) {
			player1_pieces[i].x_position = curser_x_position;
			player1_pieces[i].y_position = curser_y_position;
			player1_pieces[i].inPlay = true;
			break;
		}
	}
}

void stratego_operations::assign_curser_position_to_player2_piece(char piece) {
	for (int i = 0; i < 40; i++) {
		if ((player2_pieces[i].piece == piece) && (!player2_pieces[i].inPlay)) {
			player2_pieces[i].x_position = curser_x_position;
			player2_pieces[i].y_position = curser_y_position;
			player2_pieces[i].inPlay = true;
			break;
		}
	}
}

void stratego_operations::remove_player1_piece_from_curser_position() {
	for (int i = 0; i < 40; i++) {
		if ((player1_pieces[i].x_position == curser_x_position) && (player1_pieces[i].y_position == curser_y_position)) {
			player1_pieces[i].x_position = -1;
			player1_pieces[i].y_position = -1;
			player1_pieces[i].inPlay = false;
			break;
		}
	}
}

void stratego_operations::remove_player2_piece_from_curser_position() {
	for (int i = 0; i < 40; i++) {
		if ((player2_pieces[i].x_position == curser_x_position) && (player2_pieces[i].y_position == curser_y_position)) {
			player2_pieces[i].x_position = -1;
			player2_pieces[i].y_position = -1;
			player2_pieces[i].inPlay = false;
			break;
		}
	}
}

void stratego_operations::display_board_in_setup_configuration() {
	display_board();
	if (player_turn == 1) {
		display_player1_out_of_play_pieces();
	}
	else if (player_turn == 2) {
		display_player2_out_of_play_pieces();
	}
}

bool stratego_operations::wait_for_player1_game_loop() {
	int input = 0;
	int input2 = 0;
	system("CLS");
	cout << "Player 1's turn. Press Space to continue" << endl;
	cout << "\n1 -> save as game 1\n2 -> save as game 2\n3 -> save as game 3\n4 -> save as game 4" << endl;
	while ((input != SPACE) && (input != ONE) && (input != TWO) && (input != THREE) && (input != FOUR)){
		input = _getch();
	}
	if (input == SPACE) {
		return false;
	}
	else if (input == ONE) {
		save_game(file_path1);
		system("CLS");
		cout << "Game saved to game 1." << endl;
		cout << "Press Enter to continue." << endl;
		while (input2 != ENTER) {
			input2 = _getch();
		}
		return true;
	}
	else if (input == TWO) {
		save_game(file_path2);
		system("CLS");
		cout << "Game saved to game 2." << endl;
		cout << "Press Enter to continue." << endl;
		while (input2 != ENTER) {
			input2 = _getch();
		}
		return true;
	}
	else if (input == THREE) {
		save_game(file_path3);
		system("CLS");
		cout << "Game saved to game 3." << endl;
		cout << "Press Enter to continue." << endl;
		while (input2 != ENTER) {
			input2 = _getch();
		}
		return true;
	}
	else if (input == FOUR) {
		save_game(file_path4);
		system("CLS");
		cout << "Game saved to game 4." << endl;
		cout << "Press Enter to continue." << endl;
		while (input2 != ENTER) {
			input2 = _getch();
		}
		return true;
	}

}

bool stratego_operations::wait_for_player2_game_loop() {
	int input = 0;
	int input2 = 0;
	system("CLS");
	cout << "Player 2's turn. Press Space to continue" << endl;
	cout << "\n1 -> save as game 1\n2 -> save as game 2\n3 -> save as game 3\n4 -> save as game 4" << endl;
	while ((input != SPACE) && (input != ONE) && (input != TWO) && (input != THREE) && (input != FOUR)) {
		input = _getch();
	}
	if (input == SPACE) {
		return false;
	}
	else if (input == ONE) {
		save_game(file_path1);
		system("CLS");
		cout << "Game saved to game 1." << endl;
		cout << "Press Enter to continue." << endl;
		while (input2 != ENTER) {
			input2 = _getch();
		}
		return true;
	}
	else if (input == TWO) {
		save_game(file_path2);
		system("CLS");
		cout << "Game saved to game 2." << endl;
		cout << "Press Enter to continue." << endl;
		while (input2 != ENTER) {
			input2 = _getch();
		}
		return true;
	}
	else if (input == THREE) {
		save_game(file_path3);
		system("CLS");
		cout << "Game saved to game 3." << endl;
		cout << "Press Enter to continue." << endl;
		while (input2 != ENTER) {
			input2 = _getch();
		}
		return true;
	}
	else if (input == FOUR) {
		save_game(file_path4);
		system("CLS");
		cout << "Game saved to game 4." << endl;
		cout << "Press Enter to continue." << endl;
		while (input2 != ENTER) {
			input2 = _getch();
		}
		return true;
	}
}

void stratego_operations::wait_for_player1_setup_loop() {
	int input = 0;
	system("CLS");
	cout << "Player 1's turn. Press Space to continue." << endl;
	while (input != SPACE) {
		input = _getch();
	}
}

void stratego_operations::wait_for_player2_setup_loop() {
	int input = 0;
	system("CLS");
	cout << "Player 2's turn. Press Space to continue." << endl;
	while (input != SPACE) {
		input = _getch();
	}
}


bool stratego_operations::select_piece_and_move() {
	boardChip selected_piece = get_piece_at_curser_position();
	int input = 0;
	int distance = 1;
	char direction = ' ';
	bool move_made = false;
	if ((selected_piece.piece != ' ') && (selected_piece.piece != 'b') && (selected_piece.piece != 'f') && ((board[curser_y_position][curser_x_position])[1] != 'X')) {
		do {
			input = _getch();
		} while ((input != KEY_UP) && (input != KEY_DOWN) && (input != KEY_RIGHT) && (input != KEY_LEFT));
		if (input == KEY_UP) {
			move_made = move_piece_up_routine(selected_piece);
		}
		else if (input == KEY_DOWN) {
			move_made = move_piece_down_routine(selected_piece);
		}
		else if (input == KEY_RIGHT) {
			move_made = move_piece_right_routine(selected_piece);
		}
		else if (input == KEY_LEFT) {
			move_made = move_piece_left_routine(selected_piece);
		}
	}
	return move_made;
}

//char stratego_operations::get_piece_at_curser_position() {
//	char piece = ' ';
//	piece = (board[curser_y_position][curser_x_position])[1];
//	return piece;
//}

boardChip stratego_operations::get_piece_at_curser_position() {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player1_pieces[i].x_position) && (curser_y_position == player1_pieces[i].y_position)) {
			return player1_pieces[i];
		}
	}

	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player2_pieces[i].x_position) && (curser_y_position == player2_pieces[i].y_position)){
			return player2_pieces[i];
		}
	}
	boardChip empty_piece;
	empty_piece.piece = ' ';
	empty_piece.inPlay = false;
	empty_piece.x_position = -1;
	empty_piece.y_position = -1;
	return empty_piece;
}

void stratego_operations::save_board() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			saved_board[i][j] = board[i][j];
		}
	}
}

void stratego_operations::move_player1_piece_at_curser_position_up(int distance) {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player1_pieces[i].x_position) && (curser_y_position == player1_pieces[i].y_position)) {
			player1_pieces[i].y_position = player1_pieces[i].y_position - distance;
			update_piece_positions();
			break;
		}
	}
}

void stratego_operations::move_player1_piece_at_curser_position_down(int distance) {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player1_pieces[i].x_position) && (curser_y_position == player1_pieces[i].y_position)) {
			player1_pieces[i].y_position = player1_pieces[i].y_position + distance;
			update_piece_positions();
			break;
		}
	}
}

void stratego_operations::move_player1_piece_at_curser_position_right(int distance) {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player1_pieces[i].x_position) && (curser_y_position == player1_pieces[i].y_position)) {
			player1_pieces[i].x_position = player1_pieces[i].x_position + distance;
			update_piece_positions();
			break;
		}
	}
}

void stratego_operations::move_player1_piece_at_curser_position_left(int distance) {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player1_pieces[i].x_position) && (curser_y_position == player1_pieces[i].y_position)) {
			player1_pieces[i].x_position = player1_pieces[i].x_position - distance;
			update_piece_positions();
			break;
		}
	}
}

void stratego_operations::move_player2_piece_at_curser_position_up(int distance) {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player2_pieces[i].x_position) && (curser_y_position == player2_pieces[i].y_position)) {
			player2_pieces[i].y_position = player2_pieces[i].y_position + distance;
			update_piece_positions();
			break;
		}
	}
}

void stratego_operations::move_player2_piece_at_curser_position_down(int distance) {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player2_pieces[i].x_position) && (curser_y_position == player2_pieces[i].y_position)) {
			player2_pieces[i].y_position = player2_pieces[i].y_position - distance;
			update_piece_positions();
			break;
		}
	}
}

void stratego_operations::move_player2_piece_at_curser_position_right(int distance) {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player2_pieces[i].x_position) && (curser_y_position == player2_pieces[i].y_position)) {
			player2_pieces[i].x_position = player2_pieces[i].x_position + distance;
			update_piece_positions();
			break;
		}
	}
}

void stratego_operations::move_player2_piece_at_curser_position_left(int distance) {
	for (int i = 0; i < 40; i++) {
		if ((curser_x_position == player2_pieces[i].x_position) && (curser_y_position == player2_pieces[i].y_position)) {
			player2_pieces[i].x_position = player2_pieces[i].x_position - distance;
			update_piece_positions();
			break;
		}
	}
}

bool stratego_operations::board_chip_clear(int x_position, int y_position) {
	if ((board[y_position][x_position])[1] == ' ') {
		return true;
	}
	else {
		return false;
	}
}

bool stratego_operations::player1_piece_at_location(int x_position, int y_position) {
	for (int i = 0; i < 40; i++) {
		if ((player1_pieces[i].x_position == x_position) && (player1_pieces[i].y_position == y_position)) {
			return true;
		}
	}
	return false;
}

bool stratego_operations::player2_piece_at_location(int x_position, int y_position) {
	for (int i = 0; i < 40; i++) {
		if ((player2_pieces[i].x_position == x_position) && (player2_pieces[i].y_position == y_position)) {
			return true;
		}
	}
	return false;
}

void stratego_operations::reveal_piece(boardChip board_piece) {
	(board[board_piece.y_position][board_piece.x_position])[1] = board_piece.piece;
}

bool stratego_operations::player1_win() {
	for (int i = 0; i < 40; i++) {
		if ((player2_pieces[i].piece == 'f') && (player2_pieces[i].inPlay == false)) {
			return true;
		}
	}
	return false;
}

bool stratego_operations::player2_win() {
	for (int i = 0; i < 40; i++) {
		if ((player1_pieces[i].piece == 'f') && (player1_pieces[i].inPlay == false)) {
			return true;
		}
	}
	return false;
}

void stratego_operations::game_loop() {
	int input = 0;
	int input2 = 0;
	int input3 = 0;
	int input4 = 0;
	int input5 = 0;
	bool move_made;
	bool game_saved;
	if (player_turn == 1) {
		system("CLS");
		hide_player2();
		show_player1();
		game_saved = wait_for_player1_game_loop();
		if (game_saved) {
			return;
		}
		if (game_loaded) {
			system("CLS");
			display_saved_board();
			cout << "Opponent's move. Press enter to continue." << endl;
			do {
				input5 = _getch();
			} while (input5 != ENTER);
			game_loaded = false;
		}
		system("CLS");
		display_board();
		display_player1_out_of_play_pieces();
		display_player2_out_of_play_pieces();
	}
	else if (player_turn == 2) {
		system("CLS");
		hide_player1();
		show_player2();
		game_saved = wait_for_player2_game_loop();
		if (game_saved) {
			return;
		}
		if (game_loaded) {
			system("CLS");
			display_saved_board();
			cout << "Opponent's move. Press enter to continue." << endl;
			do {
				input5 = _getch();
			} while (input5 != ENTER);
			game_loaded = false;
		}
		system("CLS");
		display_board();
		display_player1_out_of_play_pieces();
		display_player2_out_of_play_pieces();
	}
	
	while (!player1_win() && !player2_win()) {
		input = _getch();
		if ((input == KEY_UP) || (input == KEY_DOWN) || (input == KEY_RIGHT) || (input == KEY_LEFT)) {
			move_curser_position(input);
			system("CLS");
			display_board();
			display_player1_out_of_play_pieces();
			display_player2_out_of_play_pieces();
		}
		else if (input == ENTER) {
			move_made = select_piece_and_move();
			if (player1_win() || player2_win()) {
				break;
			}
			if (move_made) {
				if (player_turn == 1) {
					player_turn = 2;
					hide_player1();
					show_player2();
					game_saved = wait_for_player2_game_loop();
					if (game_saved) {
						return;
					}
				}
				else if (player_turn == 2) {
					player_turn = 1;
					hide_player2();
					show_player1();
					game_saved = wait_for_player1_game_loop();
					if (game_saved) {
						return;
					}
				}
				system("CLS");
				display_saved_board();
				cout << "Opponent's move. Press enter to continue." << endl;
				do {
					input = _getch();
				} while (input != ENTER);
				system("CLS");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
			}
		}	
	}
	if (player1_win()) {
		system("CLS");
		cout << "Player 1 won." << endl;
	}
	else if (player2_win()) {
		system("CLS");
		cout << "Player 2 won." << endl;
	}
	cout << "Press Enter to view player 1's pieces." << endl;
	while (input4 != ENTER) {
		input4 = _getch();
	}
	player_turn = 1;
	hide_player2();
	show_player1();
	system("CLS");
	cout << "Player 1's pieces." << endl;
	display_board();
	cout << "Press Enter to view player 2's pieces." << endl;
	while (input2 != ENTER) {
		input2 = _getch();
	}
	player_turn = 2;
	hide_player1();
	show_player2();
	system("CLS");
	cout << "Player 2's pieces." << endl;
	display_board();
	cout << "Press Enter to end game." << endl;
	while (input3 != ENTER) {
		input3 = _getch();
	}
}

void stratego_operations::fill_board() {
	int counter = 39;
	for (int j = 6; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			//(board[j][i])[1] = player1_pieces[counter].piece;
			player1_pieces[counter].inPlay = true;
			player1_pieces[counter].x_position = i;
			player1_pieces[counter].y_position = j;
			counter--;
		}
	}
	counter = 39;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 10; i++) {
			//(board[j][i])[1] = player2_pieces[counter].piece;
			player2_pieces[counter].inPlay = true;
			player2_pieces[counter].x_position = i;
			player2_pieces[counter].y_position = j;
			counter--;
		}
	}
	update_piece_positions();
	player_turn = 1;
}

int stratego_operations::move_scout_up() {
	int input = _getch();
	int scout_y_position = 0;
	if (player_turn == 1) {
		scout_y_position = curser_y_position - 1;
	}
	else if (player_turn == 2) {
		scout_y_position = curser_y_position + 1;
	}
	while ((input != ENTER) && (input != ESC)) {
		input = _getch();
		if (((input == KEY_UP) && (player_turn == 1) && !player1_piece_at_location(curser_x_position, scout_y_position - 1) && !player2_piece_at_location(curser_x_position, scout_y_position)) || ((input == KEY_DOWN) && (player_turn == 2) && !player2_piece_at_location(curser_x_position, scout_y_position - 1) && !player1_piece_at_location(curser_x_position, scout_y_position))) {
			if ((scout_y_position != 0) && ((scout_y_position != 6) || ((curser_x_position != 2) && (curser_x_position != 3) && (curser_x_position != 6) && (curser_x_position != 7)))) {
				if (!((player_turn == 2) && ((scout_y_position - 1) <= curser_y_position))) {
					if ((player_turn == 1) && ((board[scout_y_position][curser_x_position])[1] == ' ')) {
						(board[scout_y_position][curser_x_position])[1] = '^';
					}
					scout_y_position--;
					if ((player_turn == 2) && ((board[scout_y_position][curser_x_position])[1] == '^')) {
						(board[scout_y_position][curser_x_position])[1] = ' ';
					}
					system("CLS");
					display_board();
					display_player1_out_of_play_pieces();
					display_player2_out_of_play_pieces();
				}
			}
		}
		else if (((input == KEY_DOWN) && (player_turn == 1) && !player1_piece_at_location(curser_x_position, scout_y_position + 1) && !player2_piece_at_location(curser_x_position, scout_y_position)) || ((input == KEY_UP) && (player_turn == 2) && !player2_piece_at_location(curser_x_position, scout_y_position + 1) && !player1_piece_at_location(curser_x_position, scout_y_position))) {
			if ((scout_y_position != 9) && ((scout_y_position != 3) || ((curser_x_position != 2) && (curser_x_position != 3) && (curser_x_position != 6) && (curser_x_position != 7)))) {
				if (!((player_turn == 1) && ((scout_y_position + 1) >= curser_y_position))) {
					if ((player_turn == 2) && ((board[scout_y_position][curser_x_position])[1] == ' ')) {
						(board[scout_y_position][curser_x_position])[1] = '^';
					}
					scout_y_position++;
					if ((player_turn == 1) && ((board[scout_y_position][curser_x_position])[1] == '^')) {
						(board[scout_y_position][curser_x_position])[1] = ' ';
					}
					system("CLS");
					display_board();
					display_player1_out_of_play_pieces();
					display_player2_out_of_play_pieces();
				}
			}
		}
		else if (input == ESC) {
			return 0;
		}
	}
	return abs(curser_y_position - scout_y_position);
}

int stratego_operations::move_scout_down() {
	int input = _getch();
	int scout_y_position = 0;
	if (player_turn == 1) {
		scout_y_position = curser_y_position + 1;
	}
	else if (player_turn == 2) {
		scout_y_position = curser_y_position - 1;
	}
	while ((input != ENTER) && (input != ESC)) {
		input = _getch();
		if (((input == KEY_UP) && (player_turn == 1) && !player1_piece_at_location(curser_x_position, scout_y_position - 1) && !player2_piece_at_location(curser_x_position, scout_y_position)) || ((input == KEY_DOWN) && (player_turn == 2) && !player2_piece_at_location(curser_x_position, scout_y_position - 1) && !player1_piece_at_location(curser_x_position, scout_y_position))) {
			if ((scout_y_position != 0) && ((scout_y_position != 6) || ((curser_x_position != 2) && (curser_x_position != 3) && (curser_x_position != 6) && (curser_x_position != 7)))) {
				if (!((player_turn == 1) && ((scout_y_position - 1) <= curser_y_position))) {
					if ((player_turn == 2) && ((board[scout_y_position][curser_x_position])[1] == ' ')) {
						(board[scout_y_position][curser_x_position])[1] = 'v';
					}
					scout_y_position--;
					if ((player_turn == 1) && ((board[scout_y_position][curser_x_position])[1] == 'v')) {
						(board[scout_y_position][curser_x_position])[1] = ' ';
					}
					system("CLS");
					display_board();
					display_player1_out_of_play_pieces();
					display_player2_out_of_play_pieces();
				}
			}
		}
		else if (((input == KEY_DOWN) && (player_turn == 1) && !player1_piece_at_location(curser_x_position, scout_y_position + 1) && !player2_piece_at_location(curser_x_position, scout_y_position)) || ((input == KEY_UP) && (player_turn == 2) && !player2_piece_at_location(curser_x_position, scout_y_position + 1) && !player1_piece_at_location(curser_x_position, scout_y_position))) {
			if ((scout_y_position != 9) && ((scout_y_position != 3) || ((curser_x_position != 2) && (curser_x_position != 3) && (curser_x_position != 6) && (curser_x_position != 7)))) {
				if (!((player_turn == 2) && ((scout_y_position + 1) >= curser_y_position))) {
					if ((player_turn == 1) && ((board[scout_y_position][curser_x_position])[1] == ' ')) {
						(board[scout_y_position][curser_x_position])[1] = 'v';
					}
					scout_y_position++;
					if ((player_turn == 2) && ((board[scout_y_position][curser_x_position])[1] == 'v')) {
						(board[scout_y_position][curser_x_position])[1] = ' ';
					}
					system("CLS");
					display_board();
					display_player1_out_of_play_pieces();
					display_player2_out_of_play_pieces();
				}
			}
		}
		else if (input == ESC) {
			return 0;
		}
	}
	return abs(curser_y_position - scout_y_position);
}

int stratego_operations::move_scout_right() {
	int input = _getch();
	int scout_x_position = curser_x_position + 1;
	while ((input != ENTER) && (input != ESC)) {
		input = _getch();
		if (((input == KEY_RIGHT) && (player_turn == 1) && !player1_piece_at_location(scout_x_position + 1, curser_y_position) && !player2_piece_at_location(scout_x_position, curser_y_position)) || ((input == KEY_RIGHT) && (player_turn == 2) && !player2_piece_at_location(scout_x_position + 1, curser_y_position) && !player1_piece_at_location(scout_x_position, curser_y_position))) {
			if ((scout_x_position != 9) && ((scout_x_position != 1) || ((curser_y_position != 4) && (curser_y_position != 5))) && ((scout_x_position != 5) || ((curser_y_position != 4) && (curser_y_position != 5)))) {
				if ((board[curser_y_position][scout_x_position])[1] == ' ') {
					(board[curser_y_position][scout_x_position])[1] = '>';
				}
				scout_x_position++;
				system("CLS");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
			}
		}
		else if (input == KEY_LEFT) {
			if ((scout_x_position - 1) > curser_x_position) {
				scout_x_position--;
				if ((board[curser_y_position][scout_x_position])[1] == '>') {
					(board[curser_y_position][scout_x_position])[1] = ' ';
				}
				system("CLS");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
			}
		}
		else if (input == ESC) {
			return 0;
		}
	}
	return abs(scout_x_position - curser_x_position);
}

int stratego_operations::move_scout_left() {
	int input = _getch();
	int scout_x_position = curser_x_position - 1;
	while ((input != ENTER) && (input != ESC)) {
		input = _getch();
		if (((input == KEY_LEFT) && (player_turn == 1) && !player1_piece_at_location(scout_x_position - 1, curser_y_position) && !player2_piece_at_location(scout_x_position, curser_y_position)) || ((input == KEY_LEFT) && (player_turn == 2) && !player2_piece_at_location(scout_x_position - 1, curser_y_position) && !player1_piece_at_location(scout_x_position, curser_y_position))) {
			if ((scout_x_position != 0) && ((scout_x_position != 8) || ((curser_y_position != 4) && (curser_y_position != 5))) && ((scout_x_position != 4) || ((curser_y_position != 4) && (curser_y_position != 5)))) {
				if ((board[curser_y_position][scout_x_position])[1] == ' '){
					(board[curser_y_position][scout_x_position])[1] = '<';
				}
				scout_x_position--;
				system("CLS");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
			}
		}
		else if (input == KEY_RIGHT) {
			if ((scout_x_position + 1) < curser_x_position) {
				scout_x_position++;
				if ((board[curser_y_position][scout_x_position])[1] == '<') {
					(board[curser_y_position][scout_x_position])[1] = ' ';
				}
				system("CLs");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
			}
		}
		else if (input == ESC) {
			return 0;
		}
	}
	return abs(scout_x_position - curser_x_position);
}

boardChip stratego_operations::get_piece_at_position(int x_position, int y_position) {
	for (int i = 0; i < 40; i++) {
		if ((x_position == player1_pieces[i].x_position) && (y_position == player1_pieces[i].y_position)) {
			return player1_pieces[i];
		}
	}

	for (int i = 0; i < 40; i++) {
		if ((x_position == player2_pieces[i].x_position) && (y_position == player2_pieces[i].y_position)) {
			return player2_pieces[i];
		}
	}
	boardChip empty_piece;
	empty_piece.piece = ' ';
	empty_piece.inPlay = false;
	empty_piece.x_position = -1;
	empty_piece.y_position = -1;
	return empty_piece;
}

void stratego_operations::invert_arrows() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if ((board[i][j])[1] == '^') {
				(board[i][j])[1] = 'v';
			}
			else if ((board[i][j])[1] == 'v') {
				(board[i][j])[1] = '^';
			}
		}
	}
	if ((board[curser_y_position][curser_x_position])[0] == '^') {
		(board[curser_y_position][curser_x_position])[0] = 'v';
		(board[curser_y_position][curser_x_position])[2] = 'v';
	}
	else if ((board[curser_y_position][curser_x_position])[0] == 'v') {
		(board[curser_y_position][curser_x_position])[0] = '^';
		(board[curser_y_position][curser_x_position])[2] = '^';
	}
}

void stratego_operations::save_game(string file_path) {
	string game = "";
	game = to_string(player_turn) + "\n";
	hide_player2();
	show_player1();
	game = game + get_board(1);
	game = game + "\n#\n";
	hide_player1();
	show_player2();
	game = game + get_board(1);
	game = game + "\n#\n";
	game = game + get_saved_board(1);
	write_file(file_path, game);
}

bool stratego_operations::write_file(string file_path, string message) {
	bool success = false;
	ofstream file(file_path);
	if (file.is_open()) {
		file << message << endl;
		success = true;
	}
	else {
		success = false;
	}
	return success;
}

string stratego_operations::get_board(int player_turn) {
	string board_str = "";
	if (player_turn == 1) {
		for (int i = 0; i < 10; i++) {
			board_str = board_str +  ".---.---.---.---.---.---.---.---.---.---.\n";
			for (int j = 0; j < 10; j++) {
				board_str = board_str + "|" + board[i][j];
			}
			board_str = board_str + "|\n";
		}
		board_str = board_str + ".---.---.---.---.---.---.---.---.---.---.\n";
	}
	else if (player_turn == 2) {
		for (int i = 9; i >= 0; i--) {
			board_str + board_str + ".---.---.---.---.---.---.---.---.---.---.\n";
			for (int j = 0; j < 10; j++) {
				board_str = board_str + "|" + board[i][j];
			}
			board_str = board_str + "|\n";
		}
		board_str = board_str + ".---.---.---.---.---.---.---.---.---.---.\n";
	}
	return board_str;
}

string stratego_operations::get_saved_board(int player_turn) {
	string board_str = "";
	if (player_turn == 1) {
		for (int i = 0; i < 10; i++) {
			board_str = board_str + ".---.---.---.---.---.---.---.---.---.---.\n";
			for (int j = 0; j < 10; j++) {
				board_str = board_str + "|" + saved_board[i][j];
			}
			board_str = board_str + "|\n";
		}
		board_str = board_str + ".---.---.---.---.---.---.---.---.---.---.\n";
	}
	else if (player_turn == 2) {
		for (int i = 9; i >= 0; i--) {
			board_str + board_str + ".---.---.---.---.---.---.---.---.---.---.\n";
			for (int j = 0; j < 10; j++) {
				board_str = board_str + "|" + saved_board[i][j];
			}
			board_str = board_str + "|\n";
		}
		board_str = board_str + ".---.---.---.---.---.---.---.---.---.---.\n";
	}
	return board_str;
}

string stratego_operations::read_file(string file_path) {
	ifstream file(file_path);
	string message;

	if (file.is_open()) {
		char letter[1];
		while (!file.eof()) {
			file.read(letter, 1);
			message = message + letter[0];
		}
		message.erase((message.length() - 2), 2);
		file.close();
	}
	else {
		cout << "Cannot find file.\n" << endl;
		message = "";
	}
	return message;
}

bool stratego_operations::load_game(string file_path) {
	string game_board = "";
	string board1 = "";
	string board2 = "";
	string board3 = "";
	string turn = "";
	int input = 0;
	game_board = read_file(file_path);
	int line = 0;
	if (game_board.length() != 0) {
		initialize_player1_pieces();
		initialize_player2_pieces();
		int x_position = -1;
		int y_position = -1;
		int index = 0;
		while (game_board[index] != '\n') {
			turn = game_board[index];
			index++;
		}
		player_turn = atoi(turn.c_str());
		index++;
		while (game_board[index] != '#') {
			board1 = board1 + game_board[index];
			index++;
		}
		index = index + 2;
		while (game_board[index] != '#') {
			board2 = board2 + game_board[index];
			index++;
		}
		index = index + 2;
		while (index < game_board.length()) {
			board3 = board3 + game_board[index];
			index++;
		}

		for (int i = 0; i < (board1.length() - 2); i++) {
			if (board1[i] == '|') {
				x_position++;
			}
			if (board1[i] == '\n') {
				x_position = -1;
				line++;
				y_position = line / 2;
			}
			if ((board1[i] == '1') || (board1[i] == '2') || (board1[i] == '3') || (board1[i] == '4') || (board1[i] == '5') || (board1[i] == '6') || (board1[i] == '7') || (board1[i] == '8') || (board1[i] == '9') || (board1[i] == 's') || (board1[i] == 'b') || (board1[i] == 'f')) {
				for (int j = 0; j < 40; j++) {
					if ((!player1_pieces[j].inPlay) && (player1_pieces[j].piece == board1[i])) {
						player1_pieces[j].piece = board1[i];
						player1_pieces[j].x_position = x_position;
						player1_pieces[j].y_position = y_position;
						player1_pieces[j].inPlay = true;
						break;
					}
				}
			}
		}
		x_position = -1;
		y_position = -1;
		line = 0;

		for (int i = 0; i < (board2.length() - 2); i++) {
			if (board2[i] == '|') {
				x_position++;
			}
			if (board2[i] == '\n') {
				x_position = -1;
				line++;
				y_position = line / 2;
			}
			if ((board2[i] == '1') || (board2[i] == '2') || (board2[i] == '3') || (board2[i] == '4') || (board2[i] == '5') || (board2[i] == '6') || (board2[i] == '7') || (board2[i] == '8') || (board2[i] == '9') || (board2[i] == 's') || (board2[i] == 'b') || (board2[i] == 'f')) {
				for (int j = 0; j < 40; j++) {
					if ((!player2_pieces[j].inPlay) && (player2_pieces[j].piece == board2[i])) {
						player2_pieces[j].piece = board2[i];
						player2_pieces[j].x_position = x_position;
						player2_pieces[j].y_position = y_position;
						player2_pieces[j].inPlay = true;
						break;
					}
				}
			}
		}
		x_position = -1;
		y_position = -1;
		line = 0;

		for (int i = 0; i < (board3.length() - 2); i++) {
			if ((board3[i] == '|') && (board3[i + 1] != '\n')) {
				x_position++;
				(saved_board[y_position][x_position])[0] = board3[i + 1];
				(saved_board[y_position][x_position])[1] = board3[i + 2];
				(saved_board[y_position][x_position])[2] = board3[i + 3];
			}
			if (board3[i] == '\n') {
				x_position = -1;
				line++;
				y_position = line / 2;
			}
		}
		game_loaded = true;
		update_piece_positions();
		return true;
	}
	else {
		return false;
	}
}

bool stratego_operations::menu_loop() {
	bool load_success = false;
	int input = 0;
	system("CLS");
	while (load_success == false) {
		cout << "0 -> new game\n1 -> load game 1\n2 -> load game 2\n3 -> load game 3\n4 -> load game 4" << endl;
		while ((input != ZERO) && (input != ONE) && (input != TWO) && (input != THREE) && (input != FOUR)) {
			input = _getch();
		}
		if (input == ZERO) {
			load_success = true;
			return true;
		}
		if (input == ONE) {
			load_success = load_game(file_path1);
			if (load_success == false) {
				cout << "There is no game saved for that game number." << endl; 
				input = 0;
			}
			else {
				return false;
			}
		}
		else if (input == TWO) {
			load_success = load_game(file_path2);
			if (load_success == false) {
				cout << "There is no game saved for that game number." << endl;
				input = 0;
			}
			else {
				return false;
			}
		}
		else if (input == THREE) {
			load_success = load_game(file_path3);
			if (load_success == false) {
				cout << "There is no game saved for that game number." << endl;
				input = 0;
			}
			else {
				return false;
			}
		}
		else if (input == FOUR) {
			load_success = load_game(file_path4);
			if (load_success == false) {
				cout << "There is no game saved for that game number." << endl;
				input = 0;
			}
			else {
				return false;
			}
		}
	}
}

bool stratego_operations::not_no_man_zone(int direction) {
	if (direction == KEY_UP) {
		return ((curser_y_position != 0) && ((curser_y_position != 6) || ((curser_x_position != 2) && (curser_x_position != 3) && (curser_x_position != 6) && (curser_x_position != 7))));
	}
	else if (direction == KEY_DOWN) {
		return ((curser_y_position != 9) && ((curser_y_position != 3) || ((curser_x_position != 2) && (curser_x_position != 3) && (curser_x_position != 6) && (curser_x_position != 7))));
	}
	else if (direction == KEY_RIGHT) {
		return ((curser_x_position != 9) && ((curser_x_position != 1) || ((curser_y_position != 4) && (curser_y_position != 5))) && ((curser_x_position != 5) || ((curser_y_position != 4) && (curser_y_position != 5))));
	}
	else if (direction == KEY_DOWN) {
		return ((curser_x_position != 0) && ((curser_x_position != 8) || ((curser_y_position != 4) && (curser_y_position != 5))) && ((curser_x_position != 4) || ((curser_y_position != 4) && (curser_y_position != 5))));
	}
}

bool stratego_operations::move_piece_up_routine(boardChip selected_piece) {
	int distance = 1;
	int winner = 0;
	int input = 0;
	bool scout_enter = false;
	if (not_no_man_zone(KEY_UP) && clear_of_own_piece(KEY_UP)) {
		display_move_up_curser();
		if (selected_piece.piece == '9') {
			distance = move_scout_up();
			if (distance == 0) {
				remove_arrows_from_board();
				add_curser_to_board();
				system("CLS");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
				return false;
			}
			else {
				scout_enter = true;
				input = ENTER;
			}
		}
	}
	do {
		if (!scout_enter) {
			input = _getch();
		}
		if ((player_turn == 1) && (input == ENTER)) {
			if (board_chip_clear(curser_x_position, curser_y_position - distance)) {
				move_player1_piece_at_curser_position_up(distance);
				display_move_result(1);
				invert_arrows();
				save_move(2);
				add_curser_to_board();
				return true;
			}
			else if (player2_piece_at_location(curser_x_position, curser_y_position - distance)) {
				boardChip player1_piece = get_piece_at_curser_position();
				boardChip player2_piece = get_piece_at_position(curser_x_position, curser_y_position - distance);
				reveal_piece_display_routine(player2_piece);
				invert_arrows();
				winner = determine_winner(player1_piece, player2_piece);
				if (winner == 1) {
					save_move(2);
					remove_piece(player2_piece);
				}
				else if (winner == 2) {
					configure_board_for_player2();
					reveal_piece(player1_piece);
					save_board();
					remove_piece(player1_piece);
				}
				add_curser_to_board();
				move_player1_piece_at_curser_position_up(distance);
				display_move_result(1);
				return true;
			}
			else {
				return false;
			}
		}
		if ((player_turn == 2) && (input == ENTER)) {
			if (board_chip_clear(curser_x_position, curser_y_position + distance)) {
				move_player2_piece_at_curser_position_up(distance);
				display_move_result(2);
				invert_arrows();
				save_move(1);
				add_curser_to_board();
				return true;
			}
			else if (player1_piece_at_location(curser_x_position, curser_y_position + distance)) {
				boardChip player2_piece = get_piece_at_curser_position();
				boardChip player1_piece = get_piece_at_position(curser_x_position, curser_y_position + distance);
				reveal_piece_display_routine(player1_piece);
				invert_arrows();
				winner = determine_winner(player1_piece, player2_piece);
				if (winner == 1) {
					configure_board_for_player1();
					reveal_piece(player2_piece);
					save_board();
					remove_piece(player2_piece);
				}
				else if (winner == 2) {
					save_move(1);
					remove_piece(player1_piece);
				}
				add_curser_to_board();
				move_player2_piece_at_curser_position_up(distance);
				display_move_result(2);
				return true;
			}
			else {
				return false;
			}
		}
	} while ((input != ESC) && (input != ENTER));

	if (input == ESC) {
		add_curser_to_board();
		system("CLS");
		display_board();
		display_player1_out_of_play_pieces();
		display_player2_out_of_play_pieces();
		return false;
	}
}

bool stratego_operations::move_piece_down_routine(boardChip selected_piece) {
	int distance = 1;
	int winner = 0;
	int input = 0;
	bool scout_enter = false;
	if (not_no_man_zone(KEY_DOWN) && clear_of_own_piece(KEY_DOWN)) {
		display_move_down_curser();
		if (selected_piece.piece == '9') {
			distance = move_scout_down();
			if (distance == 0) {
				remove_arrows_from_board();
				add_curser_to_board();
				system("CLS");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
				return false;
			}
			else {
				scout_enter = true;
				input = ENTER;
			}
		}
	}

	do {
		if (!scout_enter) {
			input = _getch();
		}
		if ((player_turn == 1) && (input == ENTER)) {
			if (board_chip_clear(curser_x_position, curser_y_position + distance)) {
				move_player1_piece_at_curser_position_down(distance);
				display_move_result(1);
				invert_arrows();
				save_move(2);
				add_curser_to_board();
				return true;
			}
			else if (player2_piece_at_location(curser_x_position, curser_y_position + distance)) {
				boardChip player1_piece = get_piece_at_curser_position();
				boardChip player2_piece = get_piece_at_position(curser_x_position, curser_y_position + distance);
				reveal_piece_display_routine(player2_piece);
				invert_arrows();
				winner = determine_winner(player1_piece, player2_piece);
				if (winner == 1) {
					save_move(2);
					remove_piece(player2_piece);
				}
				else if (winner == 2) {
					configure_board_for_player2();
					reveal_piece(player1_piece);
					save_board();
					remove_piece(player1_piece);
				}
				add_curser_to_board();
				move_player1_piece_at_curser_position_down(distance);
				display_move_result(1);
				return true;
			}
			else {
				return false;
			}
		}
		if ((player_turn == 2) && (input == ENTER)) {
			if (board_chip_clear(curser_x_position, curser_y_position - distance)) {
				move_player2_piece_at_curser_position_down(distance);
				display_move_result(2);
				invert_arrows();
				save_move(1);
				add_curser_to_board();
				return true;
			}
			else if (player1_piece_at_location(curser_x_position, curser_y_position - distance)) {
				boardChip player2_piece = get_piece_at_curser_position();
				boardChip player1_piece = get_piece_at_position(curser_x_position, curser_y_position - distance);
				reveal_piece_display_routine(player1_piece);
				invert_arrows();
				winner = determine_winner(player1_piece, player2_piece);
				if (winner == 1) {
					configure_board_for_player1();
					reveal_piece(player2_piece);
					save_board();
					remove_piece(player2_piece);
				}
				else if (winner == 2) {
					save_move(1);
					remove_piece(player1_piece);
				}
				add_curser_to_board();
				move_player2_piece_at_curser_position_down(distance);
				display_move_result(2);
				return true;
			}
			else {
				return false;
			}
		}
	} while ((input != ESC) && (input != ENTER));
	
	if (input == ESC) {
		add_curser_to_board();
		system("CLS");
		display_board();
		display_player1_out_of_play_pieces();
		display_player2_out_of_play_pieces();
		return false;
	}
}

bool stratego_operations::move_piece_right_routine(boardChip selected_piece) {
	int distance = 1;
	int winner = 0;
	int input = 0;
	bool scout_enter = false;
	if (not_no_man_zone(KEY_RIGHT) && clear_of_own_piece(KEY_RIGHT)) {
		display_move_right_curser();
		if (selected_piece.piece == '9') {
			distance = move_scout_right();
			if (distance == 0) {
				remove_arrows_from_board();
				add_curser_to_board();
				system("CLS");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
				return false;
			}
			else {
				scout_enter = true;
				input = ENTER;
			}
		}
	}

	do {
		if (!scout_enter) {
			input = _getch();
		}
		
		if ((player_turn == 1) && (input == ENTER)) {
			if (board_chip_clear(curser_x_position + distance, curser_y_position)) {
				move_player1_piece_at_curser_position_right(distance);
				display_move_result(1);
				save_move(2);
				add_curser_to_board();
				return true;
			}
			else if (player2_piece_at_location(curser_x_position + distance, curser_y_position)) {
				boardChip player1_piece = get_piece_at_curser_position();
				boardChip player2_piece = get_piece_at_position(curser_x_position + distance, curser_y_position);
				reveal_piece_display_routine(player2_piece);
				winner = determine_winner(player1_piece, player2_piece);
				if (winner == 1) {
					save_move(2);
					remove_piece(player2_piece);
				}
				else if (winner == 2) {
					configure_board_for_player2();
					reveal_piece(player1_piece);
					save_board();
					remove_piece(player1_piece);
				}
				add_curser_to_board();
				move_player1_piece_at_curser_position_right(distance);
				display_move_result(1);
				return true;
			}
			else {
				return false;
			}
		}
		if ((player_turn == 2) && (input == ENTER)) {
			if (board_chip_clear(curser_x_position + distance, curser_y_position)) {
				move_player2_piece_at_curser_position_right(distance);
				display_move_result(2);
				save_move(1);
				add_curser_to_board();
				return true;
			}
			else if (player1_piece_at_location(curser_x_position + distance, curser_y_position)) {
				boardChip player2_piece = get_piece_at_curser_position();
				boardChip player1_piece = get_piece_at_position(curser_x_position + distance, curser_y_position);
				reveal_piece_display_routine(player1_piece);
				invert_arrows();
				winner = determine_winner(player1_piece, player2_piece);
				if (winner == 1) {
					configure_board_for_player1();
					reveal_piece(player2_piece);
					save_board();
					remove_piece(player2_piece);
				}
				else if (winner == 2) {
					save_move(1);
					remove_piece(player1_piece);
				}
				add_curser_to_board();
				move_player2_piece_at_curser_position_right(distance);
				display_move_result(2);
				return true;
			}
			else {
				return false;
			}
		}
	} while ((input != ESC) && (input != ENTER));

	if (input == ESC) {
		add_curser_to_board();
		system("CLS");
		display_board();
		display_player1_out_of_play_pieces();
		display_player2_out_of_play_pieces();
		return false;
	}
}

bool stratego_operations::move_piece_left_routine(boardChip selected_piece) {
	int distance = 1;
	int winner = 0;
	int input = 0;
	bool scout_enter = false;
	if (not_no_man_zone(KEY_LEFT) && clear_of_own_piece(KEY_LEFT)) {
		display_move_left_curser();
		if (selected_piece.piece == '9') {
			distance = move_scout_left();
			if (distance == 0) {
				remove_arrows_from_board();
				add_curser_to_board();
				system("CLS");
				display_board();
				display_player1_out_of_play_pieces();
				display_player2_out_of_play_pieces();
				return false;
			}
			else {
				scout_enter = true;
				input = ENTER;
			}
		}
	}

	do {
		if (!scout_enter) {
			input = _getch();
		}
		
		if ((player_turn == 1) && (input == ENTER)) {
			if (board_chip_clear(curser_x_position - distance, curser_y_position)) {
				move_player1_piece_at_curser_position_left(distance);
				display_move_result(1);
				save_move(2);
				add_curser_to_board();
				return true;
			}
			else if (player2_piece_at_location(curser_x_position - distance, curser_y_position)) {
				boardChip player1_piece = get_piece_at_curser_position();
				boardChip player2_piece = get_piece_at_position(curser_x_position - distance, curser_y_position);
				reveal_piece_display_routine(player2_piece);
				winner = determine_winner(player1_piece, player2_piece);
				if (winner == 1) {
					save_move(2);
					remove_piece(player2_piece);
				}
				else if (winner == 2) {
					configure_board_for_player2();
					reveal_piece(player1_piece);
					save_board();
					remove_piece(player1_piece);
				}
				add_curser_to_board();
				move_player1_piece_at_curser_position_left(distance);
				display_move_result(1);
				return true;
			}
			else {
				return false;
			}
		}
		if ((player_turn == 2) && (input == ENTER)) {
			if (board_chip_clear(curser_x_position - distance, curser_y_position)) {
				move_player2_piece_at_curser_position_left(distance);
				display_move_result(2);
				save_move(1);
				add_curser_to_board();
				return true;
			}
			else if (player1_piece_at_location(curser_x_position - distance, curser_y_position)) {
				boardChip player2_piece = get_piece_at_curser_position();
				boardChip player1_piece = get_piece_at_position(curser_x_position - distance, curser_y_position);
				reveal_piece_display_routine(player1_piece);
				winner = determine_winner(player1_piece, player2_piece);
				if (winner == 1) {
					configure_board_for_player1();
					reveal_piece(player2_piece);
					save_board();
					remove_piece(player2_piece);
				}
				else if (winner == 2) {
					save_move(1);
					remove_piece(player1_piece);
				}
				add_curser_to_board();
				move_player2_piece_at_curser_position_left(distance);
				display_move_result(2);
				return true;
			}
			else {
				return false;
			}
		}
	} while ((input != ESC) && (input != ENTER));

	if (input == ESC) {
		add_curser_to_board();
		system("CLS");
		display_board();
		display_player1_out_of_play_pieces();
		display_player2_out_of_play_pieces();
		return false;
	}
}

void stratego_operations::display_move_up_curser() {
	(board[curser_y_position][curser_x_position])[0] = '^';
	(board[curser_y_position][curser_x_position])[2] = '^';
	system("CLS");
	display_board();
	display_player1_out_of_play_pieces();
	display_player2_out_of_play_pieces();
}

void stratego_operations::display_move_down_curser() {
	(board[curser_y_position][curser_x_position])[0] = 'v';
	(board[curser_y_position][curser_x_position])[2] = 'v';
	system("CLS");
	display_board();
	display_player1_out_of_play_pieces();
	display_player2_out_of_play_pieces();
}

void stratego_operations::display_move_right_curser() {
	(board[curser_y_position][curser_x_position])[0] = '>';
	(board[curser_y_position][curser_x_position])[2] = '>';
	system("CLS");
	display_board();
	display_player1_out_of_play_pieces();
	display_player2_out_of_play_pieces();
}

void stratego_operations::display_move_left_curser() {
	(board[curser_y_position][curser_x_position])[0] = '<';
	(board[curser_y_position][curser_x_position])[2] = '<';
	system("CLS");
	display_board();
	display_player1_out_of_play_pieces();
	display_player2_out_of_play_pieces();
}

void stratego_operations::configure_board_for_player1() {
	hide_player2();
	show_player1();

}

void stratego_operations::configure_board_for_player2() {
	hide_player1();
	show_player2();
}

void stratego_operations::save_move(int player) {
	if (player == 1) {
		configure_board_for_player1();
	}
	else if (player == 2) {
		configure_board_for_player2();
	}
	save_board();
}

void stratego_operations::display_move_result(int player) {
	int input = 0;
	if (player == 1) {
		configure_board_for_player1();
	}
	else if (player == 2) {
		configure_board_for_player2();
	}
	system("CLS");
	display_board();
	cout << "Press enter to end turn." << endl;
	do {
		input = _getch();
	} while (input != ENTER);
}

void stratego_operations::reveal_piece_display_routine(boardChip player_piece) {
	int input = 0;
	reveal_piece(player_piece);
	system("CLS");
	display_board();
	cout << "Press enter to continue." << endl;
	do {
		input = _getch();
	} while (input != ENTER);
}

void stratego_operations::remove_arrows_from_board() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (((board[i][j])[1] == '>') || ((board[i][j])[1] == '<') || ((board[i][j])[1] == 'v') || ((board[i][j])[1] == '^')) {
				(board[i][j])[1] = ' ';
			}
		}
	}
}

bool stratego_operations::clear_of_own_piece(int direction) {
	if (direction == KEY_UP) {
		if (player_turn == 1) {
			return !player1_piece_at_location(curser_x_position, curser_y_position - 1);
		}
		else if (player_turn == 2) {
			return !player2_piece_at_location(curser_x_position, curser_y_position + 1);
		}
	}
	else if (direction == KEY_DOWN) {
		if (player_turn == 1) {
			return !player1_piece_at_location(curser_x_position, curser_y_position + 1);
		}
		else if (player_turn == 2) {
			return !player2_piece_at_location(curser_x_position, curser_y_position - 1);
		}
	}
	else if (direction == KEY_RIGHT) {
		if (player_turn == 1) {
			return !player1_piece_at_location(curser_x_position + 1, curser_y_position);
		}
		else if (player_turn == 2) {
			return !player2_piece_at_location(curser_x_position + 1, curser_y_position);
		}
	}
	else if (direction == KEY_LEFT) {
		if (player_turn == 1) {
			return !player1_piece_at_location(curser_x_position - 1, curser_y_position);
		}
		else if (player_turn == 2) {
			return !player2_piece_at_location(curser_x_position - 1, curser_y_position);
		}
	}
}