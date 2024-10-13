add_executable(board_c_rm_motor_test
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CAN_SRC}
        ${CMAKE_CURRENT_LIST_DIR}/cfg/can_motor_config.cpp
        ${RM_MOTOR_SRC})
target_include_directories(board_c_rm_motor_test PRIVATE cfg)