import os

jmp_instructions = {
    "JC": 0xDA,
    "JM": 0xFA,
    "JMP": 0xC3,
    "JNC": 0xD2,
    "JNZ": 0xC2,
    "JP": 0xF2,
    "JPE": 0xEA,
    "JPO": 0xE2,
    "JZ": 0xCA
}

header = '#pragma once\n#include "../Headers/Head_2.h"\n#include "../Headers/utils.h"\n\n'

function_template = """vector<uint8_t> decode{inst}(const vector<string>& operands) {{
    if (operands.size() != 1) {{
        throw invalid_argument("{inst} instruction requires exactly one operand.");
    }}
    uint16_t addr = 0x0000 | ston<uint16_t>(operands[0]);
    return {{ 0x{opcode:02X}, static_cast<uint8_t>(addr & 0xFF), static_cast<uint8_t>((addr >> 8) & 0xFF) }};
}}
"""

directory = "Instructions"
os.makedirs(directory, exist_ok=True)

for inst, opcode in jmp_instructions.items():
    file_path = os.path.join(directory, f"{inst}.cpp")
    with open(file_path, "w") as f:
        f.write(header)
        f.write(function_template.format(inst=inst, opcode=opcode))
    print(f"Updated: {file_path}")
