#pragma once
#include "display.h"
#include "logic.h"
#include "input_to_logic_interface.h"
#include "file_managment.h"
#include "frame.h"
#include "controls.h"

class stratego_game_operations {
private:
	bool game_loaded;
	stratego_display display;
	stratego_logic logic;
	stratego_interface interface;
	stratego_file_managment file_managment;
	controls game_controls;
	struct control_mapping
	{
		std::string name = "";
		int key = ascii_io::undefined;
	};

	const std::vector<control_mapping> default_control_names =
	{
		{"up", ascii_io::up},
		{"down", ascii_io::down},
		{"right", ascii_io::right},
		{"left", ascii_io::left},
		{"spy", ascii_io::s},
		{"flag", ascii_io::f},
		{"1", ascii_io::one},
		{"2", ascii_io::two},
		{"3", ascii_io::three},
		{"4", ascii_io::four},
		{"5", ascii_io::five},
		{"6", ascii_io::six},
		{"7", ascii_io::seven},
		{"8", ascii_io::eight},
		{"9", ascii_io::nine},
		{"bomb", ascii_io::b},
		{"select", ascii_io::enter},
		{"quit", ascii_io::q},
		{"new turn", ascii_io::space},
		{"finalize", ascii_io::enter},
		{"help", ascii_io::h},
		{"save", ascii_io::s}
	};

public:
	stratego_game_operations(frame* main_display, frame* multipurpose_frame);
	void initialize_file_system();
	void setup();
	void load();
	void game_loop();
	bool game_is_loaded();
	void end_game();
	void help_menu();
	bool turn_ended_handle();
	void moving_curser_handle(int input);
	void piece_selected_handle(int input);
	void scout_selected_handle(int input);
	void move_made_handle();
	void battling_handle();
	void save_game_handle();

	const std::string logo = R"(_____/\\\\\\\\\\\______________________________________________________________________________________________________)"
		"\n"
		R"( ___/\\\/////////\\\____________________________________________________________________________________________________  )"
		"\n"
		R"(  __\//\\\______\///______/\\\_______________________________________/\\\_______________________/\\\\\\\\________________)"
		"\n"
		R"(   ___\////\\\__________/\\\\\\\\\\\__/\\/\\\\\\\___/\\\\\\\\\_____/\\\\\\\\\\\_____/\\\\\\\\___/\\\////\\\_____/\\\\\____)"
		"\n"
		R"(    ______\////\\\______\////\\\////__\/\\\/////\\\_\////////\\\___\////\\\////____/\\\/////\\\_\//\\\\\\\\\___/\\\///\\\__)"
		"\n"
		R"(     _________\////\\\______\/\\\______\/\\\___\///____/\\\\\\\\\\_____\/\\\_______/\\\\\\\\\\\___\///////\\\__/\\\__\//\\\_)"
		"\n"
		R"(      __/\\\______\//\\\_____\/\\\_/\\__\/\\\__________/\\\/////\\\_____\/\\\_/\\__\//\\///////____/\\_____\\\_\//\\\__/\\\__)"
		"\n"
		R"(       _\///\\\\\\\\\\\/______\//\\\\\___\/\\\_________\//\\\\\\\\/\\____\//\\\\\____\//\\\\\\\\\\_\//\\\\\\\\___\///\\\\\/___)"
		"\n"
		R"(        ___\///////////_________\/////____\///___________\////////\//______\/////______\//////////___\////////______\/////_____)";
};
