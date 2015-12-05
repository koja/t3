#ifndef ui_intf_54687614354
#define ui_intf_54687614354

#include <string>
#include <utility>

#include "src/engine/move_coordinates_provider_intf.hpp"
#include "src/model/board.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/symbol.hpp"
#include "src/ui/bot_type.hpp"
#include "src/ui/player_type.hpp"

/**
 * Interface for all UI implementations.
 * Some non-modifying access to board should be accessible to all methods - expected to be passed to constructor of concrete implementation.
 */
class ui_intf : public move_coordinates_provider_intf {
    public:
        virtual player_type request_player_type(const symbol _symbol) = 0;
        virtual bot_type    request_bot_type(const symbol _symbol) = 0;

        virtual void report_players_setup_started() = 0;
        virtual void report_game_started(const game& _game) = 0;
        virtual void report_turn_started(const game& _game) = 0;
        virtual void report_board_was_changed(const game& _game) = 0;
        virtual void report_victory(const game& _game) = 0;
        virtual void report_tie(const game& _game) = 0;

        virtual void report_error(const std::string& _msg) = 0;

        virtual ~ui_intf() = default;
};

#endif
