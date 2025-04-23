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

# Add source to this project's executable.
add_executable(8085_MP_sim
    Source/main.cpp
    Source/ALU.cpp
    Source/CPU.cpp
    Source/Instructions.cpp
    Source/InterruptControl.cpp
    Source/IO.cpp
    Source/IOHandler.cpp
    Source/Memory.cpp
    Source/Registers.cpp
    Source/utils.cpp
 "Headers/Parser.h" "Source/Parser.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 8085_MP_sim PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
