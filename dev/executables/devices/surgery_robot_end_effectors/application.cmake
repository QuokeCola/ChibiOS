add_executable(surgery_robot_end_effectors
        ${CAN_SRC}
        ${BUZZER_SRC}
        ${CMAKE_CURRENT_LIST_DIR}/cfg/can_motor_config.cpp
        ${RM_MOTOR_SRC}
        ${SHELL_SRC}
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_include_directories(surgery_robot_end_effectors PRIVATE ${CMAKE_CURRENT_LIST_DIR}/cfg)