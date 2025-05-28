cmake_minimum_required(VERSION 3.8)
project(8085_MP_sim LANGUAGES C CXX)

# 1) Force static builds of everything
set(BUILD_SHARED_LIBS OFF)                       # globally disable all SHARED targets
option(SDL_STATIC      "Build SDL3 as static"    ON)
option(SDL_SHARED      "Build SDL3 as shared"    OFF)
option(SDL_TEST        "Build SDL3 tests"        OFF)

# 2) For MSVC: link the runtime library statically (/MT instead of /MD)
if (MSVC)
  # CMake ≥3.15
  set(CMAKE_MSVC_RUNTIME_LIBRARY 
      "MultiThreaded$<$<CONFIG:Debug>:Debug>")    
endif()

# For MinGW: also pull in libgcc/libstdc++ statically
if (MINGW)
  set(CMAKE_EXE_LINKER_FLAGS 
      "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# 3) Turn on C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add third-party SDL and ImGui
add_subdirectory(thirdparty/SDL-main)       # <-- your SDL3 source tree
add_subdirectory(thirdparty/imgui-docking)

# Your include paths
include_directories(
    ${CMAKE_SOURCE_DIR}/InstructionHeaders
)

# Gather sources
file(GLOB_RECURSE APP_SOURCES
    "${CMAKE_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_SOURCE_DIR}/Source/*.c"
)

# Define executable
add_executable(8085_MP_sim
    ${APP_SOURCES}
    Headers/UIManager.h
    Headers/Head_2.h
    Headers/IODevice.h
    Headers/tinyfiledialogs.h
    Source/IODevice.cpp
 "Headers/Parsing/token.h" "Headers/Parsing/Lexer.h" "Source/Parsing_Imp/lexer.cpp")

# 4) Link libs: SDL3::SDL3main pulls in SDL3 as static (because SDL_STATIC is ON)
#    and supplies WinMain→main glue on Windows.
target_link_libraries(8085_MP_sim PRIVATE
    SDL3::SDL3
    imgui
)

# (Optionally) strip symbols on Release
if (CMAKE_BUILD_TYPE MATCHES Release)
  if (UNIX)
    add_custom_command(TARGET 8085_MP_sim
      POST_BUILD COMMAND strip $<TARGET_FILE:8085_MP_sim>
    )
  endif()
endif()
