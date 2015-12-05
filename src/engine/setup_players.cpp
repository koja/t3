#include "src/engine/setup_players.hpp"

#include <array>
#include <memory>
#include <vector>

#include "src/bot/naive_bot.hpp"
#include "src/bot/perfect_bot.hpp"
#include "src/engine/exception.hpp"
#include "src/engine/player_controllers.hpp"
#include "src/model/player.hpp"
#include "src/model/symbol.hpp"
#include "src/ui/bot_type.hpp"
#include "src/ui/player_type.hpp"

static std::shared_ptr<move_coordinates_provider_intf> setup_player_impl(const symbol _symbol, const std::shared_ptr<ui_intf>& _ui) {
    const player_type player_type_input = _ui->request_player_type(_symbol);

    if(player_type_input == player_type::human) {
        return _ui;

    } else if(player_type_input == player_type::computer) {

        const bot_type bot_type_input = _ui->request_bot_type(_symbol);

        if(bot_type_input == bot_type::naive) {
            return std::make_shared<naive_bot>();

        } else if(bot_type_input == bot_type::perfect) {
            return std::make_shared<perfect_bot>();

        }

        throw missing_bot_type_setup{};
    }

    throw missing_player_type_setup{};
}

player_controllers setup_players(const std::shared_ptr<ui_intf>& _ui) {
    return {
        player{symbol::x}, setup_player_impl(symbol::x, _ui),
        player{symbol::o}, setup_player_impl(symbol::o, _ui),
    };
}
