#pragma once
#include <string>
#include "piece.h"
#include <vector>
#include <controls.h>

namespace stratego_file_managment {
#ifdef _WIN32
	const std::string saved_games_path = "Saved_Stratego_Games\\";
	const std::string controls_path = "Stratego_Controls\\";
#elif __linux__
	const std::string saved_games_path = "Saved_Stratego_Games/";
	const std::string controls_path = "Stratego_Controls/";
#endif
	int save_game(std::string file_name, stratego_piece board_info[80], int player_turn, std::string saved_move_shot, std::string player1_name, std::string player2_name);
	int load_game(std::string file_name, stratego_piece(&board_info)[80], int& player_turn, std::string& saved_move_shot, std::string &player1_name, std::string &player2_name);
	int save_controls(std::string file_name, controls* game_controls);
	int load_controls(std::string file_name, controls* game_controls);
	int delete_game(std::string file_name);
	void get_saved_game_names(std::vector<std::string> &game_names);
	bool duplicate_name(std::string game_name);
	int char_to_int(char _char);
};