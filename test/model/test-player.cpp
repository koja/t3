#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "src/model/player.hpp"
#include "test/util.hpp"

BOOST_AUTO_TEST_SUITE(test_player)

BOOST_AUTO_TEST_CASE(test_make_move)
{
    struct test_case_template {
        test_case_template(const col c, const row r, const symbol _symbol) {
            player test_player{_symbol};

            board test_board;
            test_player.make_move( test_board, std::make_pair(c, r) );

            board etalon_board;
            etalon_board.add_symbol(c, r, test_player.get_symbol());

            BOOST_CHECK( equal(test_board, etalon_board) );
        }
    };

    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            test_case_template{c, r, symbol::x};
            test_case_template{c, r, symbol::o};
        }
    }
}

BOOST_AUTO_TEST_CASE(test_get_symbol)
{
    BOOST_CHECK( player{symbol::x}.get_symbol() == symbol::x );
    BOOST_CHECK( player{symbol::o}.get_symbol() == symbol::o );
}

BOOST_AUTO_TEST_SUITE_END()
