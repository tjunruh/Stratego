#pragma once

class stratego_piece {
private:
	int _owner;
	char _piece;
	int _row;
	int _column;
	bool _inPlay;
	int _rank;

public:
	void set_owner(int owner);
	int get_owner();
	void set_row(int row);
	int get_row();
	void set_column(int column);
	int get_column();
	void set_inPlay(bool inPlay);
	bool get_inPlay();
	void set_rank(int rank);
	int get_rank();
};