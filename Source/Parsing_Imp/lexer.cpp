#include "../../../Headers/Head_1.h"
#include "../../Headers/Parsing/Lexer.h"
#include "../../Headers/utils.h"

namespace {
	const unordered_map<string_view, TokenType> keywords = {
		{"EAX", TokenType::REGISTER}, {"EBX", TokenType::REGISTER},
		{"ECX", TokenType::REGISTER}, {"EDX", TokenType::REGISTER},
		{"ESI", TokenType::REGISTER}, {"EDI", TokenType::REGISTER},
		{"ESP", TokenType::REGISTER}, {"EBP", TokenType::REGISTER},
		{"RAX", TokenType::REGISTER}, {"RBX", TokenType::REGISTER},
		{"RCX", TokenType::REGISTER}, {"RDX", TokenType::REGISTER},
		{"RSI", TokenType::REGISTER}, {"RDI", TokenType::REGISTER},
		{"RSP", TokenType::REGISTER}, {"RBP", TokenType::REGISTER},
		{"R8", TokenType::REGISTER}, {"R9", TokenType::REGISTER},
		{"R10", TokenType::REGISTER}, {"R11", TokenType::REGISTER},
		{"R12", TokenType::REGISTER}, {"R13", TokenType::REGISTER},
		{"R14", TokenType::REGISTER}, {"R15", TokenType::REGISTER},
		{"A", TokenType::REGISTER}, {"B", TokenType::REGISTER},
		{"C", TokenType::REGISTER}, {"D", TokenType::REGISTER},
		{"E", TokenType::REGISTER}, {"H", TokenType::REGISTER},
		{"L", TokenType::REGISTER}, {"M", TokenType::REGISTER},
		{"F", TokenType::REGISTER}, {"PC", TokenType::REGISTER},
		{"SP", TokenType::REGISTER}, {"PSW", TokenType::REGISTER},
	};
}

Lexer::Lexer(string_view source) : m_source(source) {}

TokenList Lexer::tokenize() {
	cerr << " Tokenizing > ";

	TokenList tokens;
	while (!isAtEnd()) {
		tokens.push_back(nextToken());
	}
	tokens.push_back({ TokenType::END_OF_FILE,"",m_line, m_column });

	cerr << " Tokenized < ";
	return tokens;
}

Token Lexer::nextToken() {
	skipWhiteSpace();
	if (isAtEnd()) return { TokenType::END_OF_FILE, "", m_line, m_column };

	char c = peek();
	if (isxdigit(c) || c == '-') {
		size_t lookahed = m_current;
		bool hasDigits = false;

		if (c == '-') lookahed++;

		while (lookahed < m_source.size() && isxdigit(m_source[lookahed])) {
			lookahed++;
			hasDigits = true;
		}

		if (hasDigits && lookahed < m_source.size() && (m_source[lookahed] == 'h' || m_source[lookahed] == 'H')) {
			//cout << c << endl;
			return number();
		}
	}

	if (isalpha(c) || c == '-' || c == '.') return identifierOrKeyword();
	if (isdigit(c) || c == '-') return number();
	if (c == '"') return stringLiteral();

	size_t line = m_line;
	size_t column = m_column;

	switch (c) {
	case ',':
		advance();
		return { TokenType::COMMA, ",", line, column };
	case ':':
		advance();
		return { TokenType::COLON, ":", line, column };
	case '[':
		advance();
		return { TokenType::LBRACKET, "[", line, column };
	case ']':
		advance();
		return { TokenType::RBRACKET, "]", line, column };
	case '+':
		advance();
		return { TokenType::PLUS, "+", line, column };
	case '-':
		advance();
		return { TokenType::MINUS, "-", line, column };
	case ';':
		//while (!isAtEnd() && peek() != '\n') advance();
		advance();
		m_line++;
		m_column = 1;
		return { TokenType::COMMENT, "", line, column };
	case '\n':
		advance();
		m_line++;
		m_column = 1;
		return { TokenType::END_OF_LINE, "", line, column };
	default:
		advance(); // skip uynknown chars
		return { TokenType::END_OF_FILE, "", line, column};
	}
}




// Helpers

char Lexer::peek() const {
	return isAtEnd() ? '\0' : m_source[m_current];
}

char Lexer::advance() {
	if (isAtEnd()) return '\0';
	m_column++;
	return m_source[m_current++];
}

bool Lexer::match(char expected) {
	if (isAtEnd() || m_source[m_current] != expected) return false;

	advance();
	return true;
}

void Lexer::skipWhiteSpace() {
	while (!isAtEnd()) {
		char c = peek();
		if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f') {
			advance();
			if (c == '\n') {
				m_line++;
				m_column = 1;
			}
			else {
				m_column++;
			}
		}
		else {
			break;
		}
	}
}

void Lexer::skipComment() {
	while (!isAtEnd() && peek() != '\n') {
		advance();
	}
	/*if (peek() == '\n') {
		advance();
		m_line++;
		m_column = 1;
	}*/
}

Token Lexer::identifierOrKeyword() {
	size_t start = m_current;
	size_t line = m_line;
	size_t column = m_column;

	while (!isAtEnd()) {
		char c = peek();
		if (isalnum(c) || c == '_' || c == '-' || c == '.') {
			advance();
		}
		else {
			break;
		}
	}

	string_view text = m_source.substr(start, m_current - start);
	auto it = keywords.find(text);
	TokenType type = (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;

	return { type , string(text), line, column };
}

Token Lexer::number() {
	size_t start = m_current;
	size_t line = m_line;
	size_t column = m_column;
	bool isHex = false;

	if (peek() == '-') {
		advance();
	}

	if (!isAtEnd() && peek() == '0' && m_current + 1 < m_source.size() &&
		(m_source[m_current + 1] == 'x' || m_source[m_current + 1] == 'X')) {
		advance(); // 0
		advance(); // x
		isHex = true;
	}
	else {
		size_t lookahead = m_current;
		while (lookahead < m_source.size() && isxdigit(m_source[lookahead])) {
			lookahead++;
		}
		if (lookahead < m_source.size() &&
			(m_source[lookahead] == 'h' || m_source[lookahead] == 'H')) {
			isHex = true;
		}
	}

	while (!isAtEnd()) {
		char c = peek();
		if (isxdigit(c) || (!isHex && isdigit(c))) {
			advance();
		}
		else if (c == '.' && !isHex) {
			advance(); // allow decimal point for non-hex
		}
		else {
			break;
		}
	}

	if (!isAtEnd()) {
		char c = peek();
		if (c == 'h' || c == 'H' || c == 'b' || c == 'B' ||
			c == 'o' || c == 'O' || c == 'q' || c == 'Q') {
			advance();
		}
	}

	string_view text = m_source.substr(start, m_current - start);
	return { TokenType::NUMBER, string(text), line, column };
}

Token Lexer::stringLiteral() {
	size_t line = m_line;
	size_t column = m_column;
	advance();

	string value;
	while (!isAtEnd() && peek() != '"') {
		if (peek() == '\\') {
			advance(); 
			
			switch (peek()) {
				case 'n': value += '\n'; break;
				case 't': value += '\t'; break;
				case '\\': value += '\\'; break;
				case '"': value += '"'; break;
				default: value += '\\'; value += peek(); break;
			}
			advance();
		}
		else {
			value += advance();
		}
	}

	if (peek() == '"') {
		advance(); // closing quote
	}

	return { TokenType::STRING, value, line, column };
}

bool Lexer::isAtEnd() const {
	return m_current >= m_source.size();
}


