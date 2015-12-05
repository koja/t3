#ifndef player_0571351410
#define player_0571351410

#include <memory>
#include <utility>

#include "src/model/board.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/symbol.hpp"

/**
 * Player of the game
 */
class player {
    public:
        explicit player(const symbol _symbol);
        void make_move(board& _board, const std::pair<col, row> _coordinates) const;
        symbol get_symbol() const;
    private:
        const symbol symbol_;
};

bool operator==(const player& lhs, const player& rhs);

bool operator!=(const player& lhs, const player& rhs);

#endif
