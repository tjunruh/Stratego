#include "game_operations.h"
#include <iostream>

void stratego_game_operations::initialize_file_system() {
    std::string exe_path = file_managment.get_exe_path_directory();
    exe_path.erase(exe_path.length() - 15, 15);
    file_managment.set_working_directory(exe_path);
}

void stratego_game_operations::menu() {
    int input = -1;
    int position = 0;
    display.set_menu_selection(new_game);
    do {
        io.clear();
        display.display_menu();
        input = io.getchar();
        if ((input == UP) && (position > 0)) {
            position--;
        }
        else if ((input == DOWN) && (position < 2)) {
            position++;  
        }

        if (position == 0) {
            display.set_menu_selection(new_game);
        }
        else if (position == 1) {
            display.set_menu_selection(load_game);
        }
        else if (position == 2) {
            display.set_menu_selection(exit_game);
        }
    } while (input != ENTER);
}

void stratego_game_operations::setup() {
    int input = -1;
    logic.reset_board();
    logic.set_game_state(placing_pieces);

    io.clear();
    io.print("Enter your name player 1:\n");
    std::string player_name = "";
    player_name = io.getline();
    display.set_player1_name(player_name);

    io.clear();
    io.print("Enter your name player 2:\n");
    player_name = io.getline();
    display.set_player2_name(player_name);

    do {
        io.clear();
        display.display_player1_preturn_menu();
        input = io.getchar();
        if (input == H) {
            help_menu();
        }
    } while (input != SPACE);

    logic.set_turn(1);
    logic.set_curser_row(9);
    logic.set_curser_column(9);

    do {
        display.orient_for_player(1);
        display.add_pieces_out_of_play();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
        stratego_piece board_info[80];
        logic.get_board_info(board_info);
        io.reset();
        display.display_board(board_info);
        input = io.getchar();
        if ((input == UP) || (input == DOWN) || (input == RIGHT) || (input == LEFT)) {
            logic.move_curser(interface.user_to_logic(input));
        }
        else {
            logic.place_piece(interface.user_to_logic(input));
        }

        if (input == H) {
            help_menu();
        }

    } while (!logic.player1_pieces_placed());

    do {
        io.clear();
        display.display_player2_preturn_menu();
        input = io.getchar();
        if (input == H) {
            help_menu();
        }
    } while (input != SPACE);

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
        io.reset();
        display.display_board(board_info);
        input = io.getchar();
        if ((input == UP) || (input == DOWN) || (input == RIGHT) || (input == LEFT)) {
            logic.move_curser(interface.user_to_logic(input));
        }
        else {
            logic.place_piece(interface.user_to_logic(input));
        }

        if (input == H) {
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
    io.clear();
    do {
        io.reset();
        if (saved_game_names.size() != 0) {
            display.display_load_game_menu(saved_game_names, saved_game_selection);
        }
        input = io.getchar();
        if ((input == UP) && (saved_game_selection > 0)) {
            saved_game_selection--;
        }
        else if ((input == DOWN) && (saved_game_selection < (saved_game_names.size() - 1))) {
            saved_game_selection++;
        }
        else if ((input == ENTER) && (saved_game_names.size() != 0)) {
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
        else if (input == Q) {
            game_loaded = false;
        }
        else if (input == D) {
            file_managment.delete_file(saved_game_names[saved_game_selection]);
            file_managment.get_saved_game_names(saved_game_names);
            io.clear();
        }

        if (input == H) {
            help_menu();
        }
    } while (((input != ENTER) || (saved_game_names.size() == 0)) && (input != Q));
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
        io.reset();
        display.display_board(board_info);

        input = io.getchar();
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
        io.clear();
        io.print(display.get_player1_name() + " won!");
        do {
            input = io.getchar();
        } while (input != ENTER);
    }
    else if (logic.player2_won()) {
        io.clear();
        io.print(display.get_player2_name() + " won!");
        do {
            input = io.getchar();
        } while (input != ENTER);
    }
}

bool stratego_game_operations::game_is_loaded() {
    return game_loaded;
}

menu_options stratego_game_operations::get_menu_selection() {
    return display.get_menu_selection();
}

void stratego_game_operations::end_game() {
    if (logic.player1_won() || logic.player2_won()) {
        stratego_piece board_info[80];
        logic.get_board_info(board_info);
        display.reset();
        display.hide_player2();
        display.orient_for_player(1);
        display.add_pieces_out_of_play();
        io.clear();
        io.print(display.get_player1_name() + "'s pieces:\n");
        display.display_board(board_info);
        int input = -1;
        do {
            input = io.getchar();
        } while (input != ENTER);

        display.hide_player1();
        display.orient_for_player(2);
        display.add_pieces_out_of_play();
        io.clear();
        io.print(display.get_player2_name() + "'s pieces:\n");
        display.display_board(board_info);
        do {
            input = io.getchar();
        } while (input != ENTER);
    }
}

void stratego_game_operations::help_menu() {
    int input = -1;
   
    io.clear();
    display.display_controls();
    do {
        input = io.getchar();
    } while (input != Q);
    io.clear();
}

bool stratego_game_operations::turn_ended_handle() {
    int input = -1;
    if (logic.get_turn() == 1) {
        logic.set_curser_row(2);
        logic.set_curser_column(4);
        do {
            io.clear();
            display.display_player2_preturn_menu();
            input = io.getchar();
            if (input == H) {
                help_menu();
            }
        } while ((input != SPACE) && (input != S));
        if (input == S) {
            save_game_handle();
            return true;
        }
        logic.set_turn(2);
        if (!display.screen_shot_empty()) {
            io.reset();
            display.display_saved_move();
            io.print(display.get_player1_name() + "'s move. Press enter to continue.");
            do {
                input = io.getchar();
            } while (input != ENTER);
        }
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (logic.get_turn() == 2) {
        logic.set_curser_row(7);
        logic.set_curser_column(5);
        do {
            io.clear();
            display.display_player1_preturn_menu();
            input = io.getchar();
            if (input == H) {
                help_menu();
            }
        } while ((input != SPACE) && (input != S));
        if (input == S) {
            save_game_handle();
            return true;
        }
        logic.set_turn(1);
        if (!display.screen_shot_empty()) {
            io.reset();
            display.display_saved_move();
            io.print(display.get_player2_name() + "'s move. Press enter to continue.");
            do {
                input = io.getchar();
            } while (input != ENTER);
        }
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    logic.set_game_state(moving_curser);
    return false;
}

void stratego_game_operations::moving_curser_handle(int input) {
    if ((input == UP) || (input == DOWN) || (input == RIGHT) || (input == LEFT)) {
        logic.move_curser(interface.user_to_logic(input));
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (input == ENTER) {
        logic.select_piece(logic.get_curser_row(), logic.get_curser_column());
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (input == H) {
        help_menu();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::piece_selected_handle(int input) {
    if ((input == UP) || (input == DOWN) || (input == RIGHT) || (input == LEFT) || (input == ENTER) || (input == H)) {
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

        if (input == ENTER) {
            logic.move_piece(interface.user_to_logic(input));
            display.save_move(logic.get_turn(), logic.get_losing_piece_data());
            if (logic.battle()) {
                display.reveal_piece(logic.get_defending_piece_data().get_row(), logic.get_defending_piece_data().get_column());
            }
        }

        if (input == H) {
            help_menu();
        }
    }
    else if (input == Q) {
        logic.unselect_piece();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::scout_selected_handle(int input) {
    if ((input == UP) || (input == DOWN) || (input == RIGHT) || (input == LEFT) || (input == ENTER) || (input == H)) {
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

        if (input == ENTER) {
            display.add_scout_arrows(logic.get_selected_piece_row(), logic.get_selected_piece_column(), logic.get_direction(), logic.get_distance(), logic.get_turn());
            logic.move_piece(interface.user_to_logic(input));
            display.save_move(logic.get_turn(), logic.get_losing_piece_data());
            if (logic.battle()) {
                display.reveal_piece(logic.get_defending_piece_data().get_row(), logic.get_defending_piece_data().get_column());
            }
        }

        if (input == H) {
            help_menu();
        }
    }
    else if (input == Q) {
        logic.unselect_piece();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::move_made_handle(int input) {
    if (input == ENTER) {
        logic.set_game_state(turn_ended);
    }
    else if (input == H) {
        help_menu();
    }
    else {
        display.add_hint();
    }
}

void stratego_game_operations::battling_handle(int input) {
    if (input == ENTER) {
        logic.finalize_move();
        logic.set_game_state(move_made);
    }
    else {
        display.add_hint();
    }
}

void stratego_game_operations::save_game_handle() {
    io.clear();
    io.print("Enter a name:\n");
    std::string game_name = "";
    do {
        game_name = io.getline();
        if (file_managment.duplicate_name(game_name)) {
            io.print("Game already exists. Enter a different name:\n");
        }
    } while (file_managment.duplicate_name(game_name));
    stratego_piece board_info[80];
    logic.get_board_info(board_info);
    file_managment.save_game(game_name, board_info, logic.get_turn(), display.get_screen_shot(), display.get_player1_name(), display.get_player2_name());
    display.reset();
}