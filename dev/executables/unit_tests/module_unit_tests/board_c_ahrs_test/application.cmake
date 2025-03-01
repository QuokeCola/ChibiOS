add_executable(board_c_ahrs_test
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${AHRS_SRC})
target_include_directories(board_c_ahrs_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/cfg)