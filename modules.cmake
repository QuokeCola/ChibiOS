set(BUZZER_SRC
        dev/modules/buzzer_module/buzzer_interface.cpp
        dev/modules/buzzer_module/buzzer_scheduler.cpp)
set(CAN_SRC
        dev/modules/can_module/can_interface.cpp)

include_directories(dev/modules/buzzer_module)
include_directories(dev/modules/can_module)
include_directories(dev/common_files)