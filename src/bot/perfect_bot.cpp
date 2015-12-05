#include "src/bot/perfect_bot.hpp"

#include <experimental/optional>
using std::experimental::optional;
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <utility>

#include "src/bot/board_util_impl.hpp"
#include "src/bot/basic_moves_impl.hpp"
#include "src/model/player.hpp"
#include "src/model/scoring_util.hpp"
#include "src/bot/exception.hpp"

/** @return square where fork can be created (if any, just some if there are multiple)
 * fork possibility is a
 *     pair {
 *         of lines {
 *             - with at least one my symbol
 *             - no opponent symbol
 *         }
 *         such that their common square is free (this implies that lines are different)
 *     }
 */
static optional<std::pair<col, row>> get_fork_possibility(const board& _board, const symbol _symbol) {

    const std::set<line> lines_occupied_by_me_only = get_lines_occupied_by_me_only(_board, _symbol);

    for( const line& ln1 : lines_occupied_by_me_only ) {
        for( const line& ln2 : lines_occupied_by_me_only ) {
            std::set<std::pair<col, row>> intersection = get_intersection(ln1, ln2);
            if(
                intersection.size() == 1
                &&
                ! _board.get_symbol( *intersection.begin() )
            ) {
                return *intersection.begin();
            }
        }
    }
    return optional<std::pair<col, row>>();
}

/**
 * @returns squares used as common squares in possible forks
 * Asserts that imminent victory squares were looked for already and none were found!!!
 */
static std::set<std::pair<col, row>> get_common_squares_of_fork_possibilities(const board& _board, const symbol _symbol) {
    std::set<std::pair<col, row>> result;

    const std::set<line> lines_occupied_by_me_only = get_lines_occupied_by_me_only(_board, _symbol);

    for( const line& candidate_ln1 : lines_occupied_by_me_only ) {
        for( const line& candidate_ln2 : lines_occupied_by_me_only ) {
            if(candidate_ln1 != candidate_ln2) {
                std::set<std::pair<col, row>> intersection = get_intersection(candidate_ln1, candidate_ln2);
                /* asserting that imminent victory squares were looked for already
                 * => lines without opponent symbol have at most one my symbol
                 * => if intersection of two different lines is taken
                 *    then no other square in these lines is taken (would be second symbol) and this pair of lines is not interesting but if the intersection is free ... */
                if( intersection.size() == 1 ) {
                    /* ...if intersection is not taken... bingo! */
                    if( !_board.get_symbol( *intersection.begin() ) ) {
                        result.insert( *intersection.begin() );
                    }
                }
            }
        }
    }

    return result;
}

/**
 * @returns square where to defend against opponents possible forks
 * one fork: easy
 * multiple fork possibilities: force opponent to play elsewhere (but not just anywhere) and thus making the board more full
 */
static optional<std::pair<col, row>> get_square_to_prevent_opponent_fork(const board& _board, const symbol _my_symbol) {

    std::set< std::pair<col, row> > opponent_fork_common_squares = get_common_squares_of_fork_possibilities( _board, other_symbol(_my_symbol) );

    if(opponent_fork_common_squares.size() == 1) {
        return *opponent_fork_common_squares.begin();

    } else if(opponent_fork_common_squares.size() > 1) {
        /* find possible distracting lines - possibly forcing opponent to play there... */
        std::set<line> lines_occupied_by_me_only = get_lines_occupied_by_me_only(_board, _my_symbol);

        for(const line& candidate_ln : lines_occupied_by_me_only) {
            /* ... skip those where would opponent like to play anyway ... */
            bool line_is_not_intersecting_opponents_fork_common_squares = true;
            for(const std::pair<col, row>& fork_common_square : opponent_fork_common_squares) {
                if( std::find( candidate_ln.begin(), candidate_ln.end(), fork_common_square )
                    != candidate_ln.end()
                ) {
                    line_is_not_intersecting_opponents_fork_common_squares = false;
                }
            }
            /* ... and find some free square from those that remains */
            if(line_is_not_intersecting_opponents_fork_common_squares) {
                for(const std::pair<col, row>& square : candidate_ln) {
                    if( !_board.get_symbol(square) ) {
                        return square;
                    }
                }
            }
        }
    }

    return optional<std::pair<col, row>>();
}

std::pair<col, row> perfect_bot::get_next_move(const game& _game) {
    {
        const optional<std::pair<col, row>> victory = get_imminent_victory_square( _game.get_board_state(), _game.get_player_to_move_now().get_symbol() );
        if(victory) { return victory.value(); }
    }
    {
        /* There might be multiple but we can't do anything better about it apart hoping for the best. */
        const optional<std::pair<col, row>> lose_aversion = get_imminent_lose_aversion_square( _game.get_board_state(), _game.get_player_to_move_now().get_symbol() );
        if(lose_aversion) { return lose_aversion.value(); }
    }
    {
        const optional<std::pair<col, row>> my_fork_possibility = get_fork_possibility( _game.get_board_state(), _game.get_player_to_move_now().get_symbol() );
        if(my_fork_possibility) { return my_fork_possibility.value(); }
    }
    {
        const optional<std::pair<col, row>> opponent_fork_aversion = get_square_to_prevent_opponent_fork( _game.get_board_state(), _game.get_player_to_move_now().get_symbol() );
        if(opponent_fork_aversion) { return opponent_fork_aversion.value(); }
    }
    {   /* go for center */
        const std::pair<col, row> center = std::make_pair(col::_b, row::_2);
        if( !_game.get_board_state().get_symbol(center) ) { return center; }
    }
    {
        const optional<std::pair<col, row>> free_corner = get_some_free_corner(_game.get_board_state());
        if(free_corner) { return free_corner.value(); }
    }
    {
        const optional<std::pair<col, row>> free_square =  get_some_free_square(_game.get_board_state());
        if(!free_square) {
            throw board_is_full{};
        } else {
            return free_square.value();
        }
    }

    // This is a safety measure had I messed above. Ignore the eventual compiler warning.
    throw bot_error{};
}

void perfect_bot::report_already_occupied_square(const std::pair<col, row>, const game&) {
    throw unknown_error{};
}
