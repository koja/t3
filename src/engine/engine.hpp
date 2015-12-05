#ifndef engine_9751041170
#define engine_9751041170

#include <memory>

#include "src/engine/player_controllers.hpp"
#include "src/model/game.hpp"
#include "src/ui/ui_intf.hpp"

/**
 * Engine to run the game. Passes inputs to model and outputs response.
 */

class engine {
    public:
        /**
         * @param _game_init is copied to member instance during object construction
         * @param _player_controllers_init is copied to member instance during object construction
         * @param _ui is pointing to shared instance (shared possibly with caller)
         */
        engine(
            const game& _game_init,
            const player_controllers& _player_controllers_init,
            const std::shared_ptr<ui_intf>& _ui
        );

        /**
         * @returns true if game was ended at the end of turn
         * @throws game_already_ended if game had already ended before function was called
         */
        bool play_turn();
        game get_game_state() const;

    private:
        game game_;
        player_controllers player_controllers_;
        std::shared_ptr<ui_intf> ui_;
};

#endif
