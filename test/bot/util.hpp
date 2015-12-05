#ifndef test_util_hpp_367951231357
#define test_util_hpp_367951231357

#include <boost/algorithm/string/join.hpp>
#include <string>
#include <vector>

#include "src/model/game.hpp"
#include "src/ui/cli.hpp"

inline col col_from_string(const std::string& _x) {
    if(_x == "a") { return col::_a; }
    if(_x == "b") { return col::_b; }
    if(_x == "c") { return col::_c; }

    throw 0;
}

inline row row_from_string(const std::string& _y) {
    if(_y == "1") { return row::_1; }
    if(_y == "2") { return row::_2; }
    if(_y == "3") { return row::_3; }

    throw 1;
}

inline std::string to_string(const symbol _symbol) {
    switch(_symbol) {
        case symbol::x        : return "x"; break;
        case symbol::o        : return "o"; break;
    }
    throw 2;
}

inline std::string to_string(const optional<symbol>& _symbol) {
    /* WARNING: optional has no-explicit constructor - could lead to stack overflow in absence of to_string(symbol) */
    return _symbol ? to_string( _symbol.value() ) : " ";
}

inline std::string to_string(const board& _board) {
    std::string result;

    result += "  | a | b | c |\n";

    unsigned short row_num = 1;
    for( const row r : get_ordered_row_values() ) {
        std::vector<std::string> symbols;
        for( const col c : get_ordered_col_values() ) {
            symbols.push_back(
                to_string( _board.get_symbol(c, r) )
            );
        }
        result +=
            std::to_string(row_num)
            + " | " +
            boost::algorithm::join(symbols, " | ")
            + " |\n";
        ++row_num;
    }

    return result;
}

/* auxiliary utility - not used in testing itself, only debug printing */
inline std::string print_board_progression(const std::vector<board> & _b_progression) {
    std::string result;

    for(const board& state : _b_progression) {
        result += to_string(state) + "\n";
    }

    return result;
}

inline bool is_end_of_game(const board& _board, const player& _current_player) {
    game check_game{
        { _current_player, player{other_symbol(_current_player.get_symbol())} },
        _board
    };

    if( check_game.get_winner() ) {
        return true;
    }

    if( check_game.is_tie() ){
        return true;
    }

    return false;
}

template<typename Tbot_impl, typename Tendgame_checker> static void walk_game_tree(
    const player& _test_player,
    std::vector<board> _board_debug_sequence,
    Tendgame_checker _endgame_checker
) {
    std::shared_ptr<move_coordinates_provider_intf> test_bot = std::shared_ptr<move_coordinates_provider_intf>{new Tbot_impl};

    // generate current move and log it to debug sequence
    board board_for_current_move = _board_debug_sequence.back();

    _test_player.make_move(
        board_for_current_move,
        test_bot->get_next_move(
            game{
                {
                    _test_player,
                    player{ other_symbol( _test_player.get_symbol() ) }
                },
                board_for_current_move
            }
        )
    );

    _board_debug_sequence.push_back(board_for_current_move);

    if( is_end_of_game(board_for_current_move, player{ other_symbol( _test_player.get_symbol() ) }) ) {
        _endgame_checker(_board_debug_sequence, _test_player);
        return;
    }

    // generating all possible opponent moves and log those

    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            if( !_board_debug_sequence.back().get_symbol(c, r) ) {

                board board_for_opponent_move = _board_debug_sequence.back();
                board_for_opponent_move.add_symbol(c, r, other_symbol( _test_player.get_symbol() ));

                std::vector<board> sequence_including_opponent_move{_board_debug_sequence};
                sequence_including_opponent_move.push_back(board_for_opponent_move);

                if( is_end_of_game(board_for_opponent_move, _test_player) ) {
                    _endgame_checker(
                        sequence_including_opponent_move,
                        player{
                            other_symbol( _test_player.get_symbol() )
                        }
                    );
                    continue;
                }

                walk_game_tree<Tbot_impl>(_test_player, sequence_including_opponent_move, _endgame_checker);
            }
        }
    }
}

#endif
