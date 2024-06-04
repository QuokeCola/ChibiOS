add_executable(board_c_shell_test
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${SHELL_SRC})
target_include_directories(board_c_shell_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/cfg)