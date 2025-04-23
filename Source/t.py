import os

instructions = [
    "ACI", "ADC", "ADD", "ADI", "ANA", "ANI", "CALL", "CC", "CM", "CMA", "CMC",
    "CMP", "CNC", "CNZ", "CP", "CPE", "CPI", "CPO", "CZ", "DAA", "DAD", "DCR",
    "DCX", "DI", "EI", "INR", "INX", "JC", "JM", "JMP", "JNC", "JNZ", "JP", "JPE",
    "JPO", "JZ", "LDA", "LDAX", "LHLD", "LXI", "MOV", "MVI", "NOP", "ORA", "ORI",
    "PCHL", "POP", "PUSH", "RAL", "RAR", "RC", "RET", "RIM", "RLC", "RM", "RNC",
    "RNZ", "RP", "RPE", "RPO", "RRC", "RST", "RZ", "SBB", "SBI", "SHLD", "SIM",
    "SPHL", "STA", "STAX B", "STAX D", "STC", "SUB", "SUI", "XCHG", "XTHL", "XRA",
    "XRI", "IN", "OUT", "HLT"
]

dir_path = "Instructions"

os.makedirs(dir_path, exist_ok=True)

def sanitize(instr):
    return instr.replace(" ", "")

for instr in instructions:
    filename = sanitize(instr)
    hpp_path = os.path.join(dir_path, f"{filename}.cpp")

    with open(hpp_path, "w") as cpp:
        cpp.write(f"#pragma once\n\n")
        cpp.write(f"#include \"../../Headers/Instructionheaders/{filename}.h\"\n\n")

    

print("Done")
