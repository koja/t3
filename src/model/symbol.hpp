#ifndef symbol_053010867765
#define symbol_053010867765

enum class symbol {x, o};

/** @returns symbol of the other player. */
constexpr symbol other_symbol(const symbol _in) {
    return
        _in == symbol::x
        ? symbol::o
        : symbol::x;
}

#endif
