target_sources(opening_gui PRIVATE
mainwindow.cpp
mainwindow.h
tile.cpp
tile.h
chessboard.h
chessboard.cpp
)

target_include_directories(opening_gui PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(opening_gui PUBLIC ui)