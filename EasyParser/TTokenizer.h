#pragma once

#include <string>
#include <vector>
#include <regex>

class TToken
{
public:
	enum Type { NUMBER, STRING, WHITESPACE, COMMENT, SEMICOLON, LBRACE, RBRACE, END };

	TToken(Type type, std::string value);

public:
	Type type;
	std::string value;
};

class TTokenizer
{
	std::string m_str;
	size_t m_cursor;

	static const std::vector<std::pair<std::regex, TToken::Type>> m_spec;

public:
	TTokenizer();

	void Init(const std::string& str);

	TToken GetNextToken();

private:
	bool HasMoreTokens() const;
};