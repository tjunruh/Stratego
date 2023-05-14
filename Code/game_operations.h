#pragma once
#include "display.h"
#include "io.h"
#include "logic.h"
#include "user_input.h"
#include "input_to_logic_interface.h"
#include "file_managment.h"

class stratego_game_operations {
private:
	bool game_loaded;
	stratego_display display;
	stratego_io io;
	stratego_logic logic;
	stratego_interface interface;
	stratego_file_managment file_managment;
public:
	void initialize_file_system();
	void menu();
	void setup();
	void load();
	void game_loop();
	menu_options get_menu_selection();
	bool game_is_loaded();
	void end_game();
	void help_menu();
	bool turn_ended_handle();
	void moving_curser_handle(int input);
	void piece_selected_handle(int input);
	void scout_selected_handle(int input);
	void move_made_handle(int input);
	void battling_handle(int input);
	void save_game_handle();
};