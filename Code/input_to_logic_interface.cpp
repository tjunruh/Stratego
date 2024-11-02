#include "input_to_logic_interface.h"
#include "ascii_io.h"

input stratego_interface::user_to_logic(int user_input, controls* game_controls) {
	if (user_input == game_controls->get_key("1")) {
		return one;
	}
	else if (user_input == game_controls->get_key("2")) {
		return two;
	}
	else if (user_input == game_controls->get_key("3")) {
		return three;
	}
	else if (user_input == game_controls->get_key("4")) {
		return four;
	}
	else if (user_input == game_controls->get_key("5")) {
		return five;
	}
	else if (user_input == game_controls->get_key("6")) {
		return six;
	}
	else if (user_input == game_controls->get_key("7")) {
		return seven;
	}
	else if (user_input == game_controls->get_key("8")) {
		return eight;
	}
	else if (user_input == game_controls->get_key("9")) {
		return nine;
	}
	else if (user_input == game_controls->get_key("spy")) {
		return s;
	}
	else if (user_input == game_controls->get_key("flag")) {
		return f;
	}
	else if (user_input == game_controls->get_key("bomb")) {
		return b;
	}
	else if (user_input == game_controls->get_key("select")) {
		return enter;
	}
	else if (user_input == game_controls->get_key("quit")) {
		return q;
	}
	else if (user_input == game_controls->get_key("space")) {
		return space;
	}
	else if (user_input == game_controls->get_key("right")) {
		return _right;
	}
	else if (user_input == game_controls->get_key("left")) {
		return _left;
	}
	else if (user_input == game_controls->get_key("up")) {
		return _up;
	}
	else if (user_input == game_controls->get_key("down")) {
		return _down;
	}
	else {
		return undefined;
	}
}