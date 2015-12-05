#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <sstream>
#include "src/model/coordinates.hpp"
#include "src/model/player.hpp"
#include "src/model/symbol.hpp"
#include "src/ui/cli.hpp"

BOOST_AUTO_TEST_SUITE(test_cli);

BOOST_AUTO_TEST_CASE(test_request_player_type)
{
    std::ostringstream test_output;
    std::istringstream test_input;

    cli test_cli(test_output, test_input);

    test_input.str("c\n");
    BOOST_CHECK( test_cli.request_player_type(symbol::x) == player_type::computer );

    test_input.str("c\n");
    BOOST_CHECK( test_cli.request_player_type(symbol::o) == player_type::computer );

    test_input.str("h\n");
    BOOST_CHECK( test_cli.request_player_type(symbol::x) == player_type::human );

    test_input.str("h\n");
    BOOST_CHECK( test_cli.request_player_type(symbol::o) == player_type::human );

    /* looping until correct value */

    test_input.str("a\nb\nc\n");
    BOOST_CHECK( test_cli.request_player_type(symbol::o) == player_type::computer );

    test_input.str("1\n2\nh\n");
    BOOST_CHECK( test_cli.request_player_type(symbol::x) == player_type::human );
}

BOOST_AUTO_TEST_CASE(test_request_bot_type)
{
    std::ostringstream test_output;
    std::istringstream test_input;

    cli test_cli(test_output, test_input);

    test_input.str("n\n");
    BOOST_CHECK( test_cli.request_bot_type(symbol::x) == bot_type::naive );

    test_input.str("n\n");
    BOOST_CHECK( test_cli.request_bot_type(symbol::o) == bot_type::naive );

    test_input.str("p\n");
    BOOST_CHECK( test_cli.request_bot_type(symbol::x) == bot_type::perfect );

    test_input.str("p\n");
    BOOST_CHECK( test_cli.request_bot_type(symbol::o) == bot_type::perfect );

    /* looping until correct value */

    test_input.str("a\nb\nn\n");
    BOOST_CHECK( test_cli.request_bot_type(symbol::o) == bot_type::naive );

    test_input.str("1\n2\np\n");
    BOOST_CHECK( test_cli.request_bot_type(symbol::x) == bot_type::perfect );
}

struct has_game_instance {
    game test_game;

    has_game_instance()
    :   test_game(
            { player{symbol::x}, player{symbol::o} },
            board{}
        )
    { }
};

struct has_io {
    std::ostringstream test_output;
    std::istringstream test_input;
};

struct has_game_inst_and_io : has_game_instance, has_io {};

BOOST_FIXTURE_TEST_SUITE(tests_in_need_of_game_and_io, has_game_inst_and_io);

BOOST_AUTO_TEST_CASE(test_get_next_move)
{
    cli test_cli(test_output, test_input);

    test_input.str("a1\n");
    BOOST_CHECK( test_cli.get_next_move(test_game) == std::make_pair(col::_a, row::_1) );

    test_input.str("b2\n");
    BOOST_CHECK( test_cli.get_next_move(test_game) == std::make_pair(col::_b, row::_2) );

    test_input.str("c3\n");
    BOOST_CHECK( test_cli.get_next_move(test_game) == std::make_pair(col::_c, row::_3) );

    /* looping until correct value */

    test_input.str("x5\na4\nd1\na1\n");
    BOOST_CHECK( test_cli.get_next_move(test_game) == std::make_pair(col::_a, row::_1) );
}

BOOST_AUTO_TEST_CASE(test_report_invalid_move)
{
    cli test_cli(test_output, test_input);

    BOOST_CHECK_NO_THROW(
        test_cli.report_already_occupied_square(
            std::make_pair(col::_a, row::_1),
            test_game
        )
    );
}

BOOST_AUTO_TEST_CASE(test_setup_players_started)
{
    cli test_cli(test_output, test_input);

    BOOST_CHECK_NO_THROW( test_cli.report_players_setup_started() );
}

BOOST_AUTO_TEST_CASE(test_game_started)
{
    cli test_cli(test_output, test_input);

    BOOST_CHECK_NO_THROW( test_cli.report_game_started(test_game) );
}

BOOST_AUTO_TEST_CASE(test_turn_started)
{
    cli test_cli(test_output, test_input);

    BOOST_CHECK_NO_THROW( test_cli.report_turn_started(test_game) );
}

BOOST_AUTO_TEST_CASE(test_board_was_changed)
{
    cli test_cli(test_output, test_input);

    BOOST_CHECK_NO_THROW( test_cli.report_board_was_changed(test_game) );
}

BOOST_AUTO_TEST_CASE(test_victory)
{
    cli test_cli(test_output, test_input);

    BOOST_CHECK_NO_THROW( test_cli.report_victory(test_game) );
}

BOOST_AUTO_TEST_CASE(test_tie)
{
    cli test_cli(test_output, test_input);

    BOOST_CHECK_NO_THROW( test_cli.report_tie(test_game) );
}

BOOST_AUTO_TEST_CASE(test_error)
{
    cli test_cli(test_output, test_input);

    BOOST_CHECK_NO_THROW( test_cli.report_error("abc") );
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();
