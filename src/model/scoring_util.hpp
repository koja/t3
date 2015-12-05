#ifndef scoring_util_8108740761
#define scoring_util_8108740761

#include <map>
#include <set>
#include <utility>

#include "src/model/board.hpp"
#include "src/model/line.hpp"
#include "src/model/symbol.hpp"

/** @returns all possible winning lines
 *
 * Lines are in no particular order.
 * Coordinates in lines are in no particular order.
 */
std::set<line> get_all_scoring_lines();

std::map<symbol, unsigned> count_symbols_on_line(const board& _board, const line& _line);

#endif
