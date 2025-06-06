#include "../Headers/Head_1.h"
#include "../Headers/utils.h"
#include "../Headers/CPU.h"
#include "../Headers/IOHandler.h"

#include <SDL3/SDL.h>
#include "../Headers/UIManager.h"

#define VIDEO_WIDTH 1280
#define VIDEO_HEIGHT 720

class sim_8085 {
private:
    CPU cpu;
    IOHandler io_handler;
    uint16_t start_addr;
    string m_mem_file;

public:
    sim_8085() {
        start_addr = 0x0000;

        // Initialize CPU registers
        cpu.reg.A = 0x00;
        cpu.reg.B = 0x00;
        cpu.reg.C = 0x00;
        cpu.reg.D = 0x00;
        cpu.reg.E = 0x00;
        cpu.reg.H = 0x00;
        cpu.reg.L = 0x00;
        cpu.reg.BC.set(0x0000);
        cpu.reg.DE.set(0x0000);
        cpu.reg.HL.set(0x0000);
        cpu.reg.PC = 0x0000;
        cpu.reg.SP = 0xffff;
        cpu.reg.Flags = 0x00;
    }
	void input_data(const string& mem_file) {
		message("Insert data in Memory ...", 0, 0, MessageType::INFO);
	}
    void load_program_file(string filename,uint16_t init_addr, bool debug = false) {
        message("Loading Program in Main Memory ...", 0, 0, MessageType::INFO);
        ifstream file(filename);

        if (!file) {
            std::cerr << "Error: Cant Open the File ... " << filename << std::endl;
            throw runtime_error("Cant open the File ...");
        }

        vector<string> assembly_code;
        string strInst;
        while (getline(file, strInst)) {
            assembly_code.push_back(strInst);
        }
        file.close();
		
        if (assembly_code.empty()) {
			cerr << "Error: No Code Found in the File ... " << filename << endl;
			throw runtime_error("No code found in the file.");
		}

        cerr << "\nAssembly code size: " << assembly_code.size() << endl;

        io_handler.loadProgram(cpu, assembly_code, init_addr);
    }

    void load_program(vector<string> assem_code, uint16_t init_addr, bool debug = false) {
        message("Loading Program in Main Memory ...", 0, 0, MessageType::INFO);
        io_handler.loadProgram(cpu, assem_code, init_addr);
    }

    void setup_cpu(uint16_t init_addr, const string& mem_file) {
        message("Executing Program from Main Memory ...", 0, 0, MessageType::INFO);
        cpu.reg.PC = init_addr;
        m_mem_file = mem_file;
    }

    void reset_cpu() {
        cpu.reg.A = 0x00;
        cpu.reg.B = 0x00;
        cpu.reg.C = 0x00;
        cpu.reg.D = 0x00;
        cpu.reg.E = 0x00;
        cpu.reg.H = 0x00;
        cpu.reg.L = 0x00;
        cpu.reg.BC.set(0x0000);
        cpu.reg.DE.set(0x0000);
        cpu.reg.HL.set(0x0000);
        cpu.reg.PC = 0x0000;
        cpu.reg.SP = 0xffff;
        cpu.reg.Flags = 0x00;
        cpu.isHalt = false;

        
        
    }

    void execute_program() {
        while (true) {
            int check = cpu.execute(cpu.memory.read(cpu.reg.PC));
            if (check == -1) break;
        }
        //cpu.memory.save2csv(mem_file);
        //save_cpu2csv();
    }

    void step_program() {
        int check = cpu.execute(cpu.memory.read(cpu.reg.PC));
    }

    bool isCPUHalted() {
        return cpu.isHalt;
    }

    void save_cpu2csv() {
        cpu.memory.save2csv(m_mem_file);
    }

    const Registers& get_cpu_state() {
        return cpu.reg;
    }

    vector<uint8_t>& get_memory() {
        return cpu.memory.mem;
    }

    ~sim_8085() {
        cerr << "sim_8085 instance deconstructed" << endl;
    }
};

