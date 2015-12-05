#include "src/model/scoring_util.hpp"

#include <algorithm>
#include <map>
#include <set>
#include <utility>

#include "src/model/exception.hpp"

std::set<line> get_all_scoring_lines() {
    using col::_a;
    using col::_b;
    using col::_c;

    using row::_1;
    using row::_2;
    using row::_3;

    typedef std::array< std::pair<col, row>, 3 > arr;

    return {
        line{ arr{ std::make_pair(_a, _1), std::make_pair(_b, _1), std::make_pair(_c, _1) } },
        line{ arr{ std::make_pair(_a, _2), std::make_pair(_b, _2), std::make_pair(_c, _2) } },
        line{ arr{ std::make_pair(_a, _3), std::make_pair(_b, _3), std::make_pair(_c, _3) } },

        line{ arr{ std::make_pair(_a, _1), std::make_pair(_a, _2), std::make_pair(_a, _3) } },
        line{ arr{ std::make_pair(_b, _1), std::make_pair(_b, _2), std::make_pair(_b, _3) } },
        line{ arr{ std::make_pair(_c, _1), std::make_pair(_c, _2), std::make_pair(_c, _3) } },

        line{ arr{ std::make_pair(_a, _1), std::make_pair(_b, _2), std::make_pair(_c, _3) } },
        line{ arr{ std::make_pair(_a, _3), std::make_pair(_b, _2), std::make_pair(_c, _1) } }
    };
}

std::map<symbol, unsigned> count_symbols_on_line(const board& _board, const line& _line) {
    std::map<symbol, unsigned> result{ std::make_pair(symbol::x, 0), std::make_pair(symbol::o, 0) };

    for(const auto& square : _line) {
        const optional<symbol> symbol = _board.get_symbol(square);
        if(symbol) {
            result.at( symbol.value() )++;
        }
    }

    return result;
}
