#ifndef mock_ui_978743130
#define mock_ui_978743130

#include <string>
#include <utility>
#include <vector>

class mock_ui : public ui_intf {
    public:
        explicit mock_ui(const std::vector<std::pair<col, row>>& _moves = std::vector<std::pair<col, row>>{})
        :   moves_(_moves),
            curr_move_it_( moves_.cbegin() )
        { }

        player_type request_player_type(const symbol) override { return player_type::human; }
        bot_type    request_bot_type(const symbol) override { return bot_type::naive; }

        std::pair<col, row> get_next_move(const game&) override {
            return *(curr_move_it_++);
        }
        void report_already_occupied_square(const std::pair<col, row>, const game&) override { }

        void report_players_setup_started() override { }
        void report_game_started(const game&) override { }
        void report_turn_started(const game&) override { }
        void report_board_was_changed(const game&) override { }
        void report_victory(const game&) override { }
        void report_tie(const game&) override { }

        void report_error(const std::string&) override { }

    private:
        const std::vector<std::pair<col, row>> moves_;
        std::vector<std::pair<col, row>>::const_iterator curr_move_it_;
};

#endif