int main() {
    // Initialize SDL3 video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "8085 Simulator", // Title
        VIDEO_WIDTH, VIDEO_HEIGHT,
        SDL_WINDOW_HIGH_PIXEL_DENSITY
    );

    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create SDL3 renderer with default flags
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Create simulator instance
    sim_8085 instance;

    // Create a UI Manager object
    UIManager uiManager(window, renderer, instance.get_cpu_state(), instance.get_memory());
    uiManager.Init();
    
    // Initial Instance settings
    string mem_file = "memory.csv";
    instance.input_data(mem_file);
    uint16_t start_addr = 0x0000;

    bool running = true;
    bool errPop = false;
	string errMsg = "No Error";
    bool programLoaded = false;
    bool resetMemoryOnError = false;

    SDL_Event event;
    while (running) {
        try {
            //bool test = true;
			//uiManager.ShowError(test, errMsg);

            //if (errPop) {
            //    cerr << "Error Popup" << endl;
            //    uiManager.ShowError(errPop, errMsg);
            //    errPop = false;
            //}


            // Process SDL Events
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    running = false;
                }
                uiManager.ProcessEvent(event);
            }

            // Handle File load event
            if (uiManager.IsFileLoaded() && !programLoaded) {
                try {
                    cerr << " Loading file ... " << endl;
                    
                    //instance.load_program_file(uiManager.GetFilePath(), start_addr);
                    instance.load_program(uiManager.getLoadedCode(), start_addr);
                    programLoaded = true;
                    instance.setup_cpu(start_addr, mem_file);
                    resetMemoryOnError = false;  

                    cerr << " File Loaded " << endl;
                }
                catch (const exception& e) {
					cerr << "File load error: " << e.what() << endl;
                    uiManager.SetError(e.what());
                    instance.reset_cpu();
                    errPop = true;
                    errMsg = e.what();
                    programLoaded = false;
                }
            }

            //Handle Code Upload event
            if (uiManager.isCodeAssembled() && !programLoaded) {
                try {
                    instance.load_program(uiManager.getAssembledCode(), start_addr);
                    programLoaded = true;
                    instance.setup_cpu(start_addr, mem_file);
                    resetMemoryOnError = false; 
                }
                catch (const exception& e) {
					cerr << "Code upload error: " << e.what() << endl;
					uiManager.SetError(e.what());
                    instance.reset_cpu();
                    errPop = true;
                    errMsg = e.what();
                    programLoaded = false;
                }
            }

            //Reload
            if (uiManager.cpuReloadTriggered) {
				cerr << "Reloading CPU..." << endl;
                programLoaded = false;
                uiManager.cpuReloadTriggered = false;
                uiManager.executeAllMode = false;
                errPop = false;
            }

            // Handle Reset Event
            if (uiManager.cpuResetTriggered) {
				cerr << "Resetting CPU..." << endl;
                programLoaded = false;
                uiManager.cpuResetTriggered = false;
                instance.reset_cpu();
                uiManager.executeAllMode = false;
                errPop = false;
				resetMemoryOnError = false; 
            }

            // Step cpu instruction
            if (programLoaded) {
                try {
                    if (uiManager.CpuCanStep()) {
                        instance.step_program();
                        uiManager.stepCycle -= 1;
                        uiManager.currentInstruction = static_cast<int>(instance.get_cpu_state().PC);
                    }
                    else if (uiManager.executeAllMode && uiManager.stepCycle > 0) {
                        instance.step_program();
                        uiManager.stepCycle -= 1;
                        uiManager.currentInstruction = static_cast<int>(instance.get_cpu_state().PC);
                    }
                    else if (!uiManager.programPaused) {
                        if (!instance.isCPUHalted()) {
                            instance.step_program();
                            uiManager.currentInstruction = static_cast<int>(instance.get_cpu_state().PC);
                        }
                        else {
                            uiManager.executeAllMode = false;
                        }
                    }
                }
                catch (const exception& e) {
                    cerr << "Execution error: " << e.what() << endl;
                    uiManager.SetError(e.what());
                    instance.reset_cpu();
                    errPop = true;
                    errMsg = e.what();
                    programLoaded = false;
                    resetMemoryOnError = true;
                }
            }

            // Begin new frame and draw GUI
            uiManager.BeginFrame();
            uiManager.Draw();
            uiManager.RenderFrame();
        }
        catch (const exception& e) {
            cerr << "UI Exception: " << e.what() << endl;
            errPop = true;
            errMsg = string("UI Error: ") + e.what();
            resetMemoryOnError = true;
        }

        // Handle memory reset after error if needed
        if (resetMemoryOnError) {
            try {
                instance.reset_cpu();
                instance.input_data(mem_file);  
                programLoaded = false;
                uiManager.executeAllMode = false;
                uiManager.programPaused = true;
                uiManager.stepCycle = 0;
                resetMemoryOnError = false;
            }
            catch (const exception& e) {
                uiManager.SetError(e.what());
                cerr << "Critical reset error: " << e.what() << endl;
                running = false; 
            }
        }
    }

    uiManager.Shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
