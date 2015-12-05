#ifndef board_util_impl_997815411
#define board_util_impl_997815411

#include <set>
#include <utility>

#include "src/model/board.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/line.hpp"
#include "src/model/symbol.hpp"

std::set< std::pair<col, row> > get_intersection(const line& _lhs, const line& _rhs);

/** @returns all lines occupied by _my_symbol (at least one) that are not occupied by other symbol */
std::set<line> get_lines_occupied_by_me_only(const board& _board, const symbol _my_symbol);

#endif
