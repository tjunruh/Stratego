#include "piece.h"

void stratego_piece::set_owner(int owner) {
	_owner = owner;
}

int stratego_piece::get_owner() {
	return _owner;
}

void stratego_piece::set_row(int row) {
	_row = row;
}

int stratego_piece::get_row() {
	return _row;
}

void stratego_piece::set_column(int column) {
	_column = column;
}

int stratego_piece::get_column() {
	return _column;
}

void stratego_piece::set_inPlay(bool inPlay) {
	_inPlay = inPlay;
}

bool stratego_piece::get_inPlay() {
	return _inPlay;
}

void stratego_piece::set_rank(int rank) {
	_rank = rank;
}

int stratego_piece::get_rank() {
	return _rank;
}