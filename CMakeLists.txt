# Created by liuzikai 2018-01-29

# =========== General Part ===========

cmake_minimum_required(VERSION 3.10)
include(cmake_config/toolchain.cmake)  # include cross compile configurations

set(CMAKE_CXX_STANDARD 14)

# Check dev board definition
# NOTICE: ${BOARD_NAME} needs to be specific externally
# NOTICE: if you want to adapt this project to a new board, be sure to also set startup file in compile_options.cmake
## Default board: RM Board 2018 A
if (NOT DEFINED BOARD_NAME)
    set(BOARD_NAME rm_board_2018_a)
    #    message(FATAL_ERROR "[ERROR] No specific dev board. Do you forget to add -DBOARD_NAMD=\"***\" to CMake options?")
endif ()

if ((${BOARD_NAME} STREQUAL rm_board_2017) OR (${BOARD_NAME} STREQUAL rm_board_2018_a))
    message("[Notice] Current profile is configurated for dev board \"${BOARD_NAME}\".")
else ()
    message(FATAL_ERROR "[ERROR] Dev board \"${BOARD_NAME}\" is not configured.")
endif ()

project(meta_embedded ASM C CXX)
# NOTICE: project() must be in CMakeList.txt, rather than any cmake file. It must be after toolchain configs and before
#         flag configs for CMake to test compiler.

include(cmake_config/compile_options.cmake)  # include compile flags and startup file option

# =========== Options ===========

set(CMAKE_VERBOSE_MAKEFILE OFF)  # Enable this if you want to see verbose log


# =========== Common Files and Targets Configurations ===========

include(os/ch.cmake)  # add files and directories from ChibiOS

add_subdirectory(os/common/abstractions/cmsis_dsp)

include_directories(os/hal/boards/ST_STM32F4_DISCOVERY)  # include board configs
include_directories(dev/applications/RT-STM32F407-DISCOVERY-G++/cfg)
# Reuse ChibiOS object files (without linking) to avoid repeat compile
# They are included to every target at post configuration below
add_library(ChibiOS OBJECT ${CHIBIOS_XASM_SRC} ${CHIBIOS_C_SRC} ${CHIBIOS_CPP_SRC} os/hal/boards/ST_STM32F4_DISCOVERY/board.c)

# Gimbal: include CANInterface, GimbalInterface, GimbalController, GimbalFeedbackThread and adjustment modules.

add_executable(demo_stm32
        dev/applications/RT-STM32F407-DISCOVERY-G++/main.cpp)
target_include_directories(demo_stm32 PRIVATE dev/applications/RT-STM32F407-DISCOVERY-G++/cfg
        test/rt/source/test
        os/test/include
        test/oslib/source/test)

# ================================= Post Configurations for all targets =================================

# Make all targets compile to this filename to allow upload script to work properly
set(ELF_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_definitions(-DBUILD_TARGET_NAME="$<TARGET_PROPERTY:NAME>")

get_directory_property(TARGET_LIST BUILDSYSTEM_TARGETS)
foreach (target ${TARGET_LIST})
    if (NOT ${target} STREQUAL "ChibiOS" AND NOT ${target} STREQUAL "CMSIS_DSP")  # OBJECT library doesn't have PRE_BUILD or POST_BUILD
        # Add ChibiOS files and common sources
        target_sources(${target} PRIVATE $<TARGET_OBJECTS:ChibiOS> ${BASE_SRC})

        # Link CMSIS DSP
        target_link_libraries(${target} CMSIS_DSP)

        # Echo target dev board before link
        add_custom_command(TARGET ${target} PRE_BUILD
                COMMENT "Build for ${BOARD_NAME}")

        # Run size utility after link to show the size of elf file
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_SIZE_UTILITY} ${ELF_OUTPUT_PATH}/${target}.elf
        )  # execute size utility to show size of executable file

        # Set unique output file
        set_target_properties(${target} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${ELF_OUTPUT_PATH}
                OUTPUT_NAME ${target}.elf)  #
    endif ()
endforeach (target)