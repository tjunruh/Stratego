#include "input_to_logic_interface.h"
#include "user_input.h"

input stratego_interface::user_to_logic(int user_input) {
	if (user_input == ONE) {
		return one;
	}
	else if (user_input == TWO) {
		return two;
	}
	else if (user_input == THREE) {
		return three;
	}
	else if (user_input == FOUR) {
		return four;
	}
	else if (user_input == FIVE) {
		return five;
	}
	else if (user_input == SIX) {
		return six;
	}
	else if (user_input == SEVEN) {
		return seven;
	}
	else if (user_input == EIGHT) {
		return eight;
	}
	else if (user_input == NINE) {
		return nine;
	}
	else if (user_input == S) {
		return s;
	}
	else if (user_input == F) {
		return f;
	}
	else if (user_input == B) {
		return b;
	}
	else if (user_input == ENTER) {
		return enter;
	}
	else if (user_input == Q) {
		return q;
	}
	else if (user_input == SPACE) {
		return space;
	}
	else if (user_input == RIGHT) {
		return _right;
	}
	else if (user_input == LEFT) {
		return _left;
	}
	else if (user_input == UP) {
		return _up;
	}
	else if (user_input == DOWN) {
		return _down;
	}
}