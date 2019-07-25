set(FLATBUFFERS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/flatbuffers)

# Make sure that git submodule is initialized and updated
if (NOT EXISTS "${FLATBUFFERS_LIB_DIR}")
  message(FATAL_ERROR "FLATBUFFERS_LIB_DIR not found.")
endif()

include_directories(
  ${FLATBUFFERS_LIB_DIR}/include
)
