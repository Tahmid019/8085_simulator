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
	cerr << " Parsing > " << endl;

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

	cerr << " Parsed < ";
	return statements;
}

std::unique_ptr<ASTNode> Parser::parseInstruction() {
	auto instruction = std::make_unique<InstructionAST>();

	// Handle label 
	if (check(TokenType::IDENTIFIER)) {
		const Token& token = peek();
		if (m_current + 1 < m_tokens.size() &&
			m_tokens[m_current + 1].type == TokenType::COLON) {
			advance(); // identifier
			advance(); // colon
		}
	}

	if (!check(TokenType::IDENTIFIER)) {
		throw std::runtime_error("Expected instruction name");
	}
	instruction->name = advance().value;

	while (!isAtEnd() && !check(TokenType::END_OF_LINE)) {
		if (check(TokenType::COMMA)) {
			advance(); // skip comma
			continue;
		}
		instruction->operands.push_back(parseOperand());
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
			num->value = string(numStr);
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
				auto operand = parseOperand();
				auto scale = dynamic_cast<NumberLiteral*>(operand.get());
				if (scale) {
					mem->scale = static_cast<int>(ston<uint8_t>(scale->value));
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






