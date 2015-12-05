#ifndef mock_coordinates_provider_876356436631
#define mock_coordinates_provider_876356436631

#include <utility>

#include "src/model/coordinates.hpp"
#include "src/model/game.hpp"

struct mock_coordinates_provider : public move_coordinates_provider_intf {
    mock_coordinates_provider(const col _col, const row _row)
    :   coordinates( std::make_pair(_col, _row) )
    { }

    std::pair<col, row> get_next_move(const game&) override { return coordinates; }
    void report_already_occupied_square(const std::pair<col, row>, const game&) override { throw 0; }

    std::pair<col, row> coordinates;
};

#endif
