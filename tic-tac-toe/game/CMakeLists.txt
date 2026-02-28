add_library(game STATIC
  game.cpp
)

find_package(raylib REQUIRED)

target_link_libraries(game PRIVATE raylib)

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
