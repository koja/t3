#include "src/engine/engine.hpp"

#include "src/engine/exception.hpp"
#include "src/model/exception.hpp"
#include "src/model/scoring_util.hpp"

engine::engine(
    const game& _game_init,
    const player_controllers& _player_controllers_init,
    const std::shared_ptr<ui_intf>& _ui
) :
    game_(_game_init),
    player_controllers_(_player_controllers_init),
    ui_(_ui)
{
    ui_->report_game_started(game_);
}

bool engine::play_turn() {

    if( game_.get_winner() || game_.is_tie() ) {
        throw game_already_ended{};
    }

    ui_->report_turn_started( game_ );

    const player current_player = game_.get_player_to_move_now();

    while(true) {
        const std::pair<col, row> coordinates = player_controllers_.get_coordinates_provider(current_player)->get_next_move(game_);
        try {
            game_.make_move(
                current_player,
                coordinates
            );
            break;
        } catch(const move_to_already_occupied_square&) {
            player_controllers_.get_coordinates_provider(current_player)->report_already_occupied_square(coordinates, game_);
        }
    }

    ui_->report_board_was_changed( game_ );

    if( game_.get_winner() ) {
        ui_->report_victory( game_ );
        return true;

    } else if( game_.is_tie() ) {
        ui_->report_tie( game_ );
        return true;
    }

    return false;
}

game engine::get_game_state() const {
    return game_;
}
