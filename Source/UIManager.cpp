#include "../Headers/UIManager.h"

UIManager::UIManager(SDL_Window* window, SDL_Renderer* renderer, const Registers& reg, const vector<uint8_t>& mem)
    : m_window(window)
    , m_renderer(renderer)
    , m_file_loaded(false)
    , m_cpuState(reg)
    , m_memoryView(mem)
    , stepMode(true)
    , stepCycle(0)
    , programPaused(true)
    , cpuResetTriggered(false)
    , currentInstruction(0)
{}

UIManager::~UIManager() {
    // no-op
}

bool UIManager::Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer3_Init(m_renderer);
    return true;
}

void UIManager::Shutdown() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::ProcessEvent(const SDL_Event& event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void UIManager::BeginFrame() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void UIManager::RenderFrame() {
    ImGui::Render();
    SDL_SetRenderDrawColor(m_renderer, 45, 45, 45, 255);
    SDL_RenderClear(m_renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
    SDL_RenderPresent(m_renderer);
}

void UIManager::Draw() {
    // Make window fill the entire viewport, non-movable, non-resizable, and no decoration
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::Begin("8085 Simulator", nullptr, flags);

    // Compute available content size excluding window borders (should be full window)
    ImVec2 avail = ImGui::GetContentRegionAvail();
    float halfH = avail.y * 0.5f;

    // Top row: File and Register views
    ImGui::Columns(2, "TopCols", true);
    DrawFileView(halfH);
    ImGui::NextColumn();
    DrawRegisterView(halfH);
    ImGui::Columns(1);

    ImGui::Separator();

    // Bottom row: Controls and Memory views
    ImGui::Columns(2, "BottomCols", true);
    DrawControls(halfH);
    ImGui::NextColumn();
    DrawMemoryView(halfH);
    ImGui::Columns(1);

    ImGui::End();
}

const char* UIManager::GetFilePath() {
    if (m_file_loaded)
        return m_file_path.c_str();
    
    return NULL;
}

bool UIManager::IsFileLoaded() {
    return m_file_loaded;
}

bool UIManager::CpuCanStep() {
    return !programPaused && stepMode && stepCycle > 0;
}

void UIManager::DrawFileView(float height) {
    ImGui::BeginChild("FileView", ImVec2(0, height), true);
    ImGui::Text("File View");
    if (!m_file_loaded) {
        if (ImGui::Button("Load File")) {
            const char* filters[] = { "*.hex", "*.bin", "*" };
            const char* file = tinyfd_openFileDialog(
                "Select Program File", "", 3, filters, "Program files", 0);
            if (file) {
                m_file_path = file;
                LoadFileLines();
                m_file_loaded = true;
            }
        }
    }
    else {
        float listH = height - ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("FileContentChild", ImVec2(0, listH), false);
        for (int i = 0; i < (int)m_file_lines.size(); ++i) {
            ImGui::Text(i == currentInstruction ? "-> %s" : "   %s", m_file_lines[i].c_str());
        }
        ImGui::EndChild();
    }
    ImGui::EndChild();
}

void UIManager::LoadFileLines() {
    m_file_lines.clear();
    std::ifstream f(m_file_path);
    std::string line;
    while (std::getline(f, line)) m_file_lines.push_back(line);
}

void UIManager::DrawRegisterView(float height) {
    ImGui::BeginChild("RegisterView", ImVec2(0, height), true);
    ImGui::Text("Register View");

    ImGui::Separator();
    if (programPaused)
        ImGui::Text("CPU execution is paused!\nPress Play button to unpause!");

    ImGui::Text("Instruction: %s", currentInstruction < m_file_lines.size() ? m_file_lines[currentInstruction].c_str(): "");
    
    // Display Register Values
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

    ImGui::Text("A:  0x%02X", m_cpuState.A);
    ImGui::Text("B:  0x%02X", m_cpuState.B);
    ImGui::Text("C:  0x%02X", m_cpuState.C);
    ImGui::Text("D:  0x%02X", m_cpuState.D);
    ImGui::Text("E:  0x%02X", m_cpuState.E);
    ImGui::Text("H:  0x%02X", m_cpuState.H);
    ImGui::Text("L:  0x%02X", m_cpuState.L);
    ImGui::Text("PC: 0x%04X", m_cpuState.PC);
    ImGui::Text("SP: 0x%04X", m_cpuState.SP);

    // Display flags
    ImGui::NewLine();
    ImGui::Separator();
    ImGui::NewLine();

    ImGui::Text("Flags: 0x%02X", m_cpuState.Flags);
    
    ImGui::EndChild();
}

void UIManager::DrawControls(float height) {
    ImGui::BeginChild("ButtonCtrl", ImVec2(0, 0), true);
    ImGui::Text("Controls");
    if (programPaused) {
        if (ImGui::Button("Play"))
            programPaused = false;
    }
    else {
        if (ImGui::Button("Pause"))
            programPaused = true;
    }
    //simulator_play();
    if (ImGui::Button("Step")) {
        stepMode = true;
        stepCycle = 1;
    } //simulator_step();
    ImGui::SameLine();
    if (ImGui::Button("Reset")) Reset();
    ImGui::EndChild();
}

void UIManager::DrawMemoryView(float height) {
    ImGui::BeginChild("MemoryView", ImVec2(0, 0), true);
    ImGui::Text("Memory View / RAM View");
    ImGui::Separator();

    const int bytesPerRow = 16;
    if (m_memoryView.empty()) {
        ImGui::Text("No memory loaded.");
        ImGui::EndChild();
        return;
    }

    for (size_t addr = 0; addr < m_memoryView.size(); addr += bytesPerRow) {
        // Show memory address
        ImGui::Text("%04X: ", static_cast<uint16_t>(addr));
        ImGui::SameLine();

        // Print hex values
        for (int i = 0; i < bytesPerRow && addr + i < m_memoryView.size(); ++i) {
            ImGui::SameLine();
            ImGui::Text("%02X", m_memoryView[addr + i]);
        }
    }
    ImGui::EndChild();
}

void UIManager::Reset() {
    m_file_loaded = false;
    m_file_lines.clear();
    currentInstruction = 0;
    cpuResetTriggered = true;
}