#pragma once
#include <string>
#include "piece.h"
#include <vector>

class stratego_file_managment {
private:
#ifdef _WIN32
	std::string saved_games_path = "Saved_Stratego_Games\\";
#elif __linux__
	std::string saved_games_path = "Saved_Stratego_Games/";
#endif
public:
	int save_game(std::string file_name, stratego_piece board_info[80], int player_turn, std::string saved_move_shot, std::string player1_name, std::string player2_name);
	int load_game(std::string file_name, stratego_piece(&board_info)[80], int& player_turn, std::string& saved_move_shot, std::string &player1_name, std::string &player2_name);
	int delete_game(std::string file_name);
	void get_saved_game_names(std::vector<std::string> &game_names);
	bool duplicate_name(std::string game_name);
	int char_to_int(char _char);
};