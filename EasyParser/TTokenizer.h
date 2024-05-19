#pragma once

#include <string>

class TToken
{
public:
	enum Type { NUMBER, STRING, END };

	TToken(Type type, std::string value);

public:
	Type type;
	std::string value;
};

class TTokenizer
{
	std::string m_str;
	size_t m_cursor;

public:
	TTokenizer();

	void Init(const std::string& str);

	TToken GetNextToken();

private:
	bool HasMoreTokens() const;
};