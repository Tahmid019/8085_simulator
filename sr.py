import os

cpp_folder = "Source/Instructions"

for filename in os.listdir(cpp_folder):
    if filename.endswith(".cpp"):
        inst_name = os.path.splitext(filename)[0]
        filepath = os.path.join(cpp_folder, filename)
        
        content = f"""#pragma once
#include "Headers/Head_1.h"

vector<uint8_t> decode{inst_name}(const vector<string>& operands) {{
    return {{}}; 
}}
"""
        with open(filepath, "w") as file:
            file.write(content)

print("function definitions.")
