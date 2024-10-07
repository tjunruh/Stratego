#include "ascii_io.h"
#include "game_operations.h"
#include <iostream>

void stratego_game_operations::initialize_file_system() {
    std::string exe_path = file_managment.get_exe_path_directory();
#ifdef _WIN32
    while (exe_path[exe_path.length() - 1] != '\\') {
        exe_path.erase(exe_path.length() - 1, 1);
    }
#elif __linux__
    while (exe_path[exe_path.length() - 1] != '/') {
        exe_path.erase(exe_path.length() - 1, 1);
    }
#endif
    
    file_managment.set_working_directory(exe_path);
}

void stratego_game_operations::setup() {
    int input = -1;
    logic.reset_board();
    logic.set_game_state(placing_pieces);

    ascii_io::clear();
    ascii_io::print("Enter your name player 1:\n");
    std::string player_name = "";
    player_name = ascii_io::getline();
    display.set_player1_name(player_name);

    ascii_io::clear();
    ascii_io::print("Enter your name player 2:\n");
    player_name = ascii_io::getline();
    display.set_player2_name(player_name);

    do {
        ascii_io::clear();
        display.display_player1_preturn_menu();
        input = ascii_io::getchar();
        if (input == ascii_io::h) {
            help_menu();
        }
    } while (input != ascii_io::space);

    logic.set_turn(1);
    logic.set_curser_row(9);
    logic.set_curser_column(9);

    do {
        display.orient_for_player(1);
        display.add_pieces_out_of_play();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
        stratego_piece board_info[80];
        logic.get_board_info(board_info);
        ascii_io::move_cursor_to_position(0, 0);
        display.display_board(board_info);
        input = ascii_io::getchar();
        if ((input == ascii_io::up) || (input == ascii_io::down) || (input == ascii_io::right) || (input == ascii_io::left)) {
            logic.move_curser(interface.user_to_logic(input));
        }
        else {
            logic.place_piece(interface.user_to_logic(input));
        }

        if (input == ascii_io::h) {
            help_menu();
        }

    } while (!logic.player1_pieces_placed());

    do {
        ascii_io::clear();
        display.display_player2_preturn_menu();
        input = ascii_io::getchar();
        if (input == ascii_io::h) {
            help_menu();
        }
    } while (input != ascii_io::space);

    logic.set_turn(2);
    logic.set_curser_row(0);
    logic.set_curser_column(0);

    do {
        display.orient_for_player(2);
        display.add_pieces_out_of_play();
        display.hide_player1();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
        stratego_piece board_info[80];
        logic.get_board_info(board_info);
        ascii_io::move_cursor_to_position(0, 0);
        display.display_board(board_info);
        input = ascii_io::getchar();
        if ((input == ascii_io::up) || (input == ascii_io::down) || (input == ascii_io::right) || (input == ascii_io::left)) {
            logic.move_curser(interface.user_to_logic(input));
        }
        else {
            logic.place_piece(interface.user_to_logic(input));
        }

        if (input == ascii_io::h) {
            help_menu();
        }
    } while (!logic.player2_pieces_placed());

    logic.set_game_state(turn_ended);
}

void stratego_game_operations::load() {
    int input = -1;
    std::vector<std::string> saved_game_names;
    file_managment.get_saved_game_names(saved_game_names);
    int saved_game_selection = 0;
    ascii_io::clear();
    do {
        ascii_io::move_cursor_to_position(0, 0);
        if (saved_game_names.size() != 0) {
            display.display_load_game_menu(saved_game_names, saved_game_selection);
        }
        input = ascii_io::getchar();
        if ((input == ascii_io::up) && (saved_game_selection > 0)) {
            saved_game_selection--;
        }
        else if ((input == ascii_io::down) && (saved_game_selection < (saved_game_names.size() - 1))) {
            saved_game_selection++;
        }
        else if ((input == ascii_io::enter) && (saved_game_names.size() != 0)) {
            stratego_piece board_info[80];
            int player_turn;
            std::string saved_move_shot;
            std::string player1_name;
            std::string player2_name;
            file_managment.load_game(saved_game_names[saved_game_selection], board_info, player_turn, saved_move_shot, player1_name, player2_name);
            logic.reset_board();
            display.reset();
            logic.set_board_info(board_info);
            logic.set_turn(player_turn);
            display.set_screen_shot(saved_move_shot);
            display.set_player1_name(player1_name);
            display.set_player2_name(player2_name);
            game_loaded = true;
            logic.set_game_state(turn_ended);
        }
        else if (input == ascii_io::q) {
            game_loaded = false;
        }
        else if (input == ascii_io::q) {
            file_managment.delete_file(saved_game_names[saved_game_selection]);
            file_managment.get_saved_game_names(saved_game_names);
            ascii_io::clear();
        }

        if (input == ascii_io::h) {
            help_menu();
        }
    } while (((input != ascii_io::enter) || (saved_game_names.size() == 0)) && (input != ascii_io::q));
}

