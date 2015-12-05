#ifndef player_controllers_8978531012
#define player_controllers_8978531012

#include <memory>

#include "src/engine/move_coordinates_provider_intf.hpp"
#include "src/model/player.hpp"

/**
 * A way for players to get to "know" where to move.
 */
class player_controllers {
    public:
        /**
         * @param _player_1_init is copied to member instance during object construction
         * @param _player_2_init is is copied to member instance during object construction
         * @throws duplicate_definition_for_one_player
         */
        player_controllers(
            const player& _player_1_init, std::shared_ptr<move_coordinates_provider_intf> _coordinates_provider1,
            const player& _player_2_init, std::shared_ptr<move_coordinates_provider_intf> _coordinates_provider2
        );
        /**
         * @returns coordinates provider for given _player
         * @throws no_coordinates_provider_for_given_player
         */
        std::shared_ptr<move_coordinates_provider_intf> get_coordinates_provider(const player& _player) const;
        std::array<player, 2> get_players() const;
    private:
        player player_1_, player_2_;
        std::shared_ptr<move_coordinates_provider_intf> coordinates_provider_1_, coordinates_provider_2_;
};

#endif
