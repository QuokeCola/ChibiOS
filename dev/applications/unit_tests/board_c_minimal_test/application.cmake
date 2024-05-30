add_executable(board_c_minimal_test
        dev/applications/unit_tests/board_c_minimal_test/main.cpp)
target_include_directories(board_c_minimal_test PRIVATE dev/applications/unit_tests/board_c_minimal_test/cfg)