#pragma once
#include "logic_input.h"
#include "controls.h"


class stratego_interface {

private:
	controls _game_controls;
public:
	input user_to_logic(int user_input, controls* game_controls);
};