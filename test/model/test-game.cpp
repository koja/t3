#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <map>
#include "src/model/exception.hpp"
#include "src/model/scoring_util.hpp"
#include "test/util.hpp"

BOOST_AUTO_TEST_SUITE(test_game)

BOOST_AUTO_TEST_CASE(test_ctor_throws_invalid_board_symbols_count) {
    struct test_case_template{
        explicit test_case_template(const symbol _symbol) {
            board test_board;
            test_board.add_symbol(col::_a, row::_1, _symbol);
            test_board.add_symbol(col::_b, row::_1, _symbol);
            test_board.add_symbol(col::_c, row::_1, _symbol);
            test_board.add_symbol(col::_a, row::_2, _symbol);

            test_board.add_symbol( col::_b, row::_2, other_symbol(_symbol) );
            test_board.add_symbol( col::_c, row::_2, other_symbol(_symbol) );

            BOOST_CHECK_THROW(
                (
                    game{
                        { player{_symbol}, player{other_symbol(_symbol)} },
                        test_board
                    }
                ),
                invalid_board_symbol_counts
            );
        }
    };

    test_case_template{symbol::x};
    test_case_template{symbol::o};
}

BOOST_AUTO_TEST_CASE(test_ctor_throws_invalid_player_order) {
    struct test_case_template{
        explicit test_case_template(const symbol _symbol) {
            board test_board;
            test_board.add_symbol(col::_a, row::_1, _symbol);
            test_board.add_symbol(col::_b, row::_1, _symbol);
            test_board.add_symbol(col::_c, row::_1, _symbol);

            test_board.add_symbol( col::_a, row::_2, other_symbol(_symbol) );
            test_board.add_symbol( col::_b, row::_2, other_symbol(_symbol) );

            BOOST_CHECK_THROW(
                (
                    game{
                        { player{_symbol}, player{other_symbol(_symbol)} },
                        test_board
                    }
                ),
                invalid_player_order
            );
        }
    };

    test_case_template{symbol::x};
    test_case_template{symbol::o};
}

BOOST_AUTO_TEST_CASE(test_both_players_have_the_same_symbol) {
    struct test_case_template{
        explicit test_case_template(const symbol _symbol) {
            BOOST_CHECK_THROW(
                (
                    game{
                        { player{_symbol}, player{_symbol} },    // <== !!!
                        board{}
                    }
                ),
                both_players_have_the_same_symbol
            );
        }
    };

    test_case_template{symbol::x};
    test_case_template{symbol::o};
}

struct board_with_both_players_winning {
    board test_board;

    board_with_both_players_winning() {
        test_board.add_symbol(col::_a, row::_1, symbol::x);
        test_board.add_symbol(col::_b, row::_1, symbol::o);
        test_board.add_symbol(col::_a, row::_2, symbol::x);
        test_board.add_symbol(col::_b, row::_2, symbol::o);
        test_board.add_symbol(col::_a, row::_3, symbol::x);
        test_board.add_symbol(col::_b, row::_3, symbol::o);
    }
};

BOOST_FIXTURE_TEST_CASE(test_ctor_both_players_have_winning_line, board_with_both_players_winning)
{
    BOOST_CHECK_THROW(
        (
            game{
                { player{symbol::x}, player{symbol::o} },
                test_board
            }
        ),
        both_players_have_winning_line
    );
}

template<symbol SYMBOL> struct has_winning_board {
    board winning_board;

    has_winning_board() {
        winning_board.add_symbol(col::_a, row::_1, SYMBOL);
        winning_board.add_symbol(col::_b, row::_1, other_symbol(SYMBOL) );
        winning_board.add_symbol(col::_a, row::_2, SYMBOL);
        winning_board.add_symbol(col::_b, row::_2, other_symbol(SYMBOL) );
        winning_board.add_symbol(col::_a, row::_3, SYMBOL);
    }
};

BOOST_AUTO_TEST_CASE(test_ctor_winning_board_is_ok)
{
    player player_x{symbol::x};
    player player_o{symbol::o};

    BOOST_CHECK_NO_THROW(
        (
            game{
                { player_o, player_x }, // <== mind the players order
                has_winning_board<symbol::x>{}.winning_board
            }
        )
    );

    BOOST_CHECK_NO_THROW(
        (
            game{
                { player_x, player_o }, // <== mind the players order
                has_winning_board<symbol::o>{}.winning_board
            }
        )
    );
}

