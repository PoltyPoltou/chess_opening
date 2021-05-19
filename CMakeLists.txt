cmake_minimum_required(VERSION 3.16)

project(chess_opening)
# Adding Qt dependency
find_package(Qt5Widgets 5 REQUIRED)

# Qt requierement
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(chess_opening "")

add_subdirectory(src)

target_link_libraries(chess_opening Qt5::Widgets)