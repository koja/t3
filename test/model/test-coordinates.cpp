#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "src/model/coordinates.hpp"

BOOST_AUTO_TEST_SUITE(test_coordinates)

BOOST_AUTO_TEST_CASE(test_get_ordered_cols_values_differ)
{

    const std::array<const col, 3> ordered_cols = get_ordered_col_values();

    BOOST_CHECK( ordered_cols[0] != ordered_cols[1] );
    BOOST_CHECK( ordered_cols[1] != ordered_cols[2] );
    BOOST_CHECK( ordered_cols[2] != ordered_cols[0] );
}

BOOST_AUTO_TEST_CASE(test_get_ordered_rows_values_differ)
{
    const std::array<const row, 3> ordered_rows = get_ordered_row_values();

    BOOST_CHECK( ordered_rows[0] != ordered_rows[1] );
    BOOST_CHECK( ordered_rows[1] != ordered_rows[2] );
    BOOST_CHECK( ordered_rows[2] != ordered_rows[0] );
}

BOOST_AUTO_TEST_SUITE_END()
