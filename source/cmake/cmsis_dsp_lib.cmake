set(STM32F7_DSP_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/CMSIS/DSP)

# Make sure the lib is there
if (NOT EXISTS "${STM32F7_DSP_LIB_DIR}")
  message(FATAL_ERROR "STM32F7_DSP_LIB_DIR not found.")
endif()

include_directories(
  ${STM32F7_DSP_LIB_DIR}/Source/MatrixFunctions/
)

# Get all source files from the Source directory
set(STM32F7_DSP_LIB_SRC
    ${STM32F7_DSP_LIB_DIR}/Source/MatrixFunctions/arm_mat_init_f32.c
    ${STM32F7_DSP_LIB_DIR}/Source/SupportFunctions/arm_q15_to_float.c
    ${STM32F7_DSP_LIB_DIR}/Source/SupportFunctions/arm_q15_to_q7.c
    ${STM32F7_DSP_LIB_DIR}/Source/SupportFunctions/arm_float_to_q15.c
    ${STM32F7_DSP_LIB_DIR}/Source/SupportFunctions/arm_q7_to_q15.c
    ${STM32F7_DSP_LIB_DIR}/Source/SupportFunctions/arm_float_to_q7.c
    ${STM32F7_DSP_LIB_DIR}/Source/SupportFunctions/arm_q7_to_float.c
    ${STM32F7_DSP_LIB_DIR}/Source/BasicMathFunctions/arm_dot_prod_f32.c
    ${STM32F7_DSP_LIB_DIR}/Source/BasicMathFunctions/arm_shift_q7.c
    ${STM32F7_DSP_LIB_DIR}/Source/BasicMathFunctions/arm_shift_q15.c
)

set_source_files_properties(${STM32F7_DSP_LIB_SRC}
    PROPERTIES COMPILE_FLAGS ${STM32F7_DEFINES}
)

add_library(STM32F7_DSP_Lib STATIC ${STM32F7_DSP_LIB_SRC})
set_target_properties(STM32F7_DSP_Lib PROPERTIES LINKER_LANGUAGE C)

set(EXTERNAL_EXECUTABLES ${EXTERNAL_EXECUTABLES} ${STARTUP_ASM_FILE})

set(EXTERNAL_LIBS ${EXTERNAL_LIBS} STM32F7_DSP_Lib)