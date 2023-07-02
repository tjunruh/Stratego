#include "file_managment.h"
#include <fstream>
#include "io.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#include <libloaderapi.h>
#elif __linux__
#include <linux/limits.h>
#include <unistd.h>
#include <sys/stat.h>
#endif
#include <dirent.h>
#include <sys/types.h>

void stratego_file_managment::save_game(std::string file_name, stratego_piece board_info[80], int player_turn, std::string saved_move_shot, std::string player1_name, std::string player2_name) {
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
		content = content + board_info[piece].get_piece() + " ";
		content = content + std::to_string(board_info[piece].get_row()) + " ";
		content = content + std::to_string(board_info[piece].get_column()) + "\n";
	}
	content = content + "#\n";
	content = content + saved_move_shot;
	if (write_file(file_name, content)) {
		stratego_io::print(file_name + " saved!\n");
	}
	else {
		stratego_io::print("Failed to save game.");
	}
}

void stratego_file_managment::load_game(std::string file_name, stratego_piece(&board_info)[80], int& player_turn, std::string& saved_move_shot, std::string& player1_name, std::string& player2_name) {
	std::string content = read_file(file_name);
	if (content == "") {
		stratego_io::print("Could not open the file.\n");
	}
	else {
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
			board_info[piece].set_piece(content[position + 6]);
			board_info[piece].set_row(char_to_int(content[position + 8]));
			board_info[piece].set_column(char_to_int(content[position + 10]));
			piece++;
			position = position + 12;
		}
		position = position + 2;
		saved_move_shot = "";
		while (content[position] != '\0') {
			saved_move_shot = saved_move_shot + content[position];
			position++;
		}
	}
}

bool stratego_file_managment::write_file(std::string file_name, std::string content) {
	bool success = false;
	std::ofstream file(_working_directory + file_name);
	if (file.is_open()) {
		file << content << std::endl;
		success = true;
	}
	else {
		success = false;
	}
	return success;
}

std::string stratego_file_managment::read_file(std::string file_name) {
	std::ifstream file(_working_directory + file_name);
	std::string content;

	if (file.is_open()) {
		char letter[1];
		while (!file.eof()) {
			file.read(letter, 1);
			content = content + letter[0];
		}
		content.erase((content.length() - 2), 2);
		file.close();
	}
	else {
		stratego_io::print("Cannot find file.\n");
		content = "";
	}
	return content;
}

void stratego_file_managment::set_working_directory(std::string exe_path) {
	_working_directory = exe_path + "Saved_Stratego_Games/";
#ifdef __linux__
	struct stat sb;
	if (stat(_working_directory.c_str(), &sb) != 0) {
		char* dirname = "Saved_Stratego_Games/";
		mkdir(dirname, 0777);
	}
#endif
}

std::string stratego_file_managment::get_exe_path_directory() {
#ifdef _WIN32
	char path[MAX_PATH + 1];
	int count = ::GetModuleFileNameA(NULL, path, MAX_PATH);
	return std::string(path, (count > 0) ? count : 0);

#elif __linux__
	char path[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
	return std::string(path, (count > 0) ? count : 0);
#endif
}

void stratego_file_managment::get_saved_game_names(std::vector<std::string>& game_names) {
	game_names.clear();
	DIR* dr;
	struct dirent* en;
	dr = opendir(_working_directory.c_str());
	if (dr) {
		while ((en = readdir(dr)) != NULL) {
			game_names.push_back(en->d_name);
		}
	}
	for (int name = (game_names.size() - 1); name >= 0; name--) {
		if ((game_names[name] == ".") || (game_names[name] == "..")) {
			game_names.erase(game_names.begin() + name);
		}
	}

	closedir(dr);
}

bool stratego_file_managment::duplicate_name(std::string game_name) {
	std::vector<std::string> saved_game_names;
	get_saved_game_names(saved_game_names);
	for (int name = 0; name < saved_game_names.size(); name++) {
		if (saved_game_names[name] == game_name) {
			return true;
		}
	}
	return false;
}

int stratego_file_managment::char_to_int(char _char) {
	return (int(_char - 48));
}

void stratego_file_managment::delete_file(std::string file_name) {
	std::string path = _working_directory + file_name;
	remove(path.c_str());
}
