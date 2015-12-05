#include "src/engine/player_controllers.hpp"

#include <memory>

#include "src/engine/exception.hpp"
#include "src/engine/move_coordinates_provider_intf.hpp"
#include "src/model/board.hpp"
#include "src/model/player.hpp"

player_controllers::player_controllers(
    const player& _player_1_init, std::shared_ptr<move_coordinates_provider_intf> _coordinates_provider1,
    const player& _player_2_init, std::shared_ptr<move_coordinates_provider_intf> _coordinates_provider2
) :
    player_1_(_player_1_init),
    player_2_(_player_2_init),
    coordinates_provider_1_(_coordinates_provider1),
    coordinates_provider_2_(_coordinates_provider2)
{
    if(player_1_ == player_2_) { throw duplicate_definition_for_one_player{}; }
}

std::shared_ptr<move_coordinates_provider_intf> player_controllers::get_coordinates_provider(const player& _player) const {
    if(_player == player_1_) {
        return coordinates_provider_1_;
    }
    if(_player == player_2_) {
        return coordinates_provider_2_;
    }

    throw no_coordinates_provider_for_given_player{};
}

std::array<player, 2> player_controllers::get_players() const {
    return {player_1_, player_2_};
}
