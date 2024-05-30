# Check dev board definition
# NOTICE: ${BOARD_NAME} needs to be specific externally
# NOTICE: if you want to adapt this project to a new board, be sure to also set startup file in compile_options.cmake
## Default board: RM Board 2018 A
if (NOT DEFINED BOARD_NAME)
    set(BOARD_NAME rm_board_2018_a)
    message("[Notice] No specific dev board. Do you forget to add -DBOARD_NAME=\"***\" to CMake options?")
endif ()

message("${STARTUP_LD_DICT}\".")
if (${BOARD_NAME} STREQUAL rm_board_2017)
    ###################################################
    # Startup LD directory and LD file and board file #
    ###################################################
    set(STARTUP_LD_DICT ${PROJECT_SOURCE_DIR}/os/common/startup/ARMCMx/compilers/GCC/ld)
    set(STARTUP_LD_FILE ${STARTUP_LD_DICT}/STM32F429xI.ld)

    ###################################
    # Include board configs and files #
    ###################################
    include_directories(${PROJECT_SOURCE_DIR}/os/hal/boards/ST_STM32F427_ROBOMASTER_2017)  # include board configs
    set(BOARD_FILES ${PROJECT_SOURCE_DIR}/os/hal/boards/ST_STM32F427_ROBOMASTER_2017/board.c)

    message("[Notice] Current profile is configured for dev board \"${BOARD_NAME}\".")
elseif (${BOARD_NAME} STREQUAL rm_board_2018_a)
    ###################################################
    # Startup LD directory and LD file and board file #
    ###################################################
    set(STARTUP_LD_DICT ${PROJECT_SOURCE_DIR}/os/common/startup/ARMCMx/compilers/GCC/ld)
    set(STARTUP_LD_FILE ${STARTUP_LD_DICT}/STM32F429xI.ld)

    ###################################
    # Include board configs and files #
    ###################################
    include_directories(${PROJECT_SOURCE_DIR}/os/hal/boards/ST_STM32F427_ROBOMASTER_2018A)  # include board configs
    set(BOARD_FILES ${PROJECT_SOURCE_DIR}/os/hal/boards/ST_STM32F427_ROBOMASTER_2018A/board.c)

    message("[Notice] Current profile is configured for dev board \"${BOARD_NAME}\".")
elseif (${BOARD_NAME} STREQUAL rm_board_c)
    ###################################################
    # Startup LD directory and LD file and board file #
    ###################################################
    set(STARTUP_LD_DICT ${PROJECT_SOURCE_DIR}/os/common/startup/ARMCMx/compilers/GCC/ld)
    set(STARTUP_LD_FILE ${STARTUP_LD_DICT}/STM32F407xG.ld)

    ###################################
    # Include board configs and files #
    ###################################
    include_directories(${PROJECT_SOURCE_DIR}/os/hal/boards/ST_STM32F407_ROBOMASTER_C)
    set(BOARD_FILES     ${PROJECT_SOURCE_DIR}/os/hal/boards/ST_STM32F407_ROBOMASTER_C/board.c)

    message("[Notice] Current profile is configured for dev board \"${BOARD_NAME}\".")
elseif (${BOARD_NAME} STREQUAL st_stm32f407_discovery)
    ###################################################
    # Startup LD directory and LD file and board file #
    ###################################################
    set(STARTUP_LD_DICT ${PROJECT_SOURCE_DIR}/os/common/startup/ARMCMx/compilers/GCC/ld)
    set(STARTUP_LD_FILE ${STARTUP_LD_DICT}/STM32F407xG.ld)

    ###################################
    # Include board configs and files #
    ###################################
    include_directories(${PROJECT_SOURCE_DIR}/os/hal/boards/ST_STM32F4_DISCOVERY)
    set(BOARD_FILES     ${PROJECT_SOURCE_DIR}/os/hal/boards/ST_STM32F4_DISCOVERY/board.c)

    message("[Notice] Current profile is configured for dev board \"${BOARD_NAME}\".")
else ()
    message(FATAL_ERROR "[ERROR] Dev board \"${BOARD_NAME}\" is not configured." )
endif ()
