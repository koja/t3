#ifndef coordinates_9876320145
#define coordinates_9876320145

#include <array>

enum class col {_a = 0, _b = 1, _c = 2};
enum class row {_1 = 0, _2 = 1, _3 = 2};

/** @returns column coordinates in ascending order */
static constexpr std::array<const col, 3> get_ordered_col_values() { return {col::_a, col::_b, col::_c}; }

/** @returns row coordinates in ascending order */
static constexpr std::array<const row, 3> get_ordered_row_values() { return {row::_1, row::_2, row::_3}; }


#endif
