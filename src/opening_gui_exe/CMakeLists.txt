add_executable(opening_gui_exe)
target_sources(opening_gui_exe PRIVATE
    main.cpp
    )

target_include_directories(opening_gui_exe PUBLIC ${CMAKE_CURRENT_LIST_DIR})
