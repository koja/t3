#ifndef exception_8945331311
#define exception_8945331311

#include "src/exception_intf.hpp"

struct board_is_full : exception_intf {
    const char* what() const override { return "board_is_full"; }
};

struct bot_error : exception_intf {
    const char* what() const override { return "bot_error"; }
};

struct unknown_error : exception_intf {
    const char* what() const override { return "unknown_error"; }
};

#endif
