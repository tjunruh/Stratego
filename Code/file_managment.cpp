#include "file_managment.h"
#include <file_manager.h>
#include <ascii_io.h>
#include <filesystem>

int stratego_file_managment::save_game(std::string file_name, stratego_piece board_info[80], int player_turn, std::string saved_move_shot, std::string player1_name, std::string player2_name) {
	std::string content = "";
	content = content + player1_name + "\n";
	content = content + player2_name + "\n";
	content = content + std::to_string(player_turn) + "\n";
	for (int piece = 0; piece < 80; piece++) {
		if (board_info[piece].get_inPlay() == true) {
			content = content + "1 ";
		}
		else if (board_info[piece].get_inPlay() == false) {
			content = content + "0 ";
		}
		content = content + std::to_string(board_info[piece].get_owner()) + " ";
		if (board_info[piece].get_rank() == -1) {
			content = content + "a ";
		}
		else if (board_info[piece].get_rank() == -2) {
			content = content + "b ";
		}
		else {
			content = content + std::to_string(board_info[piece].get_rank()) + " ";
		}
		content = content + std::to_string(board_info[piece].get_row()) + " ";
		content = content + std::to_string(board_info[piece].get_column()) + "\n";
	}
	content = content + "#\n";
	content = content + saved_move_shot;
	int status = file_manager::write_file(saved_games_path + file_name, content);
	return status;
}

int stratego_file_managment::load_game(std::string file_name, stratego_piece(&board_info)[80], int& player_turn, std::string& saved_move_shot, std::string& player1_name, std::string& player2_name) {
	std::string content = "";
		
	int status = file_manager::read_file(saved_games_path + file_name, content);
	if (status == 0) {
		int position = 0;
		player1_name = "";
		player2_name = "";
		saved_move_shot = "";
		while (content[position] != '\n') {
			player1_name = player1_name + content[position];
			position++;
		}
		position++;
		while (content[position] != '\n') {
			player2_name = player2_name + content[position];
			position++;
		}
		position++;

		player_turn = char_to_int(content[position]);

		position++;
		position++;

		int piece = 0;
		while (content[position] != '#') {
			if (content[position] == '1') {
				board_info[piece].set_inPlay(true);
			}
			else if (content[position] == '0') {
				board_info[piece].set_inPlay(false);
			}
			board_info[piece].set_owner(char_to_int(content[position + 2]));
			if (content[position + 4] == 'a') {
				board_info[piece].set_rank(-1);
			}
			else if (content[position + 4] == 'b') {
				board_info[piece].set_rank(-2);
			}
			else {
				board_info[piece].set_rank(char_to_int(content[position + 4]));
			}
			board_info[piece].set_row(char_to_int(content[position + 6]));
			board_info[piece].set_column(char_to_int(content[position + 8]));
			piece++;
			position = position + 10;
		}
		position = position + 2;
		saved_move_shot = "";
		while (content[position] != '\0') {
			saved_move_shot = saved_move_shot + content[position];
			position++;
		}
	}
	return status;
}

int stratego_file_managment::save_controls(std::string file_name, controls* game_controls)
{
	if (!std::filesystem::exists(controls_path))
	{
		std::filesystem::create_directory(controls_path);
	}

	int status = game_controls->save_controls(controls_path + file_name);
	return status;
}

int stratego_file_managment::load_controls(std::string file_name, controls* game_controls)
{
	if (!std::filesystem::exists(controls_path))
	{
		std::filesystem::create_directory(controls_path);
	}

	int status = game_controls->load_controls(controls_path + file_name);
	return status;
}

int stratego_file_managment::delete_game(std::string file_name)
{
	int status = file_manager::delete_file(saved_games_path + file_name);
	return status;
}

void stratego_file_managment::get_saved_game_names(std::vector<std::string>& game_names) {
	game_names.clear();
	if (!std::filesystem::exists(saved_games_path))
	{
		std::filesystem::create_directory(saved_games_path);
	}

	for (const auto& entry : std::filesystem::directory_iterator(saved_games_path))
	{
		game_names.push_back(file_manager::extract_file(entry.path().string()));
	}

	for (int name = (game_names.size() - 1); name >= 0; name--) {
		if ((game_names[name] == ".") || (game_names[name] == "..")) {
			game_names.erase(game_names.begin() + name);
		}
	}
}

bool stratego_file_managment::duplicate_name(std::string game_name) {
	std::vector<std::string> saved_game_names;
	get_saved_game_names(saved_game_names);
	for (unsigned int name = 0; name < saved_game_names.size(); name++) {
		if (saved_game_names[name] == game_name) {
			return true;
		}
	}
	return false;
}

int stratego_file_managment::char_to_int(char _char) {
	return (int(_char - 48));
}
