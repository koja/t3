#ifndef test_util_h_54541340320
#define test_util_h_54541340320

#include <experimental/optional>
using std::experimental::optional;
#include <map>
#include <ostream>
#include <string>
#include "src/model/board.hpp"
#include "src/ui/cli.hpp"

namespace boost {
namespace test_tools {

inline std::string to_string(symbol _sym) {
    return _sym == symbol::x ? "x" : "o";
}

template<> inline void print_log_value<symbol>::operator()(
    std::ostream& _output,
    const symbol& _sym
) {
    _output << to_string(_sym);
}

template<> inline void print_log_value<std::map<symbol, unsigned int>>::operator()(
    std::ostream& _output,
    const std::map<symbol, unsigned int>& _map
) {
    for(const auto& elem : _map) {
        _output <<
            "{" +
            to_string(elem.first) +
            "," +
            std::to_string(elem.second) +
            "}";
    }
}

template<> inline void print_log_value<std::experimental::optional<symbol>>::operator()(
    std::ostream& _output,
    const std::experimental::optional<symbol>& _sym
) {
    _output << (_sym ? to_string( _sym.value() ) : "[null]");
}

}
}

inline bool equal(const board& lhs, const board& rhs) {
    for( const col c : get_ordered_col_values() ) {
        for( const row r : get_ordered_row_values() ) {
            const optional<symbol> lhs_sym = lhs.get_symbol(c, r);
            const optional<symbol> rhs_sym = rhs.get_symbol(c, r);

            if( (!lhs_sym && rhs_sym) || (lhs_sym && !rhs_sym) ) {
                return false;
            }

            if( !lhs_sym && !rhs_sym ) {
                continue;
            }

            if( lhs_sym.value() != rhs_sym.value() ) {
                return false;
            }
        }
    }

    return true;
}

#endif
