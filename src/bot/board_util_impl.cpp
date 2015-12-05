#include "src/bot/board_util_impl.hpp"

#include <set>
#include <utility>

#include "src/model/board.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/line.hpp"
#include "src/model/scoring_util.hpp"
#include "src/model/symbol.hpp"

std::set< std::pair<col, row> > get_intersection(
    const line& _lhs,
    const line& _rhs
) {
    std::set<std::pair<col, row>> intersection;

    for(const auto& l : _lhs) {
        for(const auto& r : _rhs) {
            if(l==r) { intersection.insert(l); }
        }
    }

    return intersection;
}

std::set<line> get_lines_occupied_by_me_only(const board& _board, const symbol _my_symbol) {
    std::set<line> result;

    for( const line& ln : get_all_scoring_lines() ) {
        const std::map<symbol, unsigned> symbol_counts = count_symbols_on_line(_board, ln);
        if(
            symbol_counts.at( other_symbol(_my_symbol) ) == 0
            &&
            symbol_counts.at( _my_symbol ) > 0
        ) {
            result.insert(ln);
        }
    }

    return result;
}
