set(BUZZER_SRC
        dev/modules/buzzer_module/buzzer_interface.cpp
        dev/modules/buzzer_module/buzzer_scheduler.cpp)
set(CAN_SRC
        dev/modules/can_module/can_interface.cpp)
set(RM_MOTOR_SRC
        dev/modules/rm_motor_interface/can_motor_feedback.cpp
        dev/modules/rm_motor_interface/can_motor_interface.cpp)
set(SHELL_SRC
        dev/modules/usb_serial_module/usb_serial_interface.cpp
        dev/modules/shell_module/shell_base.c
        dev/modules/shell_module/shell_base_cmd.c
        dev/modules/shell_module/shell_dbg_cmd.cpp
        dev/modules/shell_module/shell.cpp
        dev/modules/shell_module/printf.c
)

set(AHRS_LIB
        ${PROJECT_SOURCE_DIR}/modules/ahrs_module/ahrs_lib.lib)

set(AHRS_SRC
        dev/modules/ahrs_module/ahrs_lib_middleware.c
        dev/modules/ahrs_module/ahrs_math.hpp
        dev/modules/ahrs_module/ahrs.cpp)
if (${BOARD_NAME} STREQUAL rm_board_2018a)
    set(AHRS_SRC ${AHRS_SRC}
            dev/modules/ahrs_module/board_2018a_interface/imu_interface.cpp)
    include_directories(dev/modules/ahrs_module/board_2018a_interface)
elseif (${BOARD_NAME} STREQUAL rm_board_c)
    set(AHRS_SRC ${AHRS_SRC}
            dev/modules/ahrs_module/board_c_interface/imu_interface.cpp)
    include_directories(dev/modules/ahrs_module/board_c_interface)
endif ()

include_directories(dev/modules/buzzer_module)
include_directories(dev/modules/can_module)
include_directories(dev/modules/shell_module)
include_directories(dev/modules/usb_serial_module)
include_directories(dev/modules/ahrs_module)
include_directories(dev/modules/rm_motor_interface)
include_directories(dev/modules/pid_controller)
include_directories(dev/modules/common_files)
