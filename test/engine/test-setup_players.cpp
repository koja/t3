#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "src/engine/setup_players.hpp"
#include "test/mock_ui.hpp"

BOOST_AUTO_TEST_SUITE(test_setup_players)

BOOST_AUTO_TEST_CASE(test_setup_players_has_different_symbols)
{
    std::shared_ptr<mock_ui> ui { new mock_ui{ std::vector<std::pair<col, row>>{} } };

    player_controllers player_ctrls = setup_players(ui);

    /* defined by mock_ui::get_player_type() */

    BOOST_CHECK( player_ctrls.get_players().at(0) != player_ctrls.get_players().at(1) );
}

BOOST_AUTO_TEST_SUITE_END()
