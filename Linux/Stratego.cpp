#include <iostream>
#include "game_operations.h"
#include <linux/limits.h>
#include <unistd.h>
#include <ncurses.h>
//#include <conio.h>
//#include <tchar.h>
//#include <locale>
//#include <codecvt>

//#ifndef UNICODE  
//typedef std::string String;
//#else
//typedef std::wstring String;
//#endif

char end_game = ' ';
int input = 0;
int main()
{
	//using convert_type = std::codecvt_utf8<wchar_t>;
	//std::wstring_convert<convert_type, wchar_t> converter;
	//String home_directory_to_convert = argv[0];
	//string home_directory = converter.to_bytes(home_directory_to_convert);
	//home_directory.erase(home_directory.length() - 12, 12);
	
	stratego_operations game_manager;
	string home_directory = game_manager.getExePath();
	//home_directory.erase(home_directory.length() - 12, 12);
	
	bool new_game = false;
	
	game_manager.initialize_game_saver(home_directory);
	
	initscr();
	raw();
	noecho();
	cbreak();
	
	while (end_game != 'n') {
		game_manager.initialize_player1_pieces();
		game_manager.initialize_player2_pieces();
		game_manager.initialize_board();
		game_manager.initialize_saved_board();
		end_game = ' ';
		new_game = game_manager.menu_loop();
		if (new_game) {
			game_manager.game_setup_loop();
			//game_manager.fill_board();
		}
		game_manager.game_loop();
		erase();
		while ((end_game != 'n') && (end_game != 'y')) {
			printw("Play again? Type y or n.");
			end_game = getch();
		}
	}
	
	endwin();
	
	return 0;
}
