add_library(game STATIC
  ball.cpp
  hud_layer.cpp
  game_layer.cpp
)

find_package(raylib REQUIRED)

target_link_libraries(game PRIVATE core raylib)

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
