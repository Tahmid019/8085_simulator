#include "../Headers/UIManager.h"

const uint8_t u8_max = 0xff;
const uint8_t u8_min = 0x00;

UIManager::UIManager(SDL_Window* window, SDL_Renderer* renderer, const Registers& reg, vector<uint8_t>& mem)
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
    , m_selected_addr(0x0000)
    , executeAllMode(false)
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

    if (ImGui::Button(m_showCodeEditor ? "Close Code Editor" : "Open Code Editor")) {
        m_showCodeEditor = !m_showCodeEditor; 

        // When opening the editor
        if (m_showCodeEditor) {
            m_assemblerError = false; 
        }
    }

    ImGui::SameLine();
    ImGui::Text("Or load a file using the button below");

    ImGui::Separator();

    // Bottom row: Controls and Memory views
    ImGui::Columns(2, "BottomCols", true);
    DrawControls(halfH);
    ImGui::NextColumn();
    DrawMemoryView(halfH);
    ImGui::Columns(1);

    ImGui::End();

    DrawCodeEditor();
    DrawAssembledCode();
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
        ImGui::Text("CPU execution is paused!\nPress Play button to un-pause!");

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
    ImGui::SameLine();
    ImGui::TextDisabled("(?)  ");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Play | Pause");
    }



    if ((executeAllMode) ? ImGui::Button("Executed") : ImGui::Button("Execute All")) {
        executeAllMode = true;
        stepMode = false;
    }
    ImGui::SameLine();
    ImGui::TextDisabled("(?)  ");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Enables the Execution mode -> Lets you Play and Pause.");
    }



    if (ImGui::Button("Step")) {
        executeAllMode = false;
        stepMode = true;
        stepCycle = 1;
    }
    ImGui::SameLine();
    ImGui::TextDisabled("(?)  ");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Increment Line pointer one at-a-time. {not the Program Counter}");
    }


    ImGui::SameLine();
    if (ImGui::Button("Reset")) 
        Reset();
    ImGui::SameLine();
    ImGui::TextDisabled("(?)  ");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Reset the simulator to initial state. Clears your code and register Values");
    }


    ImGui::SameLine();
    if (ImGui::Button("Reload")) {
        Reload();
    }
    ImGui::SameLine();
    ImGui::TextDisabled("(?)  ");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Keeps Your Code. Re-Initialize the pointers to origin. Re-initializes the Program Counter.");
    }

    ImGui::Text("Memory Address: ");
    ImGui::SameLine();
    if (ImGui::InputInt("##Memory Location: ", &m_selected_addr, 1, 100, ImGuiInputTextFlags_CharsHexadecimal)) {
        if (m_selected_addr < 0x0000 || m_selected_addr > m_memoryView.size()) {
			m_selected_addr = 0x0000;
		}
    }
    ImGui::Text("Memory[0x%04X]: ", m_selected_addr);
    ImGui::SameLine();
    ImGui::DragScalar("##Memory Input", ImGuiDataType_U8, &m_memoryView[m_selected_addr], 1.0f, &u8_min, &u8_max, "%x");
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
    programPaused = true;
}

void UIManager::Reload() {
    currentInstruction = 0;
    cpuReloadTriggered = true;
    programPaused = true;
    stepMode = false;
	stepCycle = 0;
}

void UIManager::DrawCodeEditor() {
    if (!m_showCodeEditor) return;

    ImGui::Begin("8085 Code Editor", &m_showCodeEditor, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Enter 8085 assembly code below (one instruction per line):");
    ImGui::Text("Example: MVI A, 1FH");

    ImGui::InputTextMultiline("##sourcecode", m_codeInputBuffer, sizeof(m_codeInputBuffer),
        ImVec2(400, 200));

    if (ImGui::Button("Assemble")) {
        AssembleCode();
        if (!m_assemblerError) {
            m_showAssembledCode = true;
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Close")) {
        m_showCodeEditor = false;
    }

    if (m_assemblerError) {
        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Assembler Error: %s",
            m_assemblerErrorMsg.c_str());
    }

    ImGui::End();
}

void UIManager::DrawAssembledCode() {
    if (!m_showAssembledCode) return;

    ImGui::Begin("Assembled Code", &m_showAssembledCode, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Successfully assembled %d instructions:", m_assembledLines.size());
    ImGui::Separator();

    for (const auto& line : m_assembledLines) {
        ImGui::Text("%s", line.c_str());
    }

    ImGui::Separator();
    if (ImGui::Button("Load into Memory")) {
        m_showAssembledCode = false;
        m_file_loaded = true;
        m_file_lines = m_assembledLines;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
        m_showAssembledCode = false;
    }

    ImGui::End();
}

void UIManager::AssembleCode() {
    m_assembledLines.clear();
    m_assemblerError = false;

    std::istringstream iss(m_codeInputBuffer);
    std::string line;

    while (std::getline(iss, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) continue;

        std::transform(line.begin(), line.end(), line.begin(), ::toupper);

        if (line.find(";") == 0) continue; 

		if (line.find("DB ") == 0 || line.find("DW ") == 0 || line.find("ORG ") == 0) {
            // start adder
            m_assembledLines.push_back(line);
			continue;
		}
        m_assembledLines.push_back(line);
    }

    if (m_assembledLines.empty()) {
        m_assemblerError = true;
        m_assemblerErrorMsg = "No valid instructions found";
    }
}

bool UIManager::isCodeAssembled() {
    return (!m_assembledLines.empty() && m_assemblerError == false);
}

vector<string> UIManager::getAssembledCode() {
    return m_assembledLines;
}