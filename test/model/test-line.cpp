#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <map>
#include <set>
#include "src/model/exception.hpp"
#include "src/model/line.hpp"
#include "test/util.hpp"

BOOST_AUTO_TEST_SUITE(test_line)

typedef std::array< std::pair<col, row>, 3> coordinates_array;

BOOST_AUTO_TEST_CASE(test_line_duplicate_coordinates)
{
    {
        /* boost macro has issue with commas */
        const coordinates_array duplicate_coordinates{
            std::make_pair(col::_a, row::_1),
            std::make_pair(col::_b, row::_2),
            std::make_pair(col::_a, row::_1)
        };

        BOOST_CHECK_THROW(
            line{duplicate_coordinates},
            duplicate_coordinates_in_line
        );
    }

    {
        const coordinates_array duplicate_coordinates{
            std::make_pair(col::_c, row::_1),
            std::make_pair(col::_b, row::_2),
            std::make_pair(col::_b, row::_2)
        };

        BOOST_CHECK_THROW(
            line{duplicate_coordinates},
            duplicate_coordinates_in_line
        );
    }

    {
        const coordinates_array duplicate_coordinates{
            std::make_pair(col::_c, row::_1),
            std::make_pair(col::_c, row::_1),
            std::make_pair(col::_b, row::_2)
        };

        BOOST_CHECK_THROW(
            line{duplicate_coordinates},
            duplicate_coordinates_in_line
        );
    }
}

BOOST_AUTO_TEST_CASE(test_line_iteration)
{
    line test_ln{
        coordinates_array{
            std::make_pair(col::_a, row::_1),
            std::make_pair(col::_b, row::_2),
            std::make_pair(col::_c, row::_3)
        }
    };

    unsigned iteration_steps = 0;

    std::set<std::pair<col, row>> unique_coordinates;

    for(auto it = test_ln.begin();
        it != test_ln.end();
        ++it, ++iteration_steps
    ) {
        unique_coordinates.insert(*it);
    }

    BOOST_CHECK_EQUAL(iteration_steps, 3);
    BOOST_CHECK_EQUAL(unique_coordinates.size(), 3);
}

BOOST_AUTO_TEST_CASE(test_line_operators)
{
    line test_ln1{
        coordinates_array{
            std::make_pair(col::_a, row::_1),
            std::make_pair(col::_a, row::_2),
            std::make_pair(col::_a, row::_3)
        }
    };

    line test_ln2(
        coordinates_array{
            std::make_pair(col::_a, row::_1),
            std::make_pair(col::_b, row::_1),
            std::make_pair(col::_c, row::_1)
        }
    );

    BOOST_CHECK( test_ln1 == test_ln1 );
    BOOST_CHECK( !( test_ln1 == test_ln2 ) );

    BOOST_CHECK( !( test_ln1 != test_ln1 ) );
    BOOST_CHECK( test_ln1 != test_ln2 );

    /* exact definition of ordering is implementation detail */
    BOOST_CHECK( std::less<line>{}(test_ln1, test_ln2) || std::less<line>{}(test_ln2, test_ln1) );
}

/* testing std::less<line> indirectly by inserting into std::set<line> */
BOOST_AUTO_TEST_CASE(test_line_less)
{
    std::set<line> test_line_set;

    test_line_set.insert(
        line{
            coordinates_array{
                std::make_pair(col::_a, row::_1),
                std::make_pair(col::_b, row::_1),
                std::make_pair(col::_c, row::_1)
            }
        }
    );

    test_line_set.insert(
        line{
            coordinates_array{
                std::make_pair(col::_a, row::_1),
                std::make_pair(col::_b, row::_1),
                std::make_pair(col::_c, row::_1)
            }
        }
    );

    BOOST_CHECK_EQUAL(test_line_set.size(), 1);
}

BOOST_AUTO_TEST_SUITE_END()
