#pragma once

#include "../Head_1.h";
#include "token.h"

class Lexer {
public:
	explicit Lexer(string_view source);

	TokenList tokenize();
	Token nextToken();
private:
	char peek() const;
	char advance();
	bool match(char expected);
	void skipWhiteSpace();
	void skipComment();

	Token identifierOrKeyword();
	Token number();
	Token stringLiteral();
	
	bool isAtEnd() const;

	string_view m_source;
	size_t m_current = 0;
	size_t m_line = 1;
	size_t m_column = 1;
};