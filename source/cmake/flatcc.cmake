set(FLATCC_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/flatcc)

# Make sure that git submodule is initialized and updated
if (NOT EXISTS "${FLATCC_LIB_DIR}")
  message(FATAL_ERROR "FLATCC_LIB_DIR not found. Initialize with 'git submodule update --init' in the source directory")
endif()

include_directories(
  ${FLATCC_LIB_DIR}/include
)

# Get all source files from the Source directory
set(FLATCC_LIB_DIR_SRC
    ${FLATCC_LIB_DIR}/src/runtime/verifier.c
    ${FLATCC_LIB_DIR}/src/runtime/builder.c
    ${FLATCC_LIB_DIR}/src/runtime/json_parser.c
    ${FLATCC_LIB_DIR}/src/runtime/emitter.c
    ${FLATCC_LIB_DIR}/src/runtime/json_printer.c
    ${FLATCC_LIB_DIR}/src/runtime/refmap.c
)

set_source_files_properties(${FLATCC_LIB_DIR_SRC}
    PROPERTIES COMPILE_FLAGS ${STM32F7_DEFINES}
)

add_library(FLATCC_Lib STATIC ${FLATCC_LIB_DIR_SRC})
set_target_properties(FLATCC_Lib PROPERTIES LINKER_LANGUAGE C)

set(EXTERNAL_EXECUTABLES ${EXTERNAL_EXECUTABLES} ${STARTUP_ASM_FILE})

set(EXTERNAL_LIBS ${EXTERNAL_LIBS} FLATCC_Lib)