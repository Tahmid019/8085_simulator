#pragma once

#include "../Head_1.h"
#include "token.h"

struct ASTNode {
	virtual ~ASTNode() = default;
};

struct Identifier : ASTNode {
	string name;
};

struct InstructionAST : ASTNode{
	string name;
	vector<unique_ptr<ASTNode>> operands;
};

struct Register : ASTNode {
	string name;
};

struct NumberLiteral : ASTNode {
	int64_t value;
};

struct StringLiteral : ASTNode{
	string value;
};

struct MemoryAddress : ASTNode {
	unique_ptr<ASTNode> displacement;
	unique_ptr<ASTNode> base;
	unique_ptr<ASTNode> index;

	int scale = 1;
};


class Parser {
public:
	explicit Parser(const TokenList& tokens);
		/* : m_tokens(tokens), m_current(0) {}*/

	vector<unique_ptr<ASTNode>> parse();
private:
	unique_ptr<ASTNode> parseInstruction();
	unique_ptr<ASTNode> parseOperand();
	//unique_ptr<ASTNode> parseNumberLiter();
	//unique_ptr<ASTNode> parseStringLiteral();
	unique_ptr<ASTNode> parseMemoryAddress();

	//void consume(TokenType type);
	const Token& advance();
	const Token& peek() const;
	bool match(TokenType type);
	bool check(TokenType type) const;
	bool isAtEnd() const;

	const TokenList& m_tokens;
	size_t m_current = 0;
};