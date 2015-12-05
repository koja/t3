#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <map>
#include "src/model/exception.hpp"
#include "src/model/scoring_util.hpp"
#include "test/util.hpp"

BOOST_AUTO_TEST_SUITE(test_scoring)

BOOST_AUTO_TEST_CASE(test_get_all_scoring_lines_is_complete)
{
    BOOST_CHECK_EQUAL( get_all_scoring_lines().size(), 8 );
}

BOOST_AUTO_TEST_CASE(test_count_symbols_on_given_coords_empty_board)
{
    board emptyboard;
    const std::map<symbol, unsigned> etalon{{symbol::x, 0}, {symbol::o, 0}};
    for(const line& ln : get_all_scoring_lines()) {
        BOOST_CHECK_EQUAL( count_symbols_on_line(emptyboard, ln), etalon );
    }
}

BOOST_AUTO_TEST_CASE(test_count_symbols_on_line)
{
    struct test_case_template{
        test_case_template(const symbol _symbol, const line& ln) {
            /* for every line on board
             * iteratively adding symbols (x, o, x)
             * and checking symbol counts after each add.
             */

            board testboard;
            symbol now_playing = _symbol;
            std::map<symbol, unsigned> etalon{{_symbol, 0}, {other_symbol(_symbol), 0}};

            for(const auto& square : ln) {
                testboard.add_symbol(square, now_playing);
                etalon.at(now_playing) += 1;
                BOOST_CHECK_EQUAL( count_symbols_on_line(testboard, ln), etalon );
                now_playing = other_symbol(now_playing);
            }
        }
    };

    for(const line& ln : get_all_scoring_lines()) {
        test_case_template{symbol::x, ln};
        test_case_template{symbol::o, ln};
    }
}

BOOST_AUTO_TEST_SUITE_END()
