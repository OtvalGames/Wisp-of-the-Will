cmake_minimum_required(VERSION 3.5)

project(wotw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(wotw)

target_sources(wotw PRIVATE
    # Headers
    src/timer.hpp
    src/state.hpp

    src/asset_manager.hpp
    src/game.hpp
    src/game_over_state.hpp
    src/game_state.hpp
    src/main_menu_state.hpp
    src/obstacle.hpp
    src/pause_state.hpp
    src/player.hpp
    src/resources.hpp
    src/splash_state.hpp
    src/state_machine.hpp
    src/walls.hpp

    # Sources
    src/main.cpp

    src/asset_manager.cpp
    src/game.cpp
    src/game_over_state.cpp
    src/game_state.cpp
    src/main_menu_state.cpp
    src/obstacle.cpp
    src/pause_state.cpp
    src/player.cpp
    src/resources.cpp
    src/splash_state.cpp
    src/state_machine.cpp
    src/walls.cpp
)

add_custom_command(TARGET wotw
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
          $<TARGET_FILE_DIR:wotw>/res)

find_package(SFML COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(wotw sfml-graphics sfml-window sfml-system sfml-audio)

set_target_properties(wotw PROPERTIES LINK_FLAGS_RELEASE -s)

install(TARGETS wotw LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
