#include "../../../Headers/Head_1.h"
#include "../../Headers/Parsing/Parser.h"

Parser::Parser(const TokenList& tokens) : m_tokens(tokens) {}

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
	auto instruction = make_unique<Instruction>();
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
			from_chars(numStr.data(), numStr.data() + numStr.size(), num->value);
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






