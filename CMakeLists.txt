cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

project(chess_opening)
# Adding Qt dependency
find_package(Qt5Widgets 5 REQUIRED)

# testing pakage
find_package(GTest REQUIRED CONFIG)
# Qt requierement
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(chess_logic)
add_library(opening_gui)

add_subdirectory(src)


target_link_libraries(opening_gui PUBLIC Qt5::Widgets)
target_link_libraries(opening_gui PRIVATE chess_logic)

target_link_libraries(opening_gui_exe opening_gui)

target_link_libraries(chess_logic_exe chess_logic)

target_link_libraries(logic_test PUBLIC chess_logic)
target_link_libraries(logic_test PUBLIC GTest::gtest_main)