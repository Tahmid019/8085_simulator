#include "../../../Headers/Head_1.h"
#include "../../Headers/Parsing/Parser.h"
#include "../../Headers/utils.h"

Parser::Parser(const TokenList& tokens) : m_tokens(tokens) {}

string hexToDecimalString(uint16_t hexValue) {
	ostringstream oss;

	uint8_t highByte = (hexValue >> 8) & 0xFF; 
	uint8_t lowByte = hexValue & 0xFF;         

	oss << static_cast<int>(highByte); 
	oss << static_cast<int>(lowByte);  

	return oss.str(); 
}

uint16_t decimalStringToHex(const std::string& decimalStr) {
	if (decimalStr.size() != 4) { // Must be 4 digits (2 bytes)
		return 0xFFFF; // Error case (adjust as needed)
	}

	// Split into two 2-digit decimal numbers
	uint8_t highByte = std::stoi(decimalStr.substr(0, 2)); // "37" → 37
	uint8_t lowByte = std::stoi(decimalStr.substr(2, 2)); // "16" → 16

	// Combine into a 16-bit hex value
	return (static_cast<uint16_t>(highByte) << 8) | lowByte; // 0x2510
}

vector<unique_ptr<ASTNode>> Parser::parse() {
	vector<unique_ptr<ASTNode>> statements;

	while (!isAtEnd()) {
		if (check(TokenType::END_OF_LINE)) {
			advance();
			continue;
		}

		if (check(TokenType::IDENTIFIER)) {
			statements.push_back(parseInstruction());
		}
		else {
			advance();
		}
	}

	return statements;
}

unique_ptr<ASTNode> Parser::parseInstruction() {
	auto instruction = make_unique<InstructionAST>();
	instruction->name = advance().value;

	while (!isAtEnd() && !check(TokenType::END_OF_LINE)) {
		if (check(TokenType::COMMA)) {
			advance();
			continue;
		}

		instruction->operands.push_back(parseOperand());
	}

	if (check(TokenType::END_OF_LINE)) {
		advance();
	}

	return instruction;
}

unique_ptr<ASTNode> Parser::parseOperand() {
	if (check(TokenType::LBRACKET)) {
		return parseMemoryAddress();
	}

	const Token& token = peek();
	switch (token.type) {
		case TokenType::REGISTER: {
			auto reg = make_unique<Register>();
			reg->name = advance().value;
			return reg;
		}
		
		case TokenType::NUMBER: {
			auto num = make_unique<NumberLiteral>();
			string_view numStr = advance().value;
			if (numStr.back() == 'H' || numStr.back() == 'h') {
				if (numStr.size() == 5) {
					auto body = numStr.substr(0, numStr.size() - 1);

					uint8_t hi = 0, lo = 0;

					// parse hi
					{
						auto first = body.data();
						auto last = first + 2;
						auto res = std::from_chars(first, last, hi, 16);
						if (res.ec != std::errc()) {
							std::cerr << "Failed to parse hi\n";
							exit(1);
						}
					}

					// parse lo
					{
						auto first = body.data() + 2;
						auto last = first + 2;
						auto res = std::from_chars(first, last, lo, 16);
						if (res.ec != std::errc()) {
							std::cerr << "Failed to parse lo\n";
							exit(1);
						}
					}

					num->value = (uint16_t(hi) << 8) | lo;
				}else if (numStr.size() == 4) {
					num->value = (ston<uint8_t>('0' + string(numStr.substr(0, 1)) + 'H') << 8) & 0xFF00 + (ston<uint8_t>(string(numStr.substr(1, 4)))) & 0x00FF;
				}
				else if (numStr.size() == 3) {
					num->value = (ston<uint8_t>(string(numStr.substr(0,3)))) & 0x00FF;
				}
				else if (numStr.size() == 2) {
					num->value = (ston<uint8_t>('0' + string(numStr.substr(0, 2)))) & 0x00FF;
				}
				else {
					num->value = 0;
				}
			}
			else {
				from_chars(numStr.data(), numStr.data() + numStr.size(), num->value);
			}
			return num;
		}

		case TokenType::STRING: {
			auto str = make_unique<StringLiteral>();
			str->value = advance().value;
			return str;
		}

		case TokenType::IDENTIFIER: {
			auto ident = make_unique<Identifier>();
			ident->name = advance().value;
			return ident;
		}

		default:
			throw runtime_error("Unexpected token type: " + to_string(static_cast<int>(token.type)) +
				" at line " + to_string(token.line) + ", column " + to_string(token.column));
	}
}

unique_ptr<ASTNode> Parser::parseMemoryAddress() {
	auto mem = make_unique<MemoryAddress>();
	advance(); // skip [

	if (check(TokenType::NUMBER)) {
		mem->displacement = parseOperand();
	}

	if (check(TokenType::REGISTER)) {
		mem->base = parseOperand();
	}

	if (check(TokenType::PLUS)) {
		advance();
		mem->index = parseOperand();

		if (check(TokenType::PLUS)) {
			advance();
			if (check(TokenType::NUMBER)) {
				auto scale = dynamic_cast<NumberLiteral*>(parseOperand().get());
				if (scale) {
					mem->scale = static_cast<int>(scale->value);
				}
			}
		}
	}

	if (!check(TokenType::RBRACKET)) {
		throw runtime_error("Expected ']' at line " + to_string(peek().line) + ", column " + to_string(peek().column));

	}

	advance(); // skip ]

	return mem;
}

const Token& Parser::peek() const {
	return m_tokens[m_current];
}

const Token& Parser::advance() {
	if (!isAtEnd()) {
		m_current++;
	}

	return m_tokens[m_current - 1];
}

bool Parser::match(TokenType type) {
	if (check(type)) {
		advance();
		return true;
	}

	return false;
}

bool Parser::check(TokenType type) const {
	if (isAtEnd()) return false;
	return peek().type == type;
}

bool Parser::isAtEnd() const {
	return m_current >= m_tokens.size() ||
		m_tokens[m_current].type == TokenType::END_OF_FILE;
}