void stratego_game_operations::game_loop() {
    int input = -1;
    do {
        if (logic.get_game_state() == turn_ended) {
            bool game_saved = turn_ended_handle();
            if (game_saved) {
                break;
            }
        }

        stratego_piece board_info[80];
        logic.get_board_info(board_info);
        if (logic.get_turn() == 1) {
            display.orient_for_player(1);
            display.hide_player2();
        }
        else if (logic.get_turn() == 2) {
            display.orient_for_player(2);
            display.hide_player1();
        }
        display.add_pieces_out_of_play();
        ascii_io::move_cursor_to_position(0, 0);
        display.display_board(board_info);

        input = ascii_io::getchar();
        if (logic.get_game_state() == moving_curser) {
            moving_curser_handle(input);
        }
        else if (logic.get_game_state() == piece_selected) {
            piece_selected_handle(input);
        }
        else if (logic.get_game_state() == scout_selected) {
            scout_selected_handle(input);
        }
        else if (logic.get_game_state() == move_made) {
            move_made_handle(input);
        }
        else if (logic.get_game_state() == battling) {
            battling_handle(input);
        }
    } while (!logic.player1_won() && !logic.player2_won());
    
    if (logic.player1_won()) {
        ascii_io::clear();
        ascii_io::print(display.get_player1_name() + " won!");
        do {
            input = ascii_io::getchar();
        } while (input != ascii_io::enter);
    }
    else if (logic.player2_won()) {
        ascii_io::clear();
        ascii_io::print(display.get_player2_name() + " won!");
        do {
            input = ascii_io::getchar();
        } while (input != ascii_io::enter);
    }
}

bool stratego_game_operations::game_is_loaded() {
    return game_loaded;
}

void stratego_game_operations::end_game() {
    if (logic.player1_won() || logic.player2_won()) {
        stratego_piece board_info[80];
        logic.get_board_info(board_info);
        display.reset();
        display.hide_player2();
        display.orient_for_player(1);
        display.add_pieces_out_of_play();
        ascii_io::clear();
        ascii_io::print(display.get_player1_name() + "'s pieces:\n");
        display.display_board(board_info);
        int input = -1;
        do {
            input = ascii_io::getchar();
        } while (input != ascii_io::enter);

        display.hide_player1();
        display.orient_for_player(2);
        display.add_pieces_out_of_play();
        ascii_io::clear();
        ascii_io::print(display.get_player2_name() + "'s pieces:\n");
        display.display_board(board_info);
        do {
            input = ascii_io::getchar();
        } while (input != ascii_io::enter);
    }
}

void stratego_game_operations::help_menu() {
    int input = -1;
   
    ascii_io::clear();
    display.display_controls();
    do {
        input = ascii_io::getchar();
    } while (input != ascii_io::q);
    ascii_io::clear();
}

