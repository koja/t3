#ifndef board_4543541514
#define board_4543541514

#include <experimental/optional>
using std::experimental::optional;
#include <map>
#include <utility>

#include "src/model/coordinates.hpp"
#include "src/model/symbol.hpp"

/** playing board representation */
class board {
    public:
        /** Adds new symbol to given coordinates.
         * @throws move_to_already_occupied_square
         */
        void add_symbol(const col _col, const row _row, const symbol _new_symbol);

        /** Adds new symbol to given coordinates.
         * @throws move_to_already_occupied_square
         */
        void add_symbol(const std::pair<col, row> _coordinates, const symbol _new_symbol);

        /** @returns symbol at given coordinates and null-initialized value in case there is none */
        optional<symbol> get_symbol(const col _col, const row _row) const;

        /** @returns symbol at given coordinates and null-initialized value in case there is none */
        optional<symbol> get_symbol(const std::pair<col, row> _coordinates) const;

    private:
        std::map<
            const std::pair<const col, const row>,
            const symbol
        > occupied_squares_;
};

#endif
