#include "src/bot/basic_moves_impl.hpp"

#include <map>
#include <set>
#include <utility>

#include "src/model/scoring_util.hpp"

optional<std::pair<col, row>> get_imminent_victory_square(const board& _board, const symbol _symbol) {
    for( const line& scoring_line : get_all_scoring_lines() ) {
        const std::map<symbol, unsigned> symbol_counts = count_symbols_on_line(_board, scoring_line);
        if(
            symbol_counts.at(_symbol) == 2
            &&
            symbol_counts.at( other_symbol(_symbol) ) == 0
        ) {
            for(const std::pair<col, row>& square : scoring_line) {
                if( _board.get_symbol(square) == optional<symbol>() ) {
                    return square;
                }
            }
        }
    }
    return optional<std::pair<col, row>>();
}

optional<std::pair<col, row>> get_imminent_lose_aversion_square(const board& _board, const symbol _symbol) {
    for( const line& scoring_line : get_all_scoring_lines() ) {
        const std::map<symbol, unsigned> symbol_counts = count_symbols_on_line(_board, scoring_line);
        if(
            symbol_counts.at( other_symbol(_symbol) ) == 2
            &&
            symbol_counts.at( _symbol ) == 0
        ) {
            for(const std::pair<col, row>& square : scoring_line) {
                if( _board.get_symbol(square) == optional<symbol>() ) {
                    return square;
                }
            }
        }
    }
    return optional<std::pair<col, row>>();
}

optional<std::pair<col, row>> get_some_free_corner(const board& _board) {
    const std::set<std::pair<col, row>> corners =
        {
            {col::_a, row::_1},
            {col::_c, row::_1},
            {col::_a, row::_3},
            {col::_c, row::_3}
        };

    for(const std::pair<col, row>& square : corners) {
        if( ! _board.get_symbol(square) ) {
            return square;
        }
    }

    return optional<std::pair<col, row>>();
}

optional<std::pair<col, row>> get_some_free_square(const board& _board) {
    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            if( ! _board.get_symbol(c, r) ) {
                return std::make_pair(c, r);
            }
        }
    }

    return optional<std::pair<col, row>>();
}
