#include <iostream>

#include "src/exception_intf.hpp"
#include "src/model/game.hpp"
#include "src/engine/engine.hpp"
#include "src/engine/setup_players.hpp"
#include "src/ui/cli.hpp"

inline void t3() {
    /* std::shared_ptr ctor is noexcept */
    std::shared_ptr<ui_intf> the_ui{nullptr};

    try {
        the_ui = std::shared_ptr<ui_intf>{new cli{std::cout, std::cin}};

        const player_controllers the_player_controllers = setup_players(the_ui);

        game the_game{the_player_controllers.get_players(), board{}};

        engine the_engine(the_game, the_player_controllers, the_ui);

        while( !the_engine.play_turn() ) { }

    } catch(const exception_intf& e) {
        if(the_ui) {
            the_ui->report_error(e.what());
        }
        throw;
    } catch(const std::exception& e) {
        if(the_ui) {
            the_ui->report_error(e.what());
        }
        throw;
    } catch(...) {
        if(the_ui) {
            the_ui->report_error("");
        }
        throw;
    }
}
