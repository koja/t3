#ifndef game_5454153435
#define game_5454153435

#include <array>
#include <memory>
#include <utility>

#include "src/model/board.hpp"
#include "src/model/coordinates.hpp"
#include "src/model/player.hpp"
#include "src/model/symbol.hpp"

/**
 * The game
 */
class game {
    public:
        /**
         * @param _players_init is copied to member instance during object construction, first element defines player to move first
         * @param _board_init is copied to member instance during object construction
         * @throws invalid_board_symbol_counts
         * @throws invalid_player_order in case first player from _players has higher symbol count therefore can not make move
         * @throws both_players_have_the_same_symbol
         * @throws both_players_have_winning_line
         */
        game(
            const std::array<player, 2>& _players_init,
            const board& _board_init
        );

        /**
         * @returns player that is going to make the next move (even if the game is already ended)
         */
        player get_player_to_move_now() const;

        /**
         * makes move and sets next player to move
         * @throws player_moves_out_of_turn if player differs from get_player_to_move_now() result
         * @throws game_already_won
         */
        void make_move(const player& _player, const std::pair<col, row> _coordinates);

        board get_board_state() const;

        std::array<player, 2> get_players() const;

        /**
         * @throws both_players_have_winning_line
         */
        optional<player> get_winner() const;

        /**
         * @returns true if no player can win the game
         * @throws both_players_have_winning_line
         */
        bool is_tie() const;

    private:
        const std::array<player, 2> players_;
        std::array<player, 2>::const_iterator current_player_;
        board board_;
};

#endif
