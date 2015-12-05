#include "src/bot/naive_bot.hpp"

#include <experimental/optional>
using std::experimental::optional;
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <utility>

#include "src/bot/board_util_impl.hpp"
#include "src/bot/basic_moves_impl.hpp"
#include "src/model/player.hpp"
#include "src/model/scoring_util.hpp"
#include "src/bot/exception.hpp"

std::pair<col, row> naive_bot::get_next_move(const game& _game) {
    {
        const optional<std::pair<col, row>> victory = get_imminent_victory_square( _game.get_board_state(), _game.get_player_to_move_now().get_symbol() );
        if(victory) { return victory.value(); }
    }
    {
        /* Hypothetically there might be multiple but we can't do anything better about it apart hoping for the best. */
        const optional<std::pair<col, row>> lose_aversion = get_imminent_lose_aversion_square( _game.get_board_state(), _game.get_player_to_move_now().get_symbol() );
        if(lose_aversion) { return lose_aversion.value(); }
    }
    {   /* Go for center. */
        const std::pair<col, row> center = std::make_pair(col::_b, row::_2);
        if( !_game.get_board_state().get_symbol(center) ) { return center; }
    }
    {
        const optional<std::pair<col, row>> free_corner = get_some_free_corner(_game.get_board_state());
        if(free_corner) { return free_corner.value(); }
    }
    {
        const optional<std::pair<col, row>> free_square =  get_some_free_square(_game.get_board_state());
        if(!free_square) {
            throw board_is_full{};
        } else {
            return free_square.value();
        }
    }

    // This is a safety measure had I messed above. Ignore the eventual compiler warning.
    throw bot_error{};
}

void naive_bot::report_already_occupied_square(const std::pair<col, row>, const game&) {
    throw unknown_error{};
}
