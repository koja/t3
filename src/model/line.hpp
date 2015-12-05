#ifndef line_54544388783
#define line_54544388783

#include <array>
#include <functional> // std::less
#include <utility>

#include "src/model/coordinates.hpp"

/**
 * Stores sorted coordinates as a definition of line. Doesn't provide any geometrical validation line though.
 */
class line {
    public:
        typedef std::array< std::pair<col, row>, 3 >::const_iterator const_iterator;
        /**
         * @param _squares_init is copied to member instance during object construction
         * @throws duplicate_coordinates_in_line
         */
        explicit line( const std::array< std::pair<col, row>, 3 >& _squares_init );

        const_iterator begin() const;
        const_iterator end() const;

        friend bool operator==(const line& lhs, const line& rhs);
        friend bool operator!=(const line& lhs, const line& rhs);
        template<typename T> friend struct std::less;

    private:
        const std::array< std::pair<col, row>, 3 > sorted_squares;
};

namespace std {
template<> struct less<line> {
    bool operator()(const line& lhs, const line& rhs) const {
        return lhs.sorted_squares < rhs.sorted_squares;
    }
};
}

#endif
