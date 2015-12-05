#include "src/model/line.hpp"

#include <algorithm>
#include "src/model/exception.hpp"

static bool operator<(const std::pair<col, row>& lhs, const std::pair<col, row>& rhs) {
    return
        lhs.first < rhs.first
        ?   true
        :   lhs.second < rhs.second;
}

static std::array< std::pair<col, row>, 3 > get_sorted( const std::array< std::pair<col, row>, 3 >& _input ) {
    std::array< std::pair<col, row>, 3 > result{_input.at(0), _input.at(1), _input.at(2)};

    /* just a bubble sort - expecting elements to be sorted most of the time
     * trading speed (N=3...) for clarity
     */
    if( result.at(1) < result.at(0) ) {
        std::swap(result.at(1), result.at(0));
    }
    if( result.at(2) < result.at(1) ) {
        std::swap(result.at(2), result.at(1));
    }
    if( result.at(1) < result.at(0) ) {
        std::swap(result.at(1), result.at(0));
    }

    return result;
}

line::line(
    const std::array< std::pair<col, row>, 3 >& _squares
) :
    sorted_squares( get_sorted(_squares) )
{
    if( sorted_squares.at(0) == sorted_squares.at(1) ||
        sorted_squares.at(1) == sorted_squares.at(2) ||
        sorted_squares.at(2) == sorted_squares.at(0)
    ) {
        throw duplicate_coordinates_in_line{};
    }
}

line::const_iterator line::begin() const {
    return sorted_squares.cbegin();
}

line::const_iterator line::end() const {
    return sorted_squares.cend();
}

bool operator==(const line& lhs, const line& rhs) {
    return lhs.sorted_squares == rhs.sorted_squares;
}

bool operator!=(const line& lhs, const line& rhs) {
    return !( lhs.sorted_squares == rhs.sorted_squares );
}
