add_library(core STATIC
  application.cpp
  clock.cpp
)

find_package(raylib REQUIRED)

target_link_libraries(core PRIVATE raylib)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