/* testing get_current_player() on vanilla board and during few moves */
BOOST_AUTO_TEST_CASE(test_get_current_player) {
    struct test_case_template{
        explicit test_case_template(const symbol _symbol) {
            player player_1{_symbol};
            player player_2{other_symbol(_symbol)};

            game test_game{
                { player_1, player_2 },
                board{}
            };

            BOOST_CHECK( test_game.get_player_to_move_now() == player_1 );

            test_game.make_move( test_game.get_player_to_move_now(), std::make_pair(col::_a, row::_1) );

            BOOST_CHECK( test_game.get_player_to_move_now() == player_2 );

            test_game.make_move( test_game.get_player_to_move_now(), std::make_pair(col::_a, row::_2) );

            BOOST_CHECK( test_game.get_player_to_move_now() == player_1 );

            test_game.make_move( test_game.get_player_to_move_now(), std::make_pair(col::_a, row::_3) );

            BOOST_CHECK( test_game.get_player_to_move_now() == player_2 );
        }
    };

    test_case_template{symbol::x};
    test_case_template{symbol::o};
}

BOOST_AUTO_TEST_CASE(test_make_move_get_board_state_single) {
    struct test_case_template{
        test_case_template(const col c, const row r, const symbol _symbol) {
            game test_game{
                { player{_symbol}, player{other_symbol(_symbol)} },
                board{}
            };
            test_game.make_move( test_game.get_player_to_move_now(), std::make_pair(c, r) );

            board etalon;
            etalon.add_symbol( std::make_pair(c, r), _symbol);

            BOOST_CHECK( equal(etalon, test_game.get_board_state()) );
        }
    };

    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            test_case_template{c, r, symbol::x};
            test_case_template{c, r, symbol::o};
        }
    }
}

BOOST_AUTO_TEST_CASE(test_make_move_out_of_order) {
    struct test_case_template{
        explicit test_case_template(const symbol _symbol) {
            player player_1{_symbol};
            player player_2{other_symbol(_symbol)};

            game test_game{
                { player_1, player_2 },
                board{}
            };
            BOOST_CHECK_THROW(
                test_game.make_move( player_2, std::make_pair(col::_a, row::_1) ),
                player_moves_out_of_turn
            );
            test_game.make_move( player_1, std::make_pair(col::_a, row::_1) );

            BOOST_CHECK_THROW(
                test_game.make_move( player_1, std::make_pair(col::_a, row::_2) ),
                player_moves_out_of_turn
            );
            test_game.make_move( player_2, std::make_pair(col::_a, row::_2) );

            BOOST_CHECK_THROW(
                test_game.make_move( player_2, std::make_pair(col::_a, row::_3) ),
                player_moves_out_of_turn
            );
            test_game.make_move( player_1, std::make_pair(col::_a, row::_3) );
        }
    };

    test_case_template{symbol::x};
    test_case_template{symbol::o};
}

BOOST_AUTO_TEST_CASE(test_make_move_throws_game_already_won)
{
    game test_game_x{
        { player{symbol::o}, player{symbol::x} }, // <== mind the players order
        has_winning_board<symbol::x>{}.winning_board
    };

    BOOST_CHECK_THROW(
        test_game_x.make_move( test_game_x.get_player_to_move_now(), std::make_pair(col::_c, row::_3) ),
        game_already_won
    );

    game test_game_o{
        { player{symbol::x}, player{symbol::o} }, // <== mind the players order
        has_winning_board<symbol::o>{}.winning_board
    };

    BOOST_CHECK_THROW(
        test_game_o.make_move( test_game_o.get_player_to_move_now(), std::make_pair(col::_c, row::_3) ),
        game_already_won
    );
}

BOOST_AUTO_TEST_CASE(test_get_players) {
    struct test_case_template{
        explicit test_case_template(const symbol _symbol) {
            game test_game{
                { player{_symbol}, player{other_symbol(_symbol)} },
                board{}
            };

            const std::array<player, 2> etalon{ player{_symbol}, player{other_symbol(_symbol)} };
            BOOST_CHECK(
                test_game.get_players()
                ==
                etalon
            );
        }
    };

    test_case_template{symbol::x};
    test_case_template{symbol::o};
}

