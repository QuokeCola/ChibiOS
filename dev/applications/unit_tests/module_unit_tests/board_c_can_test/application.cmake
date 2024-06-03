add_executable(board_c_can_test
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CAN_SRC})
target_include_directories(board_c_can_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/cfg)