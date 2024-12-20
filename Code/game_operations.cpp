#include <ascii_io.h>
#include "game_operations.h"
#include <iostream>
#include <error_codes.h>
#include <file_manager.h>

stratego_game_operations::stratego_game_operations(frame* main_display, frame* multipurpose_display, frame* load_game_display, frame* settings_display, controls* master_game_controls) : display(main_display, multipurpose_display, load_game_display, settings_display, master_game_controls)
{
    game_controls = master_game_controls;
}

void stratego_game_operations::setup() {
    int input = ascii_io::undefined;
    logic.reset_board();
    logic.set_game_state(placing_pieces);
    
    display.display_get_player1_name();
    display.display_get_player2_name();

    do {
        ascii_io::clear();
        display.display_player1_preturn_menu();
        input = ascii_io::getchar();
        if (input == game_controls->get_key("help")) {
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
        display.display_board(board_info);
        input = ascii_io::getchar();
        if ((input == game_controls->get_key("up")) || (input == game_controls->get_key("down")) || (input == game_controls->get_key("right")) || (input == game_controls->get_key("left"))) {
            logic.move_curser(interface.user_to_logic(input, game_controls));
        }
        else {
            logic.place_piece(interface.user_to_logic(input, game_controls));
        }

        if (input == game_controls->get_key("help")) {
            help_menu();
        }

    } while (!logic.player1_pieces_placed());

    do {
        ascii_io::clear();
        display.display_player2_preturn_menu();
        input = ascii_io::getchar();
        if (input == game_controls->get_key("help")) {
            help_menu();
        }
    } while (input != game_controls->get_key("new turn"));

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
        display.display_board(board_info);
        input = ascii_io::getchar();
        if ((input == game_controls->get_key("up")) || (input == game_controls->get_key("down")) || (input == game_controls->get_key("right")) || (input == game_controls->get_key("left"))) {
            logic.move_curser(interface.user_to_logic(input, game_controls));
        }
        else {
            logic.place_piece(interface.user_to_logic(input, game_controls));
        }

        if (input == game_controls->get_key("help")) {
            help_menu();
        }
    } while (!logic.player2_pieces_placed());

    logic.set_game_state(turn_ended);
    display.erase_screen_shot();
}

void stratego_game_operations::load() {
    std::vector<std::string> saved_game_names;
    std::string selection = "";
    int key_stroke = ascii_io::undefined;
    do
    {
        stratego_file_managment::get_saved_game_names(saved_game_names);
        display.display_load_game_menu(saved_game_names, selection, key_stroke);
        if (key_stroke == game_controls->get_key("delete"))
        {
            stratego_file_managment::delete_game(selection);
        }
    } while ((key_stroke != game_controls->get_key("select")) && (key_stroke != game_controls->get_key("quit")));
    

    if (selection != "") {
        stratego_piece board_info[80];
        int player_turn;
        std::string saved_move_shot;
        std::string player1_name;
        std::string player2_name;
        stratego_file_managment::load_game(selection, board_info, player_turn, saved_move_shot, player1_name, player2_name);
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
    else if (selection == "") {
        game_loaded = false;
    }
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
            move_made_handle();
        }
        else if (logic.get_game_state() == battling) {
            battling_handle();
        }
    } while (!logic.player1_won() && !logic.player2_won());
    
    if (logic.player1_won()) {
        display.display_player_won(1);
    }
    else if (logic.player2_won()) {
        display.display_player_won(2);
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
        display.add_heading(display.get_player1_name() + "'s pieces:");
        display.display_board(board_info);
        int input = -1;
        do {
            input = ascii_io::getchar();
        } while (input != game_controls->get_key("finalize"));

        display.hide_player1();
        display.orient_for_player(2);
        display.add_pieces_out_of_play();
        display.add_heading(display.get_player2_name() + "'s pieces:");
        display.display_board(board_info);
        do {
            input = ascii_io::getchar();
        } while (input != game_controls->get_key("finalize"));
    }
}

void stratego_game_operations::help_menu() {
    display.display_set_controls();
}

