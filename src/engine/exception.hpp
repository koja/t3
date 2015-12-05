#ifndef exception_9876453215
#define exception_9876453215

#include "src/exception_intf.hpp"

struct missing_player_type_setup : exception_intf {
    const char* what() const override { return "missing_player_type_setup"; }
};

struct missing_bot_type_setup : exception_intf {
    const char* what() const override { return "missing_bot_type_setup"; }
};

struct game_already_ended : exception_intf {
    const char* what() const override { return "game_already_ended"; }
};

struct duplicate_definition_for_one_player : exception_intf {
    const char* what() const override { return "duplicate_definition_for_one_player"; }
};

struct no_coordinates_provider_for_given_player : exception_intf {
    const char* what() const override { return "no_coordinates_provider_for_given_player"; }
};

#endif
