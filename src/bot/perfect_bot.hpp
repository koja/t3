#ifndef perfect_bot_5413148350
#define perfect_bot_5413148350

#include <utility>

#include "src/engine/move_coordinates_provider_intf.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/game.hpp"

/**
 * Bot that never loses.
 */
class perfect_bot : public move_coordinates_provider_intf {
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
        void report_already_occupied_square(const std::pair<col, row>, const game&) override;
};

#endif
