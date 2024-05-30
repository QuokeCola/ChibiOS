file(GLOB COMMON_FILES "src/CommonTables/*.c")
file(GLOB MATRIX_FP32_FILES "src/MatrixFunctions/*f32.c")
file(GLOB FAST_MATH_FP32_FILES "src/FastMathFunctions/*f32.c")
add_library(CMSIS_DSP STATIC ${COMMON_FILES} ${MATRIX_FP32_FILES} ${FAST_MATH_FP32_FILES})
target_include_directories(CMSIS_DSP PUBLIC
        include)
target_compile_definitions(CMSIS_DSP PUBLIC
        ARM_MATH_CM4
        ARM_MATH_MATRIX_CHECK
        ARM_MATH_ROUNDING
        __FPU_PRESENT=1U
        )
set_target_properties(CMSIS_DSP PROPERTIES LINKER_LANGUAGE C)