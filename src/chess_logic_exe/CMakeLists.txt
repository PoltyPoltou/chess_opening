add_executable(chess_logic_exe)

target_sources(chess_logic_exe PRIVATE
    main.cpp
    )

target_include_directories(chess_logic_exe PUBLIC ${CMAKE_CURRENT_LIST_DIR})
