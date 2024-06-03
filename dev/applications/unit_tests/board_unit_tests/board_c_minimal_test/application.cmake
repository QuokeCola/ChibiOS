add_executable(board_c_minimal_test
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_include_directories(board_c_minimal_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/cfg)