#include "TTokenizer.h"

TToken::TToken(Type type, std::string value)
	: type(type),
	  value(value)
{
}


TTokenizer::TTokenizer()
	: m_str(""),
	  m_cursor(0)
{
}

void TTokenizer::Init(const std::string& str)
{
	m_str = str;
	m_cursor = 0;
}

bool TTokenizer::HasMoreTokens() const
{
	return m_cursor < m_str.length();
}

TToken TTokenizer::GetNextToken()
{
	if (HasMoreTokens() == false)
		return TToken(TToken::END, "");

	// Number
	if (std::isdigit(m_str[m_cursor]))
	{
		size_t start = m_cursor;
		while (m_cursor < m_str.length() && std::isdigit(m_str[m_cursor]))
		{
			m_cursor++;
		}

		return TToken(TToken::NUMBER, m_str.substr(start, m_cursor - start));
	}

	if (m_str[m_cursor] == '"')
	{
		size_t start = ++m_cursor;
		while (m_cursor < m_str.length() && m_str[m_cursor] != '"')
		{
			m_cursor++;
		}

		size_t end = m_cursor++;
		return TToken(TToken::STRING, m_str.substr(start, end - start));
	}

	return TToken(TToken::END, "");
}