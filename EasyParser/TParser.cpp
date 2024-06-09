#include "TParser.h"

#include <sstream>
#include <assert.h>

TParser::TParser()
	: m_lookahead(TToken::END, "")
{
}

std::unique_ptr<TASTNode> TParser::Parse(const std::string& str)
{
	m_str = str;
	m_tokenizer.Init(str);

	m_lookahead = m_tokenizer.GetNextToken();

	return Program();
}

std::unique_ptr<TASTNode> TParser::Program()
{
	return std::make_unique<TProgram>(StatementList());
}

std::unique_ptr<TASTNode> TParser::StatementList()
{
	auto stmts = std::make_unique<TStatementList>();

	while (m_lookahead.type != TToken::END)
	{
		stmts->AddStatement(Statement());
	}

	return stmts;
}

std::unique_ptr<TASTNode> TParser::Statement()
{
	return ExpressionStatement();
}

std::unique_ptr<TASTNode> TParser::ExpressionStatement()
{
	auto expr = Expression();
	Eat(TToken::SEMICOLON);
	return std::make_unique<TExpressionStatement>(std::move(expr));
}

std::unique_ptr<TASTNode> TParser::Expression()
{
	return Literal();
}

std::unique_ptr<TASTNode> TParser::Literal()
{
	switch (m_lookahead.type)
	{
	case TToken::NUMBER:
		return NumericLiteral();
	case TToken::STRING:
		return StringLiteral();
	default:
		assert(0 && "Literal: Unexpected literal production");
	}
}

std::unique_ptr<TASTNode> TParser::NumericLiteral()
{
	TToken token = Eat(TToken::NUMBER);

	return std::make_unique<TNumericLiteral>(std::stoi(token.value));
}

std::unique_ptr<TASTNode> TParser::StringLiteral()
{
	TToken token = Eat(TToken::STRING);

	/* 去掉开头和结尾的引号 */
	std::string trimmed = token.value.substr(1, token.value.size() - 2);

	return std::make_unique<TStringLiteral>(trimmed);
}

TToken TParser::Eat(TToken::Type tokenType)
{
	assert(m_lookahead.type != TToken::END);
	assert(m_lookahead.type == tokenType);

	TToken token = m_lookahead;
	m_lookahead = m_tokenizer.GetNextToken();
	return token;
}