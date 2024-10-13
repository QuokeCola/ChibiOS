# Created by liuzikai 2018-01-29

# =========== General Part ===========

cmake_minimum_required(VERSION 3.13)

include(cmake_config/toolchain.cmake)  # include cross compile configurations

set(CMAKE_CXX_STANDARD 14)

project(meta_embedded ASM C CXX)
# NOTICE: project() must be in CMakeList.txt, rather than any cmake file. It must be after toolchain configs and before
#         flag configs for CMake to test compiler.

include(cmake_config/board.cmake) # Board Check

include(cmake_config/compile_options.cmake)  # include compile flags and startup file option

# =========== Options ===========

set(CMAKE_VERBOSE_MAKEFILE OFF)  # Enable this if you want to see verbose log

# =========== Common Files and Targets Configurations ===========

include(os/ch.cmake)  # add files and directories from ChibiOS

include(modules.cmake)

add_subdirectory(lib/cmsis_dsp)

# Reuse ChibiOS object files (without linking) to avoid repeat compile
# They are included to every target at post configuration below

file(GLOB_RECURSE ALL_TARGETS ${PROJECT_SOURCE_DIR} application.cmake)
FOREACH(TARGET ${ALL_TARGETS})
    include(${TARGET})
ENDFOREACH()

# ================================= Post Configurations for all targets =================================

set(ELF_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(ELF_OUTPUT_NAME meta.elf)
add_definitions(-DBUILD_TARGET_NAME="$<TARGET_PROPERTY:NAME>")

get_directory_property(TARGET_LIST BUILDSYSTEM_TARGETS)

foreach (target ${TARGET_LIST})
    if (NOT ${target} STREQUAL "ChibiOS" AND NOT ${target} STREQUAL "CMSIS_DSP")  # OBJECT library doesn't have PRE_BUILD or POST_BUILD
        # Add ChibiOS files and common sources
        target_sources(${target} PRIVATE
                ${CHIBIOS_XASM_SRC}
                ${CHIBIOS_C_SRC}
                ${CHIBIOS_CPP_SRC}
                ${BASE_SRC}
                ${BOARD_FILES})

        # Link CMSIS DSP
        target_link_libraries(${target} CMSIS_DSP)

        # Echo target dev board before link
        add_custom_command(TARGET ${target} PRE_BUILD
                COMMENT "Build for ${BOARD_NAME}")

        # Run size utility after link to show the size of elf file
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND echo
                COMMAND ${CMAKE_SIZE_UTILITY} ${ELF_OUTPUT_PATH}/${ELF_OUTPUT_NAME}
                COMMAND echo)  # execute size utility to show size of executable file

        # Set unique output file
        set_target_properties(${target} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${ELF_OUTPUT_PATH}
                OUTPUT_NAME ${ELF_OUTPUT_NAME})  #
    endif ()
endforeach (target)