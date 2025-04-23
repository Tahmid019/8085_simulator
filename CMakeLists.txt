# CMakeList.txt : CMake project for 8085_MP_sim, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("8085_MP_sim")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/InstructionHeaders
)

# Collect all .cpp files
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/Source/*.cpp"
)

# Create the executable
add_executable(8085_MP_sim ${SOURCE_FILES} "Headers/Head_2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 8085_MP_sim PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
