set(BUZZER_SRC
        dev/modules/buzzer_module/buzzer_interface.cpp
        dev/modules/buzzer_module/buzzer_scheduler.cpp)
set(CAN_SRC
        dev/modules/can_module/can_interface.cpp)
set(SHELL_SRC
        dev/modules/shell_module/shell_base.c
        dev/modules/shell_module/shell_base_cmd.c
        dev/modules/shell_module/shell_dbg_cmd.cpp
        dev/modules/shell_module/shell.cpp)

include_directories(dev/modules/buzzer_module)
include_directories(dev/modules/can_module)
include_directories(dev/modules/shell_module)
include_directories(dev/modules/usb_serial)
include_directories(dev/common_files)