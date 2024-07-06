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

std::unique_ptr<TASTNode> TParser::StatementList(TToken::Type endTokenType)
{
	auto stmts = std::make_unique<TStatementList>();

	while (m_lookahead.type != TToken::END && m_lookahead.type != endTokenType)
	{
		stmts->AddStatement(Statement());
	}

	return stmts;
}

std::unique_ptr<TASTNode> TParser::Statement()
{
	switch (m_lookahead.type)
	{
	case TToken::SEMICOLON:
		return EmptyStatement();
	case TToken::LBRACE:
		return BlockStatement();
	default:
		return ExpressionStatement();
	}
}

std::unique_ptr<TASTNode> TParser::EmptyStatement()
{
	Eat(TToken::SEMICOLON);

	return std::make_unique<TEmptyStatement>();
}

std::unique_ptr<TASTNode> TParser::BlockStatement()
{
	Eat(TToken::LBRACE);
	auto body = StatementList(TToken::RBRACE);
	Eat(TToken::RBRACE);

	return std::make_unique<TBlockStatement>(std::move(body));
}

std::unique_ptr<TASTNode> TParser::ExpressionStatement()
{
	auto expr = Expression();
	Eat(TToken::SEMICOLON);
	return std::make_unique<TExpressionStatement>(std::move(expr));
}

std::unique_ptr<TASTNode> TParser::Expression()
{
	return AdditiveExpression();
}

std::unique_ptr<TASTNode> TParser::AdditiveExpression()
{
	return HelperBinaryExpression(&TParser::MultiplicativeExpression, TToken::ADD_OP);
}

std::unique_ptr<TASTNode> TParser::MultiplicativeExpression()
{
	return HelperBinaryExpression(&TParser::PrimaryExpression, TToken::MUL_OP);
}

std::unique_ptr<TASTNode> TParser::PrimaryExpression()
{
	if (m_lookahead.type == TToken::LPAREN)
		return ParenthesizedExpression();

	return Literal();
}

std::unique_ptr<TASTNode> TParser::ParenthesizedExpression()
{
	Eat(TToken::LPAREN);
	auto expr = Expression();
	Eat(TToken::RPAREN);
	return expr;
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


std::unique_ptr<TASTNode> TParser::HelperBinaryExpression(
	std::unique_ptr<TASTNode>(TParser::* builder)(),
	TToken::Type operatorToken)
{
	auto left = (this->*builder)();

	while (m_lookahead.type == operatorToken)
	{
		std::string op = Eat(operatorToken).value;
		auto right = (this->*builder)();

		left = std::make_unique<TBinaryExpression>(op, std::move(left), std::move(right));
	}

	return left;
}