// StrategoVs2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game_operations.h"
#ifdef __linux__
#include <unistd.h>
#include <ncurses.h>
#endif

int main()
{
#ifdef __linux__
    initscr();
    raw();
    noecho();
    cbreak();
#endif
    do {
        stratego_game_operations game_manager;
        game_manager.initialize_file_system();
        do {
            game_manager.menu();
            if (game_manager.get_menu_selection() == new_game) {
                game_manager.setup();
            }
            else if (game_manager.get_menu_selection() == load_game) {
                game_manager.load();
            }
        } while ((!game_manager.game_is_loaded() && (game_manager.get_menu_selection() == load_game)));
        if (game_manager.get_menu_selection() == exit_game) {
            break;
        }
        game_manager.game_loop();
        game_manager.end_game();
    } while (1);
   
#ifdef __linux__
    endwin();
#endif
}