BOOST_AUTO_TEST_CASE(test_get_winner_on_empty_board)
{
    board emptyboard;
    game test_game{
        { player{symbol::x}, player{symbol::o} },
        emptyboard
    };

    BOOST_CHECK( ! test_game.get_winner() );
}

static board prepare_valid_board_with_winning_line(const line& _line, const symbol _symbol) {
    board result;

    /* the line */
    for(const auto& square : _line) {
        result.add_symbol(square, _symbol);
    }

    /* only humble attempt so far */
    int other_symbols_left_to_place = 2;
    /* background */
    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            if(! result.get_symbol(c, r) ) {
                result.add_symbol( c, r, other_symbol(_symbol) );
                --other_symbols_left_to_place;
            }
            if(other_symbols_left_to_place < 1) {
                goto end;
            }
        }
    }

    end:

    return result;
}

BOOST_AUTO_TEST_CASE(test_get_winner_positive)
{
    struct test_case_template{
        test_case_template(const symbol _symbol, const line& ln) {

            player player_1{_symbol};
            player player_2{other_symbol(_symbol)};

            game test_game{
                { player_2, player_1 }, /* reverse order because player_1 just won */
                prepare_valid_board_with_winning_line(ln, _symbol)
            };

            BOOST_CHECK( test_game.get_winner().value() == player_1 );
        }
    };

    for(const line& ln : get_all_scoring_lines()) {
        test_case_template{symbol::x, ln};
        test_case_template{symbol::o, ln};
    }
}

BOOST_AUTO_TEST_CASE(test_is_tie_during_gameplay)
{
    struct test_case_template{
        explicit test_case_template(const symbol _symbol) {
            game test_game{
                { player{_symbol}, player{other_symbol(_symbol)} },
                board{}
            };

            test_game.make_move(player{_symbol}, {col::_b, row::_2} );
            BOOST_CHECK_EQUAL( test_game.is_tie(), false );

            test_game.make_move(player{other_symbol(_symbol)}, {col::_a, row::_1} );
            BOOST_CHECK_EQUAL( test_game.is_tie(), false );

            test_game.make_move(player{_symbol}, {col::_a, row::_3} );
            BOOST_CHECK_EQUAL( test_game.is_tie(), false );

            test_game.make_move(player{other_symbol(_symbol)}, {col::_c, row::_1} );
            BOOST_CHECK_EQUAL( test_game.is_tie(), false );

            test_game.make_move(player{_symbol}, {col::_b, row::_1} );
            BOOST_CHECK_EQUAL( test_game.is_tie(), false );

            test_game.make_move(player{other_symbol(_symbol)}, {col::_b, row::_3} );
            BOOST_CHECK_EQUAL( test_game.is_tie(), false );

            test_game.make_move(player{_symbol}, {col::_c, row::_3} );
            BOOST_CHECK_EQUAL( test_game.is_tie(), false );

            test_game.make_move(player{other_symbol(_symbol)}, {col::_a, row::_2} );
            BOOST_CHECK_EQUAL( test_game.is_tie(), true );
        }
    };

    test_case_template{symbol::x};
    test_case_template{symbol::o};
}

BOOST_AUTO_TEST_CASE(test_is_tie_on_empty_board)
{
    game test_game{
        { player{symbol::x}, player{symbol::o} },
        board{}
    };
    BOOST_CHECK_EQUAL( test_game.is_tie(), false );
}

BOOST_AUTO_TEST_CASE(test_is_tie_on_victory_board)
{
    struct test_case_template{
        explicit test_case_template(const symbol _symbol) {
            game test_game{
                { player{_symbol}, player{other_symbol(_symbol)} },
                board{}
            };

            test_game.make_move(player{_symbol},                {col::_a, row::_1} );
            test_game.make_move(player{other_symbol(_symbol)},  {col::_a, row::_2} );
            test_game.make_move(player{_symbol},                {col::_b, row::_2} );
            test_game.make_move(player{other_symbol(_symbol)},  {col::_a, row::_3} );
            test_game.make_move(player{_symbol},                {col::_c, row::_3} ); /* victory */

            BOOST_CHECK_EQUAL( test_game.is_tie(), false );
        }
    };

    test_case_template{symbol::x};
    test_case_template{symbol::o};
}

BOOST_AUTO_TEST_SUITE_END()
