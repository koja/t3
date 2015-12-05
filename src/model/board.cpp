#include "src/model/board.hpp"

#include <vector>

#include "src/model/exception.hpp"

void board::add_symbol(const col _col, const row _row, const symbol _new_symbol) {
    if( occupied_squares_.find(std::make_pair(_col, _row)) != occupied_squares_.end() ) {
        throw move_to_already_occupied_square{};
    }

    occupied_squares_.insert(
        std::make_pair( std::make_pair(_col, _row), _new_symbol )
    );
}

void board::add_symbol(const std::pair<col, row> _coordinates, symbol _new_symbol) {
    add_symbol(_coordinates.first, _coordinates.second, _new_symbol);
}

optional<symbol> board::get_symbol(const col _col, const row _row) const {
    const auto it = occupied_squares_.find(std::make_pair(_col, _row));
    return
        it == occupied_squares_.end()
        ?   optional<symbol>()
        :   it->second;
}

optional<symbol> board::get_symbol(const std::pair<col, row> _coordinates) const {
    return get_symbol(_coordinates.first, _coordinates.second);
}
