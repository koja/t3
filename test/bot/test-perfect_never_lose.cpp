#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/scoped_ptr.hpp>

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "src/model/board.hpp"
#include "src/model/player.hpp"
#include "src/model/scoring_util.hpp"
#include "src/bot/perfect_bot.hpp"
#include "test/bot/util.hpp"

BOOST_AUTO_TEST_SUITE(test_perfect_bot)

struct check_no_lose {
    void operator()(const std::vector<board>& _b_progression, const player& _tested_player_who_just_moved) const {
        game check_game{
            { player{ other_symbol( _tested_player_who_just_moved.get_symbol() ) }, _tested_player_who_just_moved },
            _b_progression.back()
        };

        if( check_game.get_winner() && check_game.get_winner().value() != _tested_player_who_just_moved ) {
            BOOST_ERROR( "\n" + print_board_progression(_b_progression) );
        } else if( check_game.get_winner() && check_game.get_winner().value() == _tested_player_who_just_moved ) {
            BOOST_MESSAGE("victory");
            BOOST_MESSAGE( "\n" + print_board_progression(_b_progression) );
        } else if( check_game.is_tie() ){
            BOOST_MESSAGE("tie");
            BOOST_MESSAGE( "\n" + print_board_progression(_b_progression) );
        }
    }
};

BOOST_AUTO_TEST_CASE(test_never_lose_x)
{
    std::vector<board> b_start{1};
    player testplayer{symbol::x};

    walk_game_tree<perfect_bot>(
        testplayer,
        b_start,
        check_no_lose()
    );
}

BOOST_AUTO_TEST_CASE(test_never_lose_o)
{
    player testplayer{symbol::o};

    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            board board_with_opponent_first_move;
            board_with_opponent_first_move.add_symbol(c, r, other_symbol(testplayer.get_symbol()) );

            std::vector<board> b_start;
            b_start.push_back(board_with_opponent_first_move);

            walk_game_tree<perfect_bot>(
                testplayer,
                b_start,
                check_no_lose()
            );
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
