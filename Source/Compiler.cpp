#include "../Headers/Head_1.h"
#include "../Headers/Compiler.h"
#include "../Headers/Instructions.h"
#include "../Headers/Memory.h"
#include "../headers/Parsing/Parser.h"
#include "../headers/Parsing/Lexer.h"
#include "../Headers/utils.h"

unordered_map<string, uint16_t> Compiler::symbolTable;

static size_t getInstructionSize(const TokenList& tokens)
{
    if (tokens.empty()) {
        return 0;
    }
    string mne = toUpper(tokens[0].value);
    Instruction inst = instructionSet[mne];
   
    return inst.wordSize;
}

void Compiler::buildSymbolTable(vector<string>& assembled_code, uint16_t& init_addr)
{
    uint16_t addr = init_addr;  

    for (auto& rawLine : assembled_code) {
        size_t comment_pos = rawLine.find(';');
        if (comment_pos != string::npos) {
            rawLine = rawLine.substr(0, comment_pos);
        }
        trim(rawLine);
        if (rawLine.empty()) {
            continue; 
        }

       
        string line = rawLine;
        size_t colon_pos = line.find(':');
        if (colon_pos != string::npos) {
            string label = line.substr(0, colon_pos);
            label.erase(label.find_last_not_of(" \t") + 1);
            string labelUp = toUpper(label);

            Compiler::symbolTable[labelUp] = addr;

            line = line.substr(colon_pos + 1);
            trim(line);
            if (line.empty()) {
                continue;
            }
        }

       
        Lexer   lexer(line);
        TokenList tokens = lexer.tokenize();
        if (tokens.empty()) {
            continue;
        }

        size_t byteCount = getInstructionSize(tokens);

        addr = static_cast<uint16_t>(addr + byteCount);
    }

}

vector<uint8_t> Compiler::compile(CPU& cpu, const string& line, uint16_t& addr) {
    if (line.empty() || line[0] == ';') return {};

    Lexer lexer(line);
    TokenList tokens = lexer.tokenize();

    Parser parser(tokens);
    auto astNodes = parser.parse();

    for (const auto& node : astNodes) {
        if (auto instrNode = dynamic_cast<InstructionAST*>(node.get())) {
            string mne = instrNode->name;
            transform(mne.begin(), mne.end(), mne.begin(), ::toupper);

            vector<string> operandStrings;
            for (const auto& operand : instrNode->operands) {
                if (auto reg = dynamic_cast<Register*>(operand.get())) {
                    operandStrings.push_back(reg->name);
                }
                else if (auto num = dynamic_cast<NumberLiteral*>(operand.get())) {
                    operandStrings.push_back((num->value));
                }
                else if (auto ident = dynamic_cast<Identifier*>(operand.get())) {
                    if (symbolTable.count(ident->name)) {
                        operandStrings.push_back(to_string(symbolTable[ident->name]));
                    }
                    else {
                        throw runtime_error("Undefined symbol: " + ident->name);
                    }
                }
                else if (auto mem = dynamic_cast<MemoryAddress*>(operand.get())) {
                    string memStr = "[";
                    if (mem->displacement) {
                        if (auto disp = dynamic_cast<NumberLiteral*>(mem->displacement.get())) {
                            memStr += (disp->value);
                        }
                    }
                    if (mem->base) {
                        if (auto base = dynamic_cast<Register*>(mem->base.get())) {
                            memStr += base->name;
                        }
                    }
                    if (mem->index) {
                        memStr += "+";
                        if (auto index = dynamic_cast<Register*>(mem->index.get())) {
                            memStr += index->name;
                        }
                        if (mem->scale != 1) {
                            memStr += "*" + to_string(mem->scale);
                        }
                    }
                    memStr += "]";
                    operandStrings.push_back(memStr);
                }
            }

            if (instructionSet.find(mne) == instructionSet.end()) {
                throw runtime_error("Unknown instruction: " + mne);
            }

            Instruction inst = instructionSet[mne];
            vector<uint8_t> bytes = inst.decoder(operandStrings);

            if (inst.wordSize != bytes.size()) {
                throw runtime_error("Size mismatch for " + mne +
                    ": expected " + to_string(inst.wordSize) +
                    ", got " + to_string(bytes.size()));
            }

            for (uint8_t byte : bytes) {
                cpu.memory.write(addr, byte);
                t2t_message("Loaded at: ", addr, byte, Type2Tpe::t16_2_8);
                addr++;
            }

            return bytes;
        }
    }
    return {};
}