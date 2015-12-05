#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "src/engine/player_controllers.hpp"
#include "test/mock_coordinates_provider.hpp"

BOOST_AUTO_TEST_SUITE(test_player_controllers)

BOOST_AUTO_TEST_CASE(test_get_coordinates_provider)
{
    const player player_1 {symbol::x};
    const player player_2 {symbol::o};

    player_controllers test_controllers{
        player_1,
        std::shared_ptr<move_coordinates_provider_intf>( new mock_coordinates_provider{col::_a, row::_1} ),
        player_2,
        std::shared_ptr<move_coordinates_provider_intf>( new mock_coordinates_provider{col::_b, row::_2} )
    };

    game test_game_1{
        {player_1, player_2},
        board{}
    };

    BOOST_CHECK(
        test_controllers.get_coordinates_provider(player_1)->get_next_move(test_game_1)
        ==
        std::make_pair(col::_a, row::_1)
    );

    game test_game_2{
        {player_2, player_1},
        board{}
    };
    BOOST_CHECK(
        test_controllers.get_coordinates_provider(player_2)->get_next_move(test_game_2)
        ==
        std::make_pair(col::_b, row::_2)
    );
}

BOOST_AUTO_TEST_CASE(test_get_players)
{
    const player player_x {symbol::x};
    const player player_o {symbol::o};

    {
        player_controllers test_controllers_1{
            player_x,
            std::shared_ptr<move_coordinates_provider_intf>( new mock_coordinates_provider{col::_a, row::_1} ),
            player_o,
            std::shared_ptr<move_coordinates_provider_intf>( new mock_coordinates_provider{col::_b, row::_2} )
        };
        const std::array<player, 2> etalon_1{player_x, player_o};

        BOOST_CHECK( test_controllers_1.get_players() ==  etalon_1);
    }

    {
        player_controllers test_controllers_2{
            player_o,
            std::shared_ptr<move_coordinates_provider_intf>( new mock_coordinates_provider{col::_a, row::_1} ),
            player_x,
            std::shared_ptr<move_coordinates_provider_intf>( new mock_coordinates_provider{col::_b, row::_2} )
        };

        const std::array<player, 2> etalon_2{player_o, player_x};

        BOOST_CHECK( test_controllers_2.get_players() == etalon_2 );
    }
}

BOOST_AUTO_TEST_SUITE_END()
