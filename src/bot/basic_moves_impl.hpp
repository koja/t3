#ifndef basic_moves_impl_997815411
#define basic_moves_impl_997815411

#include <experimental/optional>
using std::experimental::optional;
#include <utility>

#include "src/model/board.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/symbol.hpp"

/** @returns some imminent victory square where for current move (if available) */
optional<std::pair<col, row>> get_imminent_victory_square(const board& _board, const symbol _symbol);

/** @returns square where placing symbol averts imminent lose (if available, just one/some if multiple) */
optional<std::pair<col, row>> get_imminent_lose_aversion_square(const board& _board, const symbol _symbol);

/** @returns some free corner coordinates (if available) */
optional<std::pair<col, row>> get_some_free_corner(const board& _board);

/** @returns some free coordinates (if available) */
optional<std::pair<col, row>> get_some_free_square(const board& _board);

#endif