bool stratego_game_operations::turn_ended_handle() {
    int input = -1;
    if (logic.get_turn() == 1) {
        logic.set_curser_row(2);
        logic.set_curser_column(4);
        do {
            display.display_player2_preturn_menu();
            input = ascii_io::getchar();
            if (input == game_controls->get_key("help")) {
                help_menu();
            }
        } while ((input != game_controls->get_key("new turn")) && (input != game_controls->get_key("save")));
        if (input == game_controls->get_key("save")) {
            save_game_handle();
            return true;
        }
        logic.set_turn(2);
        if (!display.screen_shot_empty()) {
            display.display_saved_move(1);
        }
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (logic.get_turn() == 2) {
        logic.set_curser_row(7);
        logic.set_curser_column(5);
        do {
            display.display_player1_preturn_menu();
            input = ascii_io::getchar();
            if (input == game_controls->get_key("help")) {
                help_menu();
            }
        } while ((input != game_controls->get_key("new turn")) && (input != game_controls->get_key("save")));
        if (input == game_controls->get_key("save")) {
            save_game_handle();
            return true;
        }
        logic.set_turn(1);
        if (!display.screen_shot_empty()) {
            display.display_saved_move(2);
        }
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    logic.set_game_state(moving_curser);
    return false;
}

void stratego_game_operations::moving_curser_handle(int input) {
    if ((input == game_controls->get_key("up")) || (input == game_controls->get_key("down")) || (input == game_controls->get_key("right")) || (input == game_controls->get_key("left"))) {
        logic.move_curser(interface.user_to_logic(input, game_controls));
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (input == game_controls->get_key("select")) {
        logic.select_piece(logic.get_curser_row(), logic.get_curser_column());
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
    else if (input == game_controls->get_key("help")) {
        help_menu();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::piece_selected_handle(int input) {
    if ((input == game_controls->get_key("up")) || (input == game_controls->get_key("down")) || (input == game_controls->get_key("right")) || (input == game_controls->get_key("left")) || (input == game_controls->get_key("finalize")) || (input == game_controls->get_key("help"))) {
        logic.adjust_piece_position(interface.user_to_logic(input, game_controls));
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

        if (input == game_controls->get_key("finalize")) {
            logic.move_piece(interface.user_to_logic(input, game_controls));
            display.save_move(logic.get_turn(), logic.get_losing_piece_data());
            if (logic.battle()) {
                display.reveal_piece(logic.get_defending_piece_data().get_row(), logic.get_defending_piece_data().get_column());
            }
        }

        if (input == game_controls->get_key("help")) {
            help_menu();
        }
    }
    else if (input == game_controls->get_key("quit")) {
        logic.unselect_piece();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::scout_selected_handle(int input) {
    if ((input == game_controls->get_key("up")) || (input == game_controls->get_key("down")) || (input == game_controls->get_key("right")) || (input == game_controls->get_key("left")) || (input == game_controls->get_key("finalize")) || (input == game_controls->get_key("help"))) {
        logic.adjust_scout_position(interface.user_to_logic(input, game_controls));
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

        if (input == game_controls->get_key("finalize")) {
            display.add_scout_arrows(logic.get_selected_piece_row(), logic.get_selected_piece_column(), logic.get_direction(), logic.get_distance(), logic.get_turn());
            logic.move_piece(interface.user_to_logic(input, game_controls));
            display.save_move(logic.get_turn(), logic.get_losing_piece_data());
            if (logic.battle()) {
                display.reveal_piece(logic.get_defending_piece_data().get_row(), logic.get_defending_piece_data().get_column());
            }
        }

        if (input == game_controls->get_key("help")) {
            help_menu();
        }
    }
    else if (input == game_controls->get_key("quit")) {
        logic.unselect_piece();
        display.add_standard_curser(logic.get_curser_row(), logic.get_curser_column());
    }
}

void stratego_game_operations::move_made_handle() {
    logic.set_game_state(turn_ended);
    
}

void stratego_game_operations::battling_handle() {
    logic.finalize_move();
    logic.set_game_state(move_made);
}

void stratego_game_operations::save_game_handle() {
    ascii_io::clear();
    ascii_io::print("Enter a name:\n");
    std::string game_name = "";
    do {
        game_name = display.display_save_game();
    } while (stratego_file_managment::duplicate_name(game_name));
    stratego_piece board_info[80];
    logic.get_board_info(board_info);
    stratego_file_managment::save_game(game_name, board_info, logic.get_turn(), display.get_screen_shot(), display.get_player1_name(), display.get_player2_name());
    display.reset();
}
