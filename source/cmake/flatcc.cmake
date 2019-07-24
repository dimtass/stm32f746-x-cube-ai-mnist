set(FLATCC_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/flatcc)

# Make sure that git submodule is initialized and updated
if (NOT EXISTS "${FLATCC_LIB_DIR}")
  message(FATAL_ERROR "FLATCC_LIB_DIR not found. Initialize with 'git submodule update --init' in the source directory")
endif()

include_directories(
    ${FLATCC_LIB_DIR}/
)
