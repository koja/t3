#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "src/model/symbol.hpp"
#include "test/util.hpp"

BOOST_AUTO_TEST_SUITE(test_symbol)

BOOST_AUTO_TEST_CASE(test_other_symbol)
{
    BOOST_CHECK_EQUAL(
        other_symbol( symbol::x ),
        symbol::o
    );

    BOOST_CHECK_EQUAL(
        other_symbol( symbol::o ),
        symbol::x
    );
}

BOOST_AUTO_TEST_SUITE_END()
