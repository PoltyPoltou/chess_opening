add_executable(logic_test)
target_sources(logic_test PRIVATE
    test.cpp
)

target_include_directories(logic_test PUBLIC ${CMAKE_CURRENT_LIST_DIR})