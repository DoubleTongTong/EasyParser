#pragma once

#include "TASTNode.h"
#include "TTokenizer.h"

class TParser
{
	std::string m_str;
	TTokenizer  m_tokenizer;
	TToken      m_lookahead;

public:
	TParser();

	std::unique_ptr<TASTNode> Parse(const std::string& input);

private:
	std::unique_ptr<TASTNode> Program();
	std::unique_ptr<TASTNode> StatementList(TToken::Type endTokenType = TToken::END);
	std::unique_ptr<TASTNode> Statement();
	std::unique_ptr<TASTNode> EmptyStatement();
	std::unique_ptr<TASTNode> BlockStatement();
	std::unique_ptr<TASTNode> ExpressionStatement();
	std::unique_ptr<TASTNode> Expression();
	std::unique_ptr<TASTNode> AdditiveExpression();
	std::unique_ptr<TASTNode> MultiplicativeExpression();
	std::unique_ptr<TASTNode> PrimaryExpression();
	std::unique_ptr<TASTNode> ParenthesizedExpression();
	std::unique_ptr<TASTNode> Literal();
	std::unique_ptr<TASTNode> NumericLiteral();
	std::unique_ptr<TASTNode> StringLiteral();

	TToken Eat(TToken::Type tokenType);

	std::unique_ptr<TASTNode> HelperBinaryExpression(
		std::unique_ptr<TASTNode> (TParser::*builder)(),
		TToken::Type operatorToken
	);
};