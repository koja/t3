#ifndef setup_players_3510554311
#define setup_players_3510554311

#include <array>
#include <memory>

#include "src/engine/player_controllers.hpp"
#include "src/ui/ui_intf.hpp"

/**
 * Enables user to setup players for game.
 * @throws missing_player_type_setup in case of missing implementation
 * @throws missing_bot_type_setup in case of missing implementation
 */
player_controllers setup_players(const std::shared_ptr<ui_intf>& _ui);

#endif
