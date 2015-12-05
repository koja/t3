#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "src/model/board.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/exception.hpp"
#include "test/util.hpp"

BOOST_AUTO_TEST_SUITE(test_board)

BOOST_AUTO_TEST_CASE(test_add_symbol_get_symbol) {
    struct test_case_template{
        test_case_template(const col c, const row r, const symbol _symbol) {
            {
                board test_board;
                test_board.add_symbol(c, r, _symbol);
                BOOST_CHECK_EQUAL(test_board.get_symbol(c, r), _symbol);
                BOOST_CHECK_EQUAL(test_board.get_symbol(std::make_pair(c, r)), _symbol);
            }
            {
                board test_board;
                test_board.add_symbol(std::make_pair(c, r), _symbol);
                BOOST_CHECK_EQUAL(test_board.get_symbol(c, r), _symbol);
                BOOST_CHECK_EQUAL(test_board.get_symbol(std::make_pair(c, r)), _symbol);
            }
        }
    };

    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            test_case_template{c, r, symbol::x};
            test_case_template{c, r, symbol::o};
        }
    }
}

BOOST_AUTO_TEST_CASE(test_add_symbol_invalid_move_already_occupied) {
    struct test_case_template{
        test_case_template(const col c, const row r, const symbol _symbol) {
            board test_board;
            test_board.add_symbol(c, r, _symbol);

            BOOST_CHECK_THROW(
                test_board.add_symbol(c, r, _symbol),
                move_to_already_occupied_square
            );
            BOOST_CHECK_THROW(
                test_board.add_symbol(std::make_pair(c, r), _symbol),
                move_to_already_occupied_square
            );
            BOOST_CHECK_THROW(
                test_board.add_symbol(c, r, other_symbol(_symbol)),
                move_to_already_occupied_square
            );
            BOOST_CHECK_THROW(
                test_board.add_symbol(std::make_pair(c, r), other_symbol(_symbol)),
                move_to_already_occupied_square
            );
            /* square symbol remained unchanged */
            BOOST_CHECK_EQUAL(
                test_board.get_symbol(c, r).value(),
                _symbol
            );
        }
    };

    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            test_case_template{c, r, symbol::x};
            test_case_template{c, r, symbol::o};
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
