#include "src/model/player.hpp"

#include <string>
#include <utility>
#include "src/model/exception.hpp"

player::player(const symbol _symbol)
:   symbol_(_symbol)
{ }

void player::make_move(board& _board, const std::pair<col, row> _coordinates) const {
    _board.add_symbol(_coordinates, symbol_);
}

symbol player::get_symbol() const {
    return symbol_;
}

bool operator==(const player& lhs, const player& rhs) {
    return lhs.get_symbol() == rhs.get_symbol();
}

bool operator!=(const player& lhs, const player& rhs) {
    return ! (lhs == rhs);
}
