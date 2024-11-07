add_executable(cold_spray_blocker
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CAN_SRC}
        ${CMAKE_CURRENT_LIST_DIR}/cfg/can_motor_config.cpp
        ${RM_MOTOR_SRC})
target_include_directories(cold_spray_blocker PRIVATE ${CMAKE_CURRENT_LIST_DIR}/cfg)