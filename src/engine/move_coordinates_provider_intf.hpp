#ifndef move_coordinates_provider_intf_97641834846
#define move_coordinates_provider_intf_97641834846

#include <utility>

#include "src/model/coordinates.hpp"
#include "src/model/game.hpp"

class move_coordinates_provider_intf {
    public:
        virtual std::pair<col, row> get_next_move(const game& _game) = 0;
        virtual void report_already_occupied_square(const std::pair<col, row> _coordinates, const game& _game) = 0;

        virtual ~move_coordinates_provider_intf() = default;
};

#endif
