#ifndef exception_5435431311
#define exception_5435431311

#include "src/exception_intf.hpp"

struct invalid_board_symbol_counts : exception_intf {
    const char* what() const override { return "invalid_board_symbol_counts"; }
};

struct invalid_player_order : exception_intf {
    const char* what() const override { return "invalid_player_order"; }
};

struct both_players_have_the_same_symbol : exception_intf {
    const char* what() const override { return "both_players_have_the_same_symbol"; }
};

struct player_moves_out_of_turn : exception_intf {
    const char* what() const override { return "player_moves_out_of_turn"; }
};

struct move_to_already_occupied_square : exception_intf {
    const char* what() const override { return "move_to_already_occupied_square"; }
};

struct game_already_won : exception_intf {
    const char* what() const override { return "game_already_won"; }
};

struct both_players_have_winning_line : exception_intf {
    const char* what() const override { return "both_players_have_winning_line"; }
};

struct duplicate_coordinates_in_line : exception_intf {
    const char* what() const override { return "duplicate_coordinates_in_line"; }
};

#endif
