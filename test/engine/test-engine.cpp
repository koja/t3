#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "src/engine/engine.hpp"
#include "test/mock_ui.hpp"
#include "test/mock_coordinates_provider.hpp"
#include "test/util.hpp"

BOOST_AUTO_TEST_SUITE(test_engine)

struct has_vanilla_game {
    has_vanilla_game()
    :    x_move{col::_a, row::_1},
         o_move{col::_b, row::_2},
        test_engine{
            game{
                { player{symbol::x}, player{symbol::o} },
                board{}
            },
            player_controllers{
                player{symbol::x}, std::shared_ptr<move_coordinates_provider_intf>{ new mock_coordinates_provider{x_move.first, x_move.second} },
                player{symbol::o}, std::shared_ptr<move_coordinates_provider_intf>{ new mock_coordinates_provider{o_move.first, o_move.second} }
            },
            std::shared_ptr<ui_intf>{ new mock_ui }
        }
    { }

    const std::pair<col, row> x_move;
    const std::pair<col, row> o_move;
    engine test_engine;
};

BOOST_FIXTURE_TEST_SUITE(testcases_in_need_of_vanilla_game_fixture, has_vanilla_game)

BOOST_AUTO_TEST_CASE(test_game_state_empty)
{
    BOOST_CHECK( equal( test_engine.get_game_state().get_board_state(), board{} ) );
}

BOOST_AUTO_TEST_CASE(test_play_turn_get_game_state)
{
    board etalon_board;

    test_engine.play_turn();
    etalon_board.add_symbol(x_move, symbol::x);
    BOOST_CHECK( equal( test_engine.get_game_state().get_board_state(), etalon_board ) );

    test_engine.play_turn();
    etalon_board.add_symbol(o_move, symbol::o);
    BOOST_CHECK( equal( test_engine.get_game_state().get_board_state(), etalon_board ) );
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
