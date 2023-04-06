#include <iostream>
#include "game_operations.h"
#include <linux/limits.h>
#include <unistd.h>
#include <ncurses.h>

char end_game = ' ';
int input = 0;
int main()
{
	
	stratego_operations game_manager;
	string home_directory = game_manager.getExePath();
	
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
