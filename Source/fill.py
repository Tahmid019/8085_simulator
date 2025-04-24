import os

decoder_functions = {
    "XCHG": "return { 0xEB };",

    "XTHL": "return { 0xE3 };",

    "XRA": """const string& reg = operands[0];
    if (reg == "B") return { 0xA8 };
    if (reg == "C") return { 0xA9 };
    if (reg == "D") return { 0xAA };
    if (reg == "E") return { 0xAB };
    if (reg == "H") return { 0xAC };
    if (reg == "L") return { 0xAD };
    if (reg == "M") return { 0xAE };
    if (reg == "A") return { 0xAF };
    throw invalid_argument("Invalid operand for XRA instruction: " + reg);""",

    "XRI": """int data = stoi(operands[0], nullptr, 0);
    return { 0xEE, static_cast<uint8_t>(data & 0xFF) };"""
}

header = '#pragma once\n#include "../Headers/Head_2.h"\n\n'

function_template_single = """vector<uint8_t> decode{inst}(const vector<string>& operands) {{
    if (!operands.empty()) {{
        throw invalid_argument("{inst} instruction takes no operands.");
    }}
    {body}
}}
"""

function_template_operand = """vector<uint8_t> decode{inst}(const vector<string>& operands) {{
    if (operands.size() != 1) {{
        throw invalid_argument("{inst} instruction requires exactly one operand.");
    }}
    {body}
}}
"""

directory = "Instructions"
os.makedirs(directory, exist_ok=True)

for inst, body in decoder_functions.items():
    file_path = os.path.join(directory, f"{inst}.cpp")
    with open(file_path, "w") as f:
        f.write(header)
        if "operands[0]" in body:
            f.write(function_template_operand.format(inst=inst, body=body))
        else:
            f.write(function_template_single.format(inst=inst, body=body))
    print(f"Updated: {file_path}")
