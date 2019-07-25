set(STM_AI_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/AI)

# Make sure the lib is there
if (NOT EXISTS "${STM_AI_LIB_DIR}")
  message(FATAL_ERROR "STM_AI_LIB_DIR not found.")
endif()

include_directories(
    ${STM_AI_LIB_DIR}/Inc
    ${CMAKE_SOURCE_DIR}libs/CMSIS/DSP/Source/MatrixFunctions/
)

find_library(ST_AI_Lib NetworkRuntime400_CM7_GCC ${CMAKE_SOURCE_DIR}/libs/AI/Lib/)

set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${ST_AI_Lib})