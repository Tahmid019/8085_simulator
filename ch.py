import os

header_folder = "Headers/InstructionHeaders"

for filename in os.listdir(header_folder):
    if filename.endswith(".h"):
        instruction = os.path.splitext(filename)[0]
        filepath = os.path.join(header_folder, filename)
        
        boilerplate = f"""#pragma once
#include "Head_1.h"

vector<uint8_t> decode{instruction}(const std::vector<std::string>& operands);
"""

        with open(filepath, "w") as file:
            file.write(boilerplate)

print("decode declarations.")
