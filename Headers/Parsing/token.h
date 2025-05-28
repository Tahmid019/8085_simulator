#pragma once

#include "../Head_1.h";

enum class TokenType {
	IDENTIFIER,    // inst names, labels
	REGISTER,     // R0, R1, etc.
	NUMBER,       // numeric literals
	STRING,       // string literals
	COMMA,       // ,
	COLON,       // :
	LBRACKET,     // [
	RBRACKET,     // ]
	PLUS,         // +
	MINUS,        // -
	COMMENT,     // ;
	END_OF_LINE, // end of line
	END_OF_FILE, // end of file
	UNKNOWN       
};

struct Token {
	TokenType type;
	string value;
	size_t line;
	size_t column;

	Token(TokenType type, const string& value, size_t line, size_t column)
		: type(type), value(value), line(line), column(column) {}
};

using TokenList = vector<Token>;

