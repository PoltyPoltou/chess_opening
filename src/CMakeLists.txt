target_sources(chess_opening PRIVATE
    main.cpp
    )

target_include_directories(chess_opening PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(chess)
add_subdirectory(gui)