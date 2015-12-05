#set(CMAKE_VERBOSE_MAKEFILE ON)

cmake_minimum_required(VERSION 3.0)

project(t3 CXX)

# I really want -std=c++14, not -std=gnu++14
set(CMAKE_CXX_EXTENSIONS OFF )
set(CMAKE_CXX_STANDARD 14 )

# I don't want to set() compiler here to be able to use scan-build (which works by setting scanner as a compiler).
# At the same time, don't want to hassle with portability and want to enforce clang++ >= 3.6 is used.
if (NOT CMAKE_CXX_COMPILER MATCHES ".*clang")
    message(FATAL_ERROR "Please use clang++ (3.6 or newer) compiler.")
endif()
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.6)
    message(FATAL_ERROR "Clang version ${CMAKE_CXX_COMPILER_VERSION} is older than 3.6 - debugging symbols for auto might not work.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-weak-vtables -Wno-missing-braces")

find_package( Boost REQUIRED )
find_package( Boost COMPONENTS unit_test_framework REQUIRED)

include_directories ("${CMAKE_SOURCE_DIR}" "${Boost_INCLUDE_DIR}")

add_library(
    model
    src/model/board.cpp
    src/model/game.cpp
    src/model/line.cpp
    src/model/player.cpp
    src/model/scoring_util.cpp
)

add_library(
    engine
    src/engine/engine.cpp
    src/engine/player_controllers.cpp
    src/engine/setup_players.cpp
)

add_library(
    bot
    src/bot/basic_moves_impl.cpp
    src/bot/board_util_impl.cpp
    src/bot/naive_bot.cpp
    src/bot/perfect_bot.cpp
)

add_library(
    cli
    src/ui/cli.cpp
)

add_executable(
    t3
    src/main.cpp
)

target_link_libraries(t3 cli engine bot model)

set(ADDITIONAL_TEST_CXX_FLAGS "-Wno-global-constructors -Wno-c++98-compat-pedantic")

add_executable(
    test-model
    test/model/main.cpp
    test/model/test-board.cpp
    test/model/test-coordinates.cpp
    test/model/test-game.cpp
    test/model/test-line.cpp
    test/model/test-player.cpp
    test/model/test-scoring_util.cpp
    test/model/test-symbol.cpp
)
set_target_properties(test-model PROPERTIES COMPILE_FLAGS "${ADDITIONAL_TEST_CXX_FLAGS}")
target_link_libraries(test-model model ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_executable(
    test-engine
    test/engine/main.cpp
    test/engine/test-engine.cpp
    test/engine/test-player_controllers.cpp
    test/engine/test-setup_players.cpp
)
set_target_properties(test-engine PROPERTIES COMPILE_FLAGS "${ADDITIONAL_TEST_CXX_FLAGS}")
target_link_libraries(test-engine engine bot model ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_executable(
    test-bot
    test/bot/main.cpp
    test/bot/test-naive_never_throw.cpp
    test/bot/test-perfect_never_lose.cpp
)
set_target_properties(test-bot PROPERTIES COMPILE_FLAGS "${ADDITIONAL_TEST_CXX_FLAGS}")
target_link_libraries(test-bot bot cli model ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_executable(
    test-cli
    test/cli/main.cpp
    test/cli/test-cli.cpp
)
set_target_properties(test-cli PROPERTIES COMPILE_FLAGS "${ADDITIONAL_TEST_CXX_FLAGS}")
target_link_libraries(test-cli cli model ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file("${CMAKE_SOURCE_DIR}/Doxyfile.in" "${CMAKE_BINARY_DIR}/Doxyfile" @ONLY)
    add_custom_target(
        doc
        COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        COMMENT "Generating source code documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)
