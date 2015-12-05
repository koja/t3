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
#include "src/bot/naive_bot.hpp"
#include "test/bot/util.hpp"

BOOST_AUTO_TEST_SUITE(test_naive_bot)

BOOST_AUTO_TEST_CASE(test_never_throw_x)
{
    std::vector<board> b_start{1};
    player testplayer{symbol::x};
    BOOST_CHECK_NO_THROW(
        walk_game_tree<naive_bot>(
            testplayer,
            b_start,
            [](const std::vector<board>&, const player&){} /* AKA do-nothing */
        )
    );
}

BOOST_AUTO_TEST_CASE(test_never_throw_o)
{
    player testplayer{symbol::o};

    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            board board_with_opponent_first_move;
            board_with_opponent_first_move.add_symbol(c, r, other_symbol(testplayer.get_symbol()) );

            std::vector<board> b_start;
            b_start.push_back(board_with_opponent_first_move);

            BOOST_CHECK_NO_THROW(
                walk_game_tree<naive_bot>(
                    testplayer,
                    b_start,
                    [](const std::vector<board>&, const player&){} /* AKA do-nothing */
                )
            );
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
