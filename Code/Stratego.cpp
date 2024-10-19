// StrategoVs2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game_operations.h"
#include "frame.h"
#include "menu.h"
#include "label.h"
#include "ascii_board.h"
#ifdef __linux__
#include <unistd.h>
#include "ascii_io.h"
#endif

int main()
{
#ifdef __linux__
    ascii_io::ncurses_init();
#endif
    frame* home_frame = new frame();
    frame* main_frame = new frame();
    stratego_game_operations game_manager(main_frame);
    game_manager.initialize_file_system();
    label logo(home_frame);
    logo.set_alignment("center block");
    logo.set_output(game_manager.logo);
    logo.set_spacing(15, 3, 0, 0);
    menu initialization_menu(home_frame, "new line");
    initialization_menu.set_alignment("center block");
    initialization_menu.append_item("New Game");
    initialization_menu.append_item("Load Game");
    initialization_menu.append_item("Exit");
    initialization_menu.disable_quit();
    do {
        home_frame->display();
        std::string selection = "";
        do {
            selection = initialization_menu.get_selection();
            if (selection == "New Game") {
                game_manager.setup();
            }
            else if (selection == "Load Game") {
                game_manager.load();
                if (!game_manager.game_is_loaded())
                {
                    home_frame->display();
                }
            }
        } while ((!game_manager.game_is_loaded() && (selection == "Load Game")));
        if (selection == "Exit") {
            break;
        }
        game_manager.game_loop();
        game_manager.end_game();
    } while (1);
   
    delete(home_frame);
#ifdef __linux__
    ascii_io::ncurses_end();
#endif
}
