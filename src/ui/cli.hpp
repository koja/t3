#ifndef cli_7658743511
#define cli_7658743511

#include <iostream>
#include <string>
#include <utility>

#include "src/model/board.hpp"
#include "src/ui/ui_intf.hpp"

/**
 * Interface for all UI implementations.
 */
class cli : public ui_intf {
    protected:
        std::ostream& output_;
        std::istream& input_;

    public:
        cli(std::ostream& _output, std::istream& _input);
        /**
         * Sends request for user to specify player type to output_.
         * Receives user input from input_ and returns appropriate player_type value.
         * Repeats until valid input is given.
         * Valid input values are 'c' (converted to player_type::computer) and 'h' (converted to player_type::human).
         */
        player_type request_player_type(const symbol _symbol) override;
        /**
         * Sends request for user to specify bot type to output_.
         * Receives user input from input_ and returns appropriate bot_type value.
         * Repeats until valid input is given.
         * Valid input values are 'n' (converted to bot_type::naive) and 'p' (converted to bot_type::perfect).
         */
        bot_type request_bot_type(const symbol _symbol) override;
        /**
         * Sends request for user to specify coordinates of his/her new move.
         * Receives user input from input_ and returns appropriate coordinates value.
         * Repeats until valid input is given.
         * Valid input values are [abc][123].
         */
        std::pair<col, row> get_next_move(const game& _game) override;

        void report_already_occupied_square(const std::pair<col, row> _coordinates, const game& _game) override;

        /* Events reporting */

        void report_players_setup_started() override;
        void report_game_started(const game& _game) override;
        void report_turn_started(const game& _game) override;
        void report_board_was_changed(const game& _game) override;
        void report_victory(const game& _game) override;
        void report_tie(const game& _game) override;
        void report_error(const std::string& _msg) override;
};

#endif
