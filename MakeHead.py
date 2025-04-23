import os

header_folder = "Headers/InstructionHeaders"
output_file = "Inst_Head.h"

headers = sorted(f for f in os.listdir(header_folder) if f.endswith(".h"))

with open(output_file, "w") as out:
    out.write("// instruction headers\n\n")
    for header in headers:
        out.write(f"#include \"{header}\"\n")

print(f"{output_file} with {len(headers)} includes.")
