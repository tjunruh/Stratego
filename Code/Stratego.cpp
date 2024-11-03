// StrategoVs2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game_operations.h"
#include <frame.h>
#include <menu.h>
#include <label.h>
#include <ascii_board.h>
#include <controls.h>
#include "default_controls.h"
#ifdef __linux__
#include <unistd.h>
#include <ascii_io.h>
#endif

int main()
{
#ifdef __linux__
    ascii_io::ncurses_init();
#endif
    controls* game_controls = new controls();
    game_controls->load_controls("controls.json");
    for (unsigned int i = 0; i < default_control_names.size(); i++)
    {
        if (game_controls->get_key(default_control_names[i].name) == ascii_io::undefined)
        {
            game_controls->bind(default_control_names[i].name, default_control_names[i].key);
        }
    }
    frame* home_frame = new frame();
    frame* main_frame = new frame();
    frame* multipurpose_frame = new frame();
    stratego_game_operations game_manager(main_frame, multipurpose_frame, game_controls);
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
    initialization_menu.set_controls(game_controls->get_key("select"), game_controls->get_key("up"), game_controls->get_key("down"), game_controls->get_key("quit"));
    if (game_controls->get_key("enable color"))
    {
        home_frame->set_default_foreground_color(game_controls->get_key("foreground color"));
        home_frame->set_default_background_color(game_controls->get_key("background color"));
    }
    ascii_io::hide_cursor();
    do {
        if (game_controls->get_key("enable line drawing"))
        {
            home_frame->enable_dec();
        }
        else
        {
            home_frame->disable_dec();
        }

        if (game_controls->get_key("enable color"))
        {
            home_frame->enable_color();
            home_frame->set_default_background_color(game_controls->get_key("background color"));
            home_frame->set_default_foreground_color(game_controls->get_key("foreground color"));
        }
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
   
    game_controls->save_controls("controls.json");
    delete(home_frame);
    delete(main_frame);
    delete(multipurpose_frame);
    delete(game_controls);
#ifdef __linux__
    ascii_io::ncurses_end();
#endif
}
