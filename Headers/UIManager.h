#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>
#include <vector>
#include <string>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include "../Headers/tinyfiledialogs.h"
#include "../Headers/CPU.h"
#include <fstream>


class UIManager {
public:
    UIManager(SDL_Window* window, SDL_Renderer* renderer, const Registers& reg, const vector<uint8_t>&);
    ~UIManager();

    bool        Init();
    void        Shutdown();
    void        ProcessEvent(const SDL_Event& event);
    void        BeginFrame();
    void        RenderFrame();
    void        Draw();
    const char* GetFilePath();
    bool        IsFileLoaded();
    bool        CpuCanStep();

private:
    void DrawFileView(float height);
    void LoadFileLines();
    void DrawRegisterView(float height);
    void DrawControls(float height);
    void DrawMemoryView(float height);
    void Reset();

private:
    SDL_Window*     m_window;
    SDL_Renderer*   m_renderer;
    bool            m_file_loaded;
    std::string     m_file_path;
    
    const Registers&            m_cpuState;
    const vector<uint8_t>&      m_memoryView;
    std::vector<std::string>    m_file_lines;

public:
    bool            programPaused;
    bool            stepMode;
    bool            cpuResetTriggered;
    int             stepCycle;
    int             currentInstruction;
};
