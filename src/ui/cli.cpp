#include "src/ui/cli.hpp"

#include <boost/algorithm/string/join.hpp>

#include <experimental/optional>
using std::experimental::optional;
#include <ostream>
#include <string>
#include <vector>

#include "src/ui/exception.hpp"
#include "src/model/player.hpp"

/** @throws invalid_coordinate */
static col col_from_string(const std::string& _c) {
    if(_c == "a") { return col::_a; }
    if(_c == "b") { return col::_b; }
    if(_c == "c") { return col::_c; }

    throw invalid_coordinate{};
}

/** @throws invalid_coordinate */
static row row_from_string(const std::string& _r) {
    if(_r == "1") { return row::_1; }
    if(_r == "2") { return row::_2; }
    if(_r == "3") { return row::_3; }

    throw invalid_coordinate{};
}

/** @throws invalid_move_input_syntax */
static std::pair<col, row> parse_move_input(const std::string& _input) {
    if( _input.length() != 2 ) {
        throw invalid_move_input_syntax{};
    }
    try {
        col temp_x = col_from_string( _input.substr(0, 1) );
        row temp_y = row_from_string( _input.substr(1, 2) );

        return std::make_pair(temp_x, temp_y);

    } catch(const invalid_coordinate&) {
        throw invalid_move_input_syntax{};
    }
}

/** @throws invalid_symbol */
static std::string to_string(const symbol _symbol) {
    switch(_symbol) {
        case symbol::x  : return "x";
        case symbol::o  : return "o";
    }
    throw invalid_symbol{};
}

static std::string to_string(const optional<symbol>& _symbol) {
    /* WARNING: optional has no-explicit constructor - could lead to stack overflow in absence of to_string(symbol) */
    return _symbol ? to_string( _symbol.value() ) : " ";
}

static std::string to_string(const board& _board) {
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

/** @throws invalid_coordinate */
static std::string to_string(col c) {
    switch(c) {
        case col::_a : return "a";
        case col::_b : return "b";
        case col::_c : return "c";
    }

    throw invalid_coordinate{};
}

/** @throws invalid_coordinate */
static std::string to_string(row r) {
    switch(r) {
        case row::_1 : return "1";
        case row::_2 : return "2";
        case row::_3 : return "3";
    }

    throw invalid_coordinate{};
}

cli::cli(std::ostream& _output, std::istream& _input)
:   output_(_output),
    input_(_input)
{ }

player_type cli::request_player_type(const symbol _player_symbol) {
    output_ << "Is player " + to_string(_player_symbol) + " human or computer? [h/c] ";

    while(true) {
        std::string player_type_input;
        input_ >> player_type_input;

        if(player_type_input == "h") {
            return player_type::human;
        }
        if(player_type_input == "c") {
            return player_type::computer;
        }

        output_ << "Unexpected input \"" + player_type_input + "\". Please inupt either \"h\" or \"c\"." << std::endl;
    }
}

bot_type cli::request_bot_type(const symbol _symbol) {
    output_ << "Is bot " + to_string(_symbol) + " naive or perfect? [n/p] ";

    while(true) {
        std::string bot_type_input;
        input_ >> bot_type_input;

        if(bot_type_input == "n") {
            return bot_type::naive;
        }
        if(bot_type_input == "p") {
            return bot_type::perfect;
        }

        output_ << "Unexpected input \"" + bot_type_input + "\". Please inupt either \"n\" or \"p\"." << std::endl;
    }
}

void cli::report_already_occupied_square(const std::pair<col, row> _coordinates, const game& _game) {
    output_ <<
        "Invalid move of symbol " +
        to_string( _game.get_player_to_move_now().get_symbol() ) +
        " to already occupied coordinates " +
        to_string(_coordinates.first) + to_string(_coordinates.second)
        + "."
        << std::endl;
}

std::pair<col, row> cli::get_next_move(const game& _game) {
    while(true) {
        output_ <<
            "Player " + to_string( _game.get_player_to_move_now().get_symbol() ) + ", "
            "please input coordinates of your move as '[abc][123]' (e. g. 'b3'): ";
        std::string new_move_input;

        try {
            input_ >> new_move_input;

            return parse_move_input( new_move_input );
        } catch(const invalid_move_input_syntax&) {
            output_ <<
                "Player " + to_string( _game.get_player_to_move_now().get_symbol() ) + ", "
                "your input '" + new_move_input +"' is not a valid input of the form '[abc][123]' (e. g. 'b3'). "
                << std::endl;
        }
    }
}

void cli::report_players_setup_started() { }

void cli::report_game_started(const game& _game) {
    output_ << to_string(_game.get_board_state()) << std::endl;
}

void cli::report_turn_started(const game& _game) {
    output_ << "Player " + to_string( _game.get_player_to_move_now().get_symbol() ) + " is playing. " << std::endl;
}

void cli::report_board_was_changed(const game& _game) {
    output_ << to_string(_game.get_board_state());
}

void cli::report_victory(const game& _game) {
    const optional<player> winner = _game.get_winner();
    if(winner) {
        output_
            << "Player '" + to_string( winner.value().get_symbol() ) +"' won!" << std::endl;
    }
}

void cli::report_tie(const game& _game) {
    if( _game.is_tie() ) {
        output_
            << "Tie." << std::endl;
    }
}

void cli::report_error(const std::string& _msg) {
    output_ << "Error: " << _msg << std::endl;
}
