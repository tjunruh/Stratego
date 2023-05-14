#pragma once
#include <string>
#include "piece.h"
#include <vector>

class stratego_file_managment {

private:
	std::string _working_directory;
public:
	void save_game(std::string file_name, stratego_piece board_info[80], int player_turn, std::string saved_move_shot, std::string player1_name, std::string player2_name);
	void load_game(std::string file_name, stratego_piece(&board_info)[80], int& player_turn, std::string& saved_move_shot, std::string &player1_name, std::string &player2_name);
	void set_working_directory(std::string exe_path);
	bool write_file(std::string file_name, std::string content);
	std::string read_file(std::string file_name);
	std::string get_exe_path_directory();
	void get_saved_game_names(std::vector<std::string> &game_names);
	bool duplicate_name(std::string game_name);
	int char_to_int(char _char);
	void delete_file(std::string file_name);
};