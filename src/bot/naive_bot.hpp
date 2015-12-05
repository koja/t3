#ifndef naive_bot_5304341521
#define naive_bot_5304341521

#include <utility>

#include "src/engine/move_coordinates_provider_intf.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/game.hpp"

/**
 * Simple yet reasonably capable bot. Sometimes loses.
 */
class naive_bot : public move_coordinates_provider_intf {
    public:
        /**
         * @throws board_is_full
         * @throws bot_error
         */
        std::pair<col, row> get_next_move(const game& _game) override;

        /**
         * Parameters are ignored.
         * @throws unknown_error - always, as a reaction to unexpected error, could be bot error, could be client error, no way to handle it
         */
        void report_already_occupied_square(const std::pair<col, row> _coordinates, const game& _game) override;
};

#endif
