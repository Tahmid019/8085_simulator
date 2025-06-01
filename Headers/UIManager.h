#pragma once

#include "Head_1.h"
#include "CPU.h"


class UIManager {
private:
    void DrawFileView(float height);
    void LoadFileLines();
    void DrawRegisterView(float height);
    void DrawControls(float height);
    void DrawMemoryView(float height);
    void Reset();
    void Reload();

    SDL_Window*     m_window;
    SDL_Renderer*   m_renderer;
    bool            m_file_loaded;
    string     m_file_path;
    int             m_selected_addr;
    
    const Registers&            m_cpuState;
    vector<uint8_t>&       m_memoryView;
    vector<string>    m_file_lines;

    char m_codeInputBuffer[4096] = { 0 };
	vector<string> m_assembledLines;
    bool m_showCodeEditor = false;
    bool m_showAssembledCode = false;
    bool m_assemblerError = false;
	string m_assemblerErrorMsg;

    void DrawCodeEditor();
	void DrawAssembledCode();
    void AssembleCode();

    bool show_error_popup = false;
    string error_message;


public:
    UIManager(SDL_Window* window, SDL_Renderer* renderer, const Registers& reg, vector<uint8_t>& mem);
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
    bool        isCodeAssembled();
    vector<string> getAssembledCode();
    vector<string> getLoadedCode();
    void ShowErrorPopup();
	void SetError(const string& message);

    bool         programPaused;
    bool         stepMode;
    bool         executeAllMode;
    bool         cpuResetTriggered;
    bool         cpuReloadTriggered;
    int          stepCycle;
    int          currentInstruction;
};
