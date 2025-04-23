#pragma once
#include "Head_1.h"

class CLI {
public:
    static void run();
private:
    static void optionA();   
    static void optionB();   
    static bool isEscape(char c);
    static std::string readLineWithPrompt(const std::string& prompt);
};
