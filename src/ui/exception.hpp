#ifndef exception_9324789013
#define exception_9324789013

#include "src/exception_intf.hpp"

struct invalid_coordinate : exception_intf {
    const char* what() const override { return "invalid_coordinate"; }
};

struct invalid_symbol : exception_intf {
    const char* what() const override { return "invalid_symbol"; }
};

struct invalid_move_input_syntax : exception_intf {
    const char* what() const override { return "invalid_move_input_syntax"; }
};

#endif
