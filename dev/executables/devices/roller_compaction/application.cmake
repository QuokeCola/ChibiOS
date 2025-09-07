add_executable(roller_compaction
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CAN_SRC}
        ${CMAKE_CURRENT_LIST_DIR}/cfg/can_motor_config.cpp
        ${RM_MOTOR_SRC})
target_include_directories(roller_compaction PRIVATE ${CMAKE_CURRENT_LIST_DIR}/cfg)