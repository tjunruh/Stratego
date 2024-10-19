#include "input_to_logic_interface.h"
#include "ascii_io.h"

input stratego_interface::user_to_logic(int user_input) {
	if (user_input == ascii_io::one) {
		return one;
	}
	else if (user_input == ascii_io::two) {
		return two;
	}
	else if (user_input == ascii_io::three) {
		return three;
	}
	else if (user_input == ascii_io::four) {
		return four;
	}
	else if (user_input == ascii_io::five) {
		return five;
	}
	else if (user_input == ascii_io::six) {
		return six;
	}
	else if (user_input == ascii_io::seven) {
		return seven;
	}
	else if (user_input == ascii_io::eight) {
		return eight;
	}
	else if (user_input == ascii_io::nine) {
		return nine;
	}
	else if (user_input == ascii_io::s) {
		return s;
	}
	else if (user_input == ascii_io::f) {
		return f;
	}
	else if (user_input == ascii_io::b) {
		return b;
	}
	else if (user_input == ascii_io::enter) {
		return enter;
	}
	else if (user_input == ascii_io::q) {
		return q;
	}
	else if (user_input == ascii_io::space) {
		return space;
	}
	else if (user_input == ascii_io::right) {
		return _right;
	}
	else if (user_input == ascii_io::left) {
		return _left;
	}
	else if (user_input == ascii_io::up) {
		return _up;
	}
	else if (user_input == ascii_io::down) {
		return _down;
	}
	else {
		return undefined;
	}
}