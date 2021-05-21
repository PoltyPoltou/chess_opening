target_sources(chess_opening PRIVATE
    boardstate.cpp
    boardstate.h
    tile.cpp
    tile.h
    move.cpp
    move.h
    piece.h
    )

target_include_directories(chess_opening PUBLIC ${CMAKE_CURRENT_LIST_DIR})
