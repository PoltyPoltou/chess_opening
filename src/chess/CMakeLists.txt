target_sources(chess_opening PRIVATE
    boardutility.h
    chess.cpp
    chess.h
    )

target_include_directories(chess_opening PUBLIC ${CMAKE_CURRENT_LIST_DIR})