bool stratego_game_operations::turn_ended_handle() {
    int input = -1;
    if (logic.get_turn() == 1) {
        logic.set_curser_row(2);
        logic.set_curser_column(4);
        do {
            ascii_io::clear();
            display.display_player2_preturn_menu();
            input = ascii_io::getchar();
            if (input == ascii_io::h) {
                help_menu();
            }
        } while ((input != ascii_io::space) && (input != ascii_io::s));
        if (input == ascii_io::s) {
            save_game_handle();
            return true;
        }
        logic.set_turn(2);
        if (!display.screen_shot_empty()) {
            ascii_io::move_cursor_to_position(0, 0);
            display.display_saved_move();
            ascii_io::print(display.get_player1_name() + "'s move. Press enter to continue.");
            do {
                input = ascii_io::getchar();
            } while (input != ascii_io::enter);
        }
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (logic.get_turn() == 2) {
        logic.set_curser_row(7);
        logic.set_curser_column(5);
        do {
            ascii_io::clear();
            display.display_player1_preturn_menu();
            input = ascii_io::getchar();
            if (input == ascii_io::h) {
                help_menu();
            }
        } while ((input != ascii_io::space) && (input != ascii_io::s));
        if (input == ascii_io::s) {
            save_game_handle();
            return true;
        }
        logic.set_turn(1);
        if (!display.screen_shot_empty()) {
            ascii_io::move_cursor_to_position(0, 0);
            display.display_saved_move();
            ascii_io::print(display.get_player2_name() + "'s move. Press enter to continue.");
            do {
                input = ascii_io::getchar();
            } while (input != ascii_io::enter);
        }
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    logic.set_game_state(moving_curser);
    return false;
}

void stratego_game_operations::moving_curser_handle(int input) {
    if ((input == ascii_io::up) || (input == ascii_io::down) || (input == ascii_io::right) || (input == ascii_io::left)) {
        logic.move_curser(interface.user_to_logic(input));
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (input == ascii_io::enter) {
        logic.select_piece(logic.get_curser_row(), logic.get_curser_column());
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (input == ascii_io::h) {
        help_menu();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::piece_selected_handle(int input) {
    if ((input == ascii_io::up) || (input == ascii_io::down) || (input == ascii_io::right) || (input == ascii_io::left) || (input == ascii_io::enter) || (input == ascii_io::h)) {
        logic.adjust_piece_position(interface.user_to_logic(input));
        if (logic.get_direction() == neutral) {
            display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
        }
        else if (logic.get_direction() == right) {
            display.add_move_right_curser(logic.get_curser_row(), logic.get_curser_column());
        }
        else if (logic.get_direction() == left) {
            display.add_move_left_curser(logic.get_curser_row(), logic.get_curser_column());
        }
        else if (logic.get_direction() == up) {
            display.add_move_up_curser(logic.get_curser_row(), logic.get_curser_column());
        }
        else if (logic.get_direction() == down) {
            display.add_move_down_curser(logic.get_curser_row(), logic.get_curser_column());
        }

        if (input == ascii_io::enter) {
            logic.move_piece(interface.user_to_logic(input));
            display.save_move(logic.get_turn(), logic.get_losing_piece_data());
            if (logic.battle()) {
                display.reveal_piece(logic.get_defending_piece_data().get_row(), logic.get_defending_piece_data().get_column());
            }
        }

        if (input == ascii_io::h) {
            help_menu();
        }
    }
    else if (input == ascii_io::q) {
        logic.unselect_piece();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::scout_selected_handle(int input) {
    if ((input == ascii_io::up) || (input == ascii_io::down) || (input == ascii_io::right) || (input == ascii_io::left) || (input == ascii_io::enter) || (input == ascii_io::h)) {
        logic.adjust_scout_position(interface.user_to_logic(input));
        if (logic.get_direction() == neutral) {
            display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
        }
        else if (logic.get_direction() == right) {
            display.add_move_right_curser(logic.get_curser_row(), logic.get_curser_column());
            display.add_scout_arrows(logic.get_selected_piece_row(), logic.get_selected_piece_column(), logic.get_direction(), logic.get_distance(), logic.get_turn());
        }
        else if (logic.get_direction() == left) {
            display.add_move_left_curser(logic.get_curser_row(), logic.get_curser_column());
            display.add_scout_arrows(logic.get_selected_piece_row(), logic.get_selected_piece_column(), logic.get_direction(), logic.get_distance(), logic.get_turn());
        }
        else if (logic.get_direction() == up) {
            display.add_move_up_curser(logic.get_curser_row(), logic.get_curser_column());
            display.add_scout_arrows(logic.get_selected_piece_row(), logic.get_selected_piece_column(), logic.get_direction(), logic.get_distance(), logic.get_turn());
        }
        else if (logic.get_direction() == down) {
            display.add_move_down_curser(logic.get_curser_row(), logic.get_curser_column());
            display.add_scout_arrows(logic.get_selected_piece_row(), logic.get_selected_piece_column(), logic.get_direction(), logic.get_distance(), logic.get_turn());
        }

        if (input == ascii_io::enter) {
            display.add_scout_arrows(logic.get_selected_piece_row(), logic.get_selected_piece_column(), logic.get_direction(), logic.get_distance(), logic.get_turn());
            logic.move_piece(interface.user_to_logic(input));
            display.save_move(logic.get_turn(), logic.get_losing_piece_data());
            if (logic.battle()) {
                display.reveal_piece(logic.get_defending_piece_data().get_row(), logic.get_defending_piece_data().get_column());
            }
        }

        if (input == ascii_io::h) {
            help_menu();
        }
    }
    else if (input == ascii_io::q) {
        logic.unselect_piece();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::move_made_handle(int input) {
    if (input == ascii_io::enter) {
        logic.set_game_state(turn_ended);
    }
    else if (input == ascii_io::h) {
        help_menu();
    }
    else {
        display.add_hint();
    }
}

void stratego_game_operations::battling_handle(int input) {
    if (input == ascii_io::enter) {
        logic.finalize_move();
        logic.set_game_state(move_made);
    }
    else {
        display.add_hint();
    }
}

void stratego_game_operations::save_game_handle() {
    ascii_io::clear();
    ascii_io::print("Enter a name:\n");
    std::string game_name = "";
    do {
        game_name = ascii_io::getline();
        if (file_managment.duplicate_name(game_name)) {
            ascii_io::print("Game already exists. Enter a different name:\n");
        }
    } while (file_managment.duplicate_name(game_name));
    stratego_piece board_info[80];
    logic.get_board_info(board_info);
    file_managment.save_game(game_name, board_info, logic.get_turn(), display.get_screen_shot(), display.get_player1_name(), display.get_player2_name());
    display.reset();
}
