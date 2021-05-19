target_sources(chess_opening PRIVATE
    mainwindow.cpp
    mainwindow.h
    tile.cpp
    tile.h
    chessboard.h
    chessboard.cpp
    )

target_include_directories(chess_opening PUBLIC ${CMAKE_CURRENT_LIST_DIR})
