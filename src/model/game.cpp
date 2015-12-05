#include "src/model/game.hpp"

#include <cstdlib>  // abs()

#include "src/model/exception.hpp"
#include "src/model/line.hpp"
#include "src/model/scoring_util.hpp"

static bool is_victory_impl(const board& _board, const symbol _symbol) {

    for( const line& scoring_line : get_all_scoring_lines() ) {
        if( count_symbols_on_line(_board, scoring_line).at(_symbol) == 3) {
            return true;
        }
    }

    return false;
}

game::game(
    const std::array<player, 2>& _players_init,
    const board& _board_init
) :
    players_{_players_init.at(0), _players_init.at(1)},
    current_player_{players_.begin()},
    board_{_board_init}
{
    if( players_.at(0).get_symbol() == players_.at(1).get_symbol() ) {
        throw both_players_have_the_same_symbol{};
    }

    if(
        is_victory_impl(board_, players_.at(0).get_symbol() )
        &&
        is_victory_impl(board_, players_.at(1).get_symbol() )
    ) {
        throw both_players_have_winning_line{};
    }

    {
        int x_o_diff = 0;

        for( const col c : get_ordered_col_values() ) {
            for( const row r : get_ordered_row_values() ) {
                const optional<symbol> curr_symbol = board_.get_symbol(c, r);
                if(curr_symbol) {
                    curr_symbol.value() == symbol::x
                        ?   ++x_o_diff
                        :   --x_o_diff;
                }
            }
        }

        if(abs(x_o_diff) > 1) {
            throw invalid_board_symbol_counts{};
        } else if(
            ( current_player_->get_symbol() == symbol::x && x_o_diff > 0 )
            ||
            ( current_player_->get_symbol() == symbol::o && x_o_diff < 0 )
        ) { throw invalid_player_order{}; }
    }

}

player game::get_player_to_move_now() const { return *current_player_; }

void game::make_move(const player& _player, const std::pair<col, row> _coordinates) {
    if(_player != *current_player_) {
        throw player_moves_out_of_turn{};
    }

    if( get_winner() ) {
        throw game_already_won{};
    }

    current_player_->make_move(board_, _coordinates);

    if( *current_player_ == players_.at(0) ) {
        current_player_ = &players_.at(1);
    } else {
        current_player_ = &players_.at(0);
    }
}

board game::get_board_state() const { return board_; }

std::array<player, 2> game::get_players() const { return players_; }

optional<player> game::get_winner() const {
    bool victory_0 = is_victory_impl(board_, players_.at(0).get_symbol() );
    bool victory_1 = is_victory_impl(board_, players_.at(1).get_symbol() );

    if(victory_0 && victory_1) { throw both_players_have_winning_line{}; }

    return
        victory_0
        ?   players_.at(0)
        :   victory_1
            ?   players_.at(1)
            :   optional<player>{};
}

bool game::is_tie() const {

    if( get_winner() ) { return false; }

    // if there is any scoring line occupied by only one of players left it is not a tie
    for( const line& ln : get_all_scoring_lines() ) {
        const std::map<symbol, unsigned> symbol_count = count_symbols_on_line(board_, ln);
        if( symbol_count.at(symbol::x) == 0 || symbol_count.at(symbol::o) == 0 ) { return false; }
    }

    return true;
}
