cmake_minimum_required(VERSION 3.8)
project(8085_MP_sim LANGUAGES C CXX)

set(BUILD_SHARED_LIBS OFF)

# Force static SDL build
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch SDL3
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.2
)
FetchContent_MakeAvailable(SDL3)

# Fetch ImGui docking
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

# Build ImGui as a library with SDL3 Renderer backend
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp

    # ImGui SDL3 + SDL Renderer backends
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

# Link SDL3
target_link_libraries(imgui PUBLIC SDL3::SDL3)

include_directories(${CMAKE_SOURCE_DIR}/InstructionHeaders)

file(GLOB_RECURSE APP_SOURCES
    "${CMAKE_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_SOURCE_DIR}/Source/*.c"
)

add_executable(8085_MP_sim
    ${APP_SOURCES}
    Headers/UIManager.h
    Headers/Head_2.h
    Headers/IODevice.h
    Headers/tinyfiledialogs.h
    Source/IODevice.cpp
    Headers/Parsing/token.h
    Headers/Parsing/Lexer.h
    Source/Parsing_Imp/lexer.cpp
    Source/Compiler.cpp
)

# Link SDL3 + ImGui
target_link_libraries(8085_MP_sim PRIVATE SDL3::SDL3 imgui)

# Add project include paths
target_include_directories(8085_MP_sim PRIVATE
    ${CMAKE_SOURCE_DIR}/Headers
    ${CMAKE_SOURCE_DIR}/Headers/Parsing
)


if (CMAKE_BUILD_TYPE MATCHES Release)
    if (UNIX)
        add_custom_command(TARGET 8085_MP_sim POST_BUILD COMMAND strip $<TARGET_FILE:8085_MP_sim>)
    endif()
endif()
